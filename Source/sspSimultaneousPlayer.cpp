/*
  ==============================================================================

    sspSimultaneousPlayer.cpp
    Created: 17 Jan 2019 1:39:47pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspSimultaneousPlayer.h"
#include "sspLogging.h"

bool sspSimultaneousPlayer::initialize()
{
	play_count_ = 0;
	return true;
}

bool sspSimultaneousPlayer::start(std::weak_ptr<sspFinishedResponder> responder)
{
	if (isPlaying())
		return false;

	auto ptr = weak_from_this();
	for (auto&& player : players_) {
		if (player->start(ptr)) {
			play_count_++;
		}
	}
	if (isPlaying()) {
		responder_ = responder;
		return true;
	}
	else {
		return false;
	}
}

void sspSimultaneousPlayer::stop()
{
	for (auto&& player : players_) {
		player->stop();
	}
	play_count_ = 0;
}

bool sspSimultaneousPlayer::verify(int & nErrors, int & nWarnings) const
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
