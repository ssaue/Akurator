/*
  ==============================================================================

	sspChainPlayer.cpp
	Created: 17 Jan 2019 1:39:47pm
	Author:  sigurds

  ==============================================================================
*/

#include "sspChainPlayer.h"
#include "sspLogging.h"

#include <random>

namespace {
	// Establish a random-number engine
	std::random_device rd;
	std::mt19937 random_generator(rd());
}

sspChainPlayer::sspChainPlayer()
	: sspPlayer(), players_()
{
}

bool sspChainPlayer::start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder)
{
	if (isPlaying())
		return false;

	if (chain_count_ >= chain_length_) {
		std::uniform_int_distribution<size_t> dist(0, players_.size()-1);
		selected_ = dist(random_generator);
		chain_count_ = 1;
	}
	else {
		selected_ = (selected_ + chain_hop_) % players_.size();
		chain_count_++;
	}

	auto player = players_.getAt(selected_);
	if (player->start(channel, weak_from_this())) {
		is_playing_ = true;
		setResponder(responder);
	}
	return isPlaying();
}

void sspChainPlayer::stop()
{
	is_playing_ = false;
	auto player = players_.getAt(selected_);
	player->stop();
	chain_count_ = chain_length_;
}

bool sspChainPlayer::update()
{
	is_playing_ = false;
	return false;
}

bool sspChainPlayer::isPlaying() const
{
	return is_playing_;
}

bool sspChainPlayer::verify(int & nErrors, int & nWarnings) const
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
	if (chain_length_ <= 1) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << ": the chain has too few elements";
	}
	if (chain_hop_ > players_.size()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << ": the chain hop is too long";
	}
	if ((chain_hop_ * chain_length_) > players_.size()) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << ": the chain may have repeated elements";
	}

	return bReturn;
}
