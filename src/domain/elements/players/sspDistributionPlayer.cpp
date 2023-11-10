/*
  ==============================================================================

    sspDistributionPlayer.cpp
    Created: 17 Jan 2019 1:41:43pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspDistributionPlayer.h"
#include "engine/scheduling/sspScheduler.h"
#include "access/sspLogging.h"

sspDistributionPlayer::sspDistributionPlayer()
	: sspPlayer(), player_(), condition_(), start_time_(), end_time_(),
	duration_(), init_time_(), silence_(std::make_shared<sspSilenceTask>())
{
}

bool sspDistributionPlayer::start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder)
{
	if (isPlaying())
		return false;

	auto ptr = player_.lock();
	if (ptr && ptr->start(channel, weak_from_this())) {
		setResponder(responder);
		setSendChannel(channel);
		is_silence_ = false;
		loop_counter_ = 0;
		is_playing_ = true;
		init_time_ = std::chrono::steady_clock::now();
		silence_->setResponder(weak_from_this());
	}

	return isPlaying();
}

bool sspDistributionPlayer::update()
{
	auto c_ptr = condition_.lock();
	if (!c_ptr || !c_ptr->isTrue()) {
		is_playing_ = false;
		return false;
	}

	// Calculate relative duration (0.0 - 1.0)
	double ramp_pos = 0.0;
	if (!is_silence_) loop_counter_++;

	if (auto dur_ptr = duration_.lock()) {
		switch (loop_mode_) {
		case LoopMode::Duration:
			std::chrono::duration<double, std::milli> diff
				= std::chrono::steady_clock::now() - init_time_;
			std::chrono::duration<double, std::milli> dur
				= std::chrono::milliseconds(static_cast<long>(1000 * dur_ptr->getValue()));
			ramp_pos = (dur > std::chrono::seconds(1) && diff < dur) ? (diff / dur) : 2.0;
			break;
		case LoopMode::Count:
		{
			auto max_count = dur_ptr->getValue();
			ramp_pos = (max_count > 0.5) ? loop_counter_ / max_count : 2.0;
		}
			break;
		default:
			break;
		}
	}

	if (ramp_pos >= 1.0) {	// Duration is passed
		is_playing_ = false;
		return false;
	}

	// If coming from silence, start player again
	if (is_silence_) {
		auto ptr = player_.lock();
		if (ptr && ptr->start(getSendChannel(), weak_from_this())) {
			is_silence_ = false;
			return true;
		}
		else {
			is_playing_ = false;
			return false;
		}
	}

	// If coming from player, calculate next silence
	auto start_ptr = start_time_.lock();
	double silence_dur = start_ptr ? start_ptr->getValue() : 0.0;
	if (auto ptr = end_time_.lock()) {
		silence_dur += ramp_pos * (ptr->getValue() - silence_dur);
	}
	silence_->setDuration(silence_dur);
	if (sspScheduler::Instance().add(silence_)) {
		is_silence_ = true;
	}
	return isPlaying();
}

bool sspDistributionPlayer::isPlaying() const
{
	return is_playing_;
}

void sspDistributionPlayer::stop()
{
	if (!is_silence_) {
		if (auto ptr = player_.lock()) ptr->stop();
	}
	is_playing_ = false;
}

bool sspDistributionPlayer::verify(int & nErrors, int & /*nWarnings*/) const
{
	bool bReturn = true;

	auto ptr = player_.lock();
	if (!ptr) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid player", getName());
	}
	else if (ptr.get() == this) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Player is a self reference", getName());
	}
	if (start_time_.expired()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid start time", getName());
	}
	if ((loop_mode_ != LoopMode::Condition) && duration_.expired()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid duration", getName());
	}
	if (condition_.expired()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid conditional", getName());
	}
	if (!silence_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid silence object", getName());
	}

	return bReturn;
}
