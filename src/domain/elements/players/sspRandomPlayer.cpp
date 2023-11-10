/*
  ==============================================================================

    sspRandomPlayer.cpp
    Created: 17 Jan 2019 1:40:50pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspRandomPlayer.h"
#include "access/sspLogging.h"

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

	auto cwi = const_weights_.cbegin();
	for (auto wi = weights_.cbegin(); wi != weights_.cend() && cwi != const_weights_.cend(); ++wi, ++cwi) {
		auto ptr = wi->lock();
		accum_sum += *cwi + (ptr ? ptr->getValue() : 0.0);
		accum_weight.push_back(accum_sum);
	}
	
	std::uniform_real_distribution<double> dist(0.0, accum_weight.back());
	auto picked = dist(random_generator);

	auto pli = players_.cbegin();
	for (auto awi = accum_weight.cbegin(); awi != accum_weight.cend() && pli != players_.cend(); ++awi, ++pli) {
		if (picked <= *awi) {
			break;
		}
	}
	auto ptr = pli != players_.cend() ? pli->lock() : players_.back().lock();
	if (ptr && ptr->start(channel, weak_from_this())) {
		setResponder(responder);
		selected_ = ptr;
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
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: No players", getName());
	}
	else if (players_.size() == 1) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn, "{}: Only one player", getName());
	}
	for (auto&& player : players_) {
		auto ptr = player.lock();
		if (!ptr) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid players", getName());
		}
		else if (ptr.get() == this) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Player self reference", getName());
		}
	}
	if (players_.size() != weights_.size() || players_.size() != const_weights_.size()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Mismatch in number of players and weights", getName());
	}

	return bReturn;
}
