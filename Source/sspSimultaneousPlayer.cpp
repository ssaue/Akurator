/*
  ==============================================================================

    sspSimultaneousPlayer.cpp
    Created: 17 Jan 2019 1:39:47pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspSimultaneousPlayer.h"
#include "sspLogging.h"

sspSimultaneousPlayer::sspSimultaneousPlayer()
	: sspPlayer(), players_()
{
}

bool sspSimultaneousPlayer::start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder)
{
	if (isPlaying())
		return false;

	player_count_ = 0;
	for (auto&& player : players_) {
		auto ptr = player.lock();
		if (ptr && ptr->start(channel, weak_from_this())) {
			player_count_++;
		}
	}
	if (isPlaying()) {
		setResponder(responder);
		return true;
	}
	else {
		return false;
	}
}

void sspSimultaneousPlayer::stop()
{
	for (auto&& player : players_) {
		if (auto ptr = player.lock()) ptr->stop();
	}
	player_count_ = 0;
}

bool sspSimultaneousPlayer::update()
{
	player_count_ = 0;
	return false;
}

bool sspSimultaneousPlayer::isPlaying() const
{
	return (player_count_ > 0);
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
		auto ptr = player.lock();
		if (!ptr) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid players";
		}
		else if (ptr.get() == this) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
		}
	}

	return bReturn;
}
