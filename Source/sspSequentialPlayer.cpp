/*
  ==============================================================================

    sspSequentialPlayer.cpp
    Created: 17 Jan 2019 1:40:02pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspSequentialPlayer.h"
#include "sspLogging.h"

bool sspSequentialPlayer::start(std::weak_ptr<sspFinishedResponder> responder)
{
	if (isPlaying())
		return false;

	iterator_ = begin(players_);
	if ((*iterator_)->start(weak_from_this())) {
		is_playing_ = true;
		setResponder(responder);
	}

	return (isPlaying());
}

bool sspSequentialPlayer::update()
{
	++iterator_;
	is_playing_ = (iterator_ != end(players_) && (*iterator_)->start(weak_from_this()));
	return isPlaying();
}

bool sspSequentialPlayer::isPlaying() const
{
	return is_playing_;
}

void sspSequentialPlayer::stop()
{
	(*iterator_)->stop();
	is_playing_ = false;
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
