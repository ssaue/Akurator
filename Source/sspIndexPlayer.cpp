/*
  ==============================================================================

    sspIndexPlayer.cpp
    Created: 17 Jan 2019 1:40:37pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspIndexPlayer.h"
#include "sspLogging.h"


bool sspIndexPlayer::initialize()
{
	play_count_ = 0;
	return true;
}

bool sspIndexPlayer::start(std::weak_ptr<sspFinishedResponder> responder)
{
	if (players_.empty())
		return false;

	auto value = index_->getValue() + 0.5; // Rounding
	size_t index = value < 0.0 ? 0 : static_cast<size_t>(value);
	auto player = (index < players_.size()) ? players_.getAt(index) : players_.getLast();
	if (player->start(weak_from_this())) {
		play_count_ = 1;
		responder_ = responder;
		selected_ = player;
	}
	return isPlaying();
}

void sspIndexPlayer::stop()
{
	if (auto ptr = selected_.lock()) ptr->stop();
	play_count_ = 0;
}

bool sspIndexPlayer::verify(int & nErrors, int & nWarnings) const
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
	if (!index_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid index value";
	}

	return bReturn;
}
