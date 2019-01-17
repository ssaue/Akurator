/*
  ==============================================================================

    sspSequentialPlayer.cpp
    Created: 17 Jan 2019 1:40:02pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspSequentialPlayer.h"
#include "sspLogging.h"

bool sspSequentialPlayer::initialize()
{
	play_count_ = 0;
	return true;
}

bool sspSequentialPlayer::start(std::weak_ptr<sspFinishedResponder> responder)
{
	if (isPlaying())
		return false;

	iterator_ = begin(players_);
	if ((*iterator_)->start(weak_from_this())) {
		play_count_ = 1;
		responder_ = responder;
	}
	return (isPlaying());
}

bool sspSequentialPlayer::update()
{
	++iterator_;
	if (iterator_ != end(players_) && (*iterator_)->start(weak_from_this())) {
		return true;
	}
	else {
		play_count_ = 0;
		return false;
	}
}

void sspSequentialPlayer::stop()
{
	(*iterator_)->stop();
	play_count_ = 0;
}

bool sspSequentialPlayer::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (players_.empty()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has no players";
	}
	else if (players_.size() == 1) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << " has only one player";
	}
	for (auto&& player : players_) {
		if (!player) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid players";
		}
		else if (player.get() == this) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
		}
	}

	return bReturn;
}
