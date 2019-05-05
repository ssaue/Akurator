/*
  ==============================================================================

    sspRandomPlayer.cpp
    Created: 17 Jan 2019 1:40:50pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspRandomPlayer.h"
#include "sspLogging.h"

#include <random>

namespace {
	// Establish a random-number engine
	std::random_device rd;
	std::mt19937 random_generator(rd());
}

sspRandomPlayer::sspRandomPlayer()
	: sspPlayer(), players_(), weights_(), const_weights_(), selected_()
{
}

bool sspRandomPlayer::start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder)
{
	if (isPlaying())
		return false;

	double accum_sum = 0.0;
	std::vector<double> accum_weight;
	auto min_size = std::min(players_.size(), std::min(weights_.size(), const_weights_.size()));
	for (size_t i = 0; i < min_size; i++) {
		accum_sum += const_weights_[i] + weights_.getAt(i)->getValue();
		accum_weight.push_back(accum_sum);
	}
	
	std::uniform_real_distribution<double> dist(0.0, accum_weight.back());
	auto picked = dist(random_generator);

	auto player = players_.getLast();
	for (size_t i = 0; i < min_size; i++) {
		if (picked <= accum_weight[i]) {
			player = players_.getAt(i);
			break;
		}
	}
	if (player->start(channel, weak_from_this())) {
		setResponder(responder);
		selected_ = player;
	}

	return isPlaying();
}

void sspRandomPlayer::stop()
{
	if (auto ptr = selected_.lock())
		ptr->stop();
	selected_.reset();
}

bool sspRandomPlayer::update()
{
	selected_.reset();
	return false;
}

bool sspRandomPlayer::isPlaying() const
{
	return !selected_.expired();
}

bool sspRandomPlayer::verify(int & nErrors, int & nWarnings) const
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
	if (players_.size() != weights_.size() || players_.size() != const_weights_.size()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << ": Mismatch in number of players and weights";
	}

	return bReturn;
}
