/*
  ==============================================================================

    sspSequentialPlayer.cpp
    Created: 17 Jan 2019 1:40:02pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspSequentialPlayer.h"
#include "sspLogging.h"

sspSequentialPlayer::sspSequentialPlayer()
	: sspPlayer(), players_(), iterator_(players_.end())
{
}

bool sspSequentialPlayer::start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder)
{
	if (isPlaying())
		return false;

	iterator_ = players_.begin();
	auto ptr = iterator_->lock();
	if (ptr && ptr->start(channel, weak_from_this())) {
		is_playing_ = true;
		setResponder(responder);
		setSendChannel(channel);
	}

	return (isPlaying());
}

bool sspSequentialPlayer::update()
{
	is_playing_ = false;
	++iterator_;
	if (iterator_ != players_.end()) {
		if (auto ptr = iterator_->lock()) {
			is_playing_ = ptr->start(getSendChannel(), weak_from_this());
		}
	}
	return isPlaying();
}

bool sspSequentialPlayer::isPlaying() const
{
	return is_playing_;
}

void sspSequentialPlayer::stop()
{
	if (iterator_ != players_.end()) {
		if (auto ptr = iterator_->lock()) ptr->stop();
	}
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

void sspSequentialPlayer::setPlayers(const sspWeakVector<sspPlayer>& players)
{
	players_ = players;
	iterator_ = players_.end();
}
