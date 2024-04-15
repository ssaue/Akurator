/*
  ==============================================================================

	sspMidiSendChannel.cpp
	Created: 15 Nov 2023
	Author:  Sigurd Saue

  ==============================================================================
*/

#include "sspMidiSendChannel.h"
#include "domain/core/sspDomainPrimitives.h"

sspMidiSendChannel::~sspMidiSendChannel()
{
	stop();
}

bool sspMidiSendChannel::play(const std::string& file_path, std::weak_ptr<sspValue> tempo_fac)
{
	juce::File file(file_path);
	juce::FileInputStream midi_stream(file);
	if (midi_stream.failedToOpen()) {
		return false;
	}

	if (not midi_file_.readFrom(midi_stream, false, nullptr)) {
		return false;
	}
	midi_file_.convertTimestampTicksToSeconds();

	tempo_fac_ = tempo_fac.lock();
	play_thread_ = std::thread(&sspMidiSendChannel::play_thread, this);
	play_thread_.detach();

	return true;
}

void sspMidiSendChannel::play_thread()
{
	juce::MidiMessageSequence sequence;

	// Merge the midi tracks into a single-track sequence
	for (auto i = 0; i < midi_file_.getNumTracks(); ++i) {
		auto* track = midi_file_.getTrack(i);
		if (track->getNumEvents() > 0) sequence.addSequence(*track, 0.0);
	}

	play_is_running_ = true;
	double previous_stamp = 0.0;

	for (auto event : sequence) {
		std::unique_lock<std::mutex> lck{ play_lock_ };

		auto timestamp = event->message.getTimeStamp();
		auto relative_stamp = timestamp - previous_stamp;
		previous_stamp = timestamp;

		if (tempo_fac_) relative_stamp *= tempo_fac_->getValue();

		using namespace std::chrono;
		auto wait_time = duration_cast<steady_clock::duration>(duration<double>(relative_stamp));

		play_cv_.wait_for(lck, wait_time, [&]{ return not play_is_running_; });
		if (not play_is_running_) break;

		if (out_device_ != nullptr) out_device_->sendMessageNow(event->message);
	}

	if (play_is_running_) {
		play_is_running_ = false;
		setFinished();
	}
	else {
		allNotesOff();
	}
}

void sspMidiSendChannel::allNotesOff() const
{
	if (out_device_ != nullptr) {
		for (int i = 1; i <= 16; ++i) {
			out_device_->sendMessageNow(juce::MidiMessage::allNotesOff(i));
		}
	}
}

void sspMidiSendChannel::stop()
{
	{
		std::scoped_lock<std::mutex> lck{ play_lock_ };
		play_is_running_ = false;
		play_cv_.notify_one();
	}
}
