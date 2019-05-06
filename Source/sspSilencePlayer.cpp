/*
  ==============================================================================

    sspSilencePlayer.cpp
    Created: 17 Jan 2019 1:39:11pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspSilencePlayer.h"
#include "sspScheduler.h"
#include "sspLogging.h"

sspSilencePlayer::sspSilencePlayer()
	: sspPlayer(), duration_(), silence_(std::make_shared<sspSilenceTask>())
{
}

bool sspSilencePlayer::start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder)
{
	if (isPlaying())
		return false;

	silence_->setResponder(weak_from_this());
	silence_->setDuration(duration_->getValue());

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

	if (!duration_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has an invalid duration";
	}
	if (!silence_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has an invalid silence object";
	}

	return bReturn;
}
