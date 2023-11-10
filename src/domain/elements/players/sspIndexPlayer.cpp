/*
  ==============================================================================

    sspIndexPlayer.cpp
    Created: 17 Jan 2019 1:40:37pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspIndexPlayer.h"
#include "access/sspLogging.h"

sspIndexPlayer::sspIndexPlayer()
	: sspPlayer(), players_(), index_(), selected_()
{
}

bool sspIndexPlayer::start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder)
{
	if (players_.empty())
		return false;

	auto value = 0.0;
	if (auto ptr = index_.lock()) {
		value = ptr->getValue() + 0.5; // Rounding
	}
	size_t index = value < 0.0 ? 0 : static_cast<size_t>(value);
	auto player = (index < players_.size()) ? players_[index] : players_.back();
	auto ptr = player.lock();	
	if (ptr && ptr->start(channel, weak_from_this())) {
		setResponder(responder);
		selected_ = player;
	}

	return isPlaying();
}

void sspIndexPlayer::stop()
{
	if (auto ptr = selected_.lock()) ptr->stop();
	selected_.reset();
}

bool sspIndexPlayer::update()
{
	selected_.reset();
	return false;
}

bool sspIndexPlayer::isPlaying() const
{
	return !selected_.expired();
}

bool sspIndexPlayer::verify(int & nErrors, int & nWarnings) const
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
	if (index_.expired()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid index value", getName());
	}

	return bReturn;
}
