/*
  ==============================================================================

    sspSilencePlayer.cpp
    Created: 17 Jan 2019 1:39:11pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspSilencePlayer.h"
#include "engine/scheduling/sspScheduler.h"
#include "access/sspLogging.h"

sspSilencePlayer::sspSilencePlayer()
	: sspPlayer(), duration_(), silence_(std::make_shared<sspSilenceTask>())
{
}

bool sspSilencePlayer::start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder)
{
	if (isPlaying())
		return false;

	silence_->setResponder(weak_from_this());
	if (auto ptr = duration_.lock()) silence_->setDuration(ptr->getValue());

	if (sspScheduler::Instance().add(silence_)) {
		is_playing_ = true;
		setResponder(responder);
	}

	return isPlaying();
}

void sspSilencePlayer::stop()
{
	is_playing_ = false;
}

bool sspSilencePlayer::update()
{
	is_playing_ = false;
	return false;
}

bool sspSilencePlayer::isPlaying() const
{
	return is_playing_;
}

bool sspSilencePlayer::verify(int & nErrors, int & /*nWarnings*/) const
{
	bool bReturn = true;

	if (duration_.expired()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid duration", getName());
	}
	if (!silence_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid silence object", getName());
	}

	return bReturn;
}
