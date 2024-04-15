/*
  ==============================================================================

    sspMidiSendChannel.h
    Created: 15 Nov 2023
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

#include "engine/sspSendChannel.h"
#include <juce_audio_devices/juce_audio_devices.h>

class sspMidiSendChannel : public sspSendChannel
{
public:
	sspMidiSendChannel(juce::MidiOutput* device) : out_device_(device) {}
	sspMidiSendChannel(const sspMidiSendChannel& obj) = delete;
	sspMidiSendChannel& operator= (const sspMidiSendChannel& obj) = delete;
	virtual ~sspMidiSendChannel();

	void sendMessage(std::string, std::vector<ArgumentType>) override {}
	bool play(const std::string& file_path, std::weak_ptr<sspValue> tempo_fac) final;
	void stop() override;

private:
	void play_thread();
	void allNotesOff() const;

	std::thread play_thread_;
	std::mutex  play_lock_;
	std::condition_variable play_cv_;

	bool play_is_running_ = true;

	juce::MidiFile midi_file_;
	std::shared_ptr<sspValue> tempo_fac_;

	juce::MidiOutput* out_device_;
};
