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
	: silence_(std::make_shared<sspSilenceTask>())
{
	silence_->setResponder(weak_from_this());
}

bool sspSilencePlayer::initialize()
{
	play_count_ = 0;
	return true;
}

bool sspSilencePlayer::start(std::weak_ptr<sspFinishedResponder> responder)
{
	if (isPlaying())
		return false;

	silence_->setDuration(duration_->getValue());
	if (sspScheduler::Instance().add(silence_)) {
		play_count_ = 1;
		responder_ = responder;
	}

	return isPlaying();
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
