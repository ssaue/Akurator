/*
  ==============================================================================

    sspDistributionPlayer.cpp
    Created: 17 Jan 2019 1:41:43pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspDistributionPlayer.h"
#include "sspScheduler.h"
#include "sspLogging.h"

sspDistributionPlayer::sspDistributionPlayer()
	: silence_(std::make_shared<sspSilenceTask>())
{
	silence_->setResponder(weak_from_this());
}

bool sspDistributionPlayer::start(std::weak_ptr<sspFinishedResponder> responder)
{
	if (isPlaying())
		return false;

	if (player_->start(weak_from_this())) {
		setResponder(responder);
		is_silence_ = false;
		loop_counter_ = 0;
		is_playing_ = true;
		init_time_ = std::chrono::steady_clock::now();
	}

	return isPlaying();
}

bool sspDistributionPlayer::update()
{
	if (!condition_->isTrue()) {
		is_playing_ = false;
		return false;
	}

	// Calculate relative duration (0.0 - 1.0)
	double ramp_pos = 0.0;
	if (!is_silence_) loop_counter_++;

	switch (loop_mode_) {
	case LoopMode::Duration:
		std::chrono::duration<double, std::milli> diff 
			= std::chrono::steady_clock::now() - init_time_;
		std::chrono::duration<double, std::milli> dur 
			= std::chrono::milliseconds(static_cast<long>(1000 * duration_->getValue()));
		ramp_pos = (dur > std::chrono::seconds(1) && diff < dur) ? (diff / dur) : 2.0;
		break;
	case LoopMode::Count:
		ramp_pos = (duration_->getValue() > 0.5) ? loop_counter_ / duration_->getValue() : 2.0;
		break;
	default:
		break;
	}

	if (ramp_pos >= 1.0) {	// Duration is passed
		is_playing_ = false;
		return false;
	}

	// If coming from silence, start player again
	if (is_silence_) {
		if (player_->start(weak_from_this())) {
			is_silence_ = false;
			return true;
		}
		else {
			is_playing_ = false;
			return false;
		}
	}

	// If coming from player, calculate next silence
	double silence_dur = start_time_->getValue();
	if (end_time_) {
		silence_dur += ramp_pos * (end_time_->getValue() - silence_dur);
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
		player_->stop();
	}
	is_playing_ = false;
}

bool sspDistributionPlayer::verify(int & nErrors, int & /*nWarnings*/) const
{
	bool bReturn = true;

	if (!player_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has an invalid player";
	}
	else if (player_.get() == this) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
	}
	if (!start_time_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has an invalid start time";
	}
	if ((loop_mode_ != LoopMode::Condition) && !duration_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has an invalid duration";
	}
	if (!condition_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has an invalid conditional";
	}
	if (!silence_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has an invalid silence object";
	}

	return bReturn;
}
