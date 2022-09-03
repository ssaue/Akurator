/*
  ==============================================================================

    sspConditionalPlayer.cpp
    Created: 17 Jan 2019 1:41:20pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspConditionalPlayer.h"
#include "access/sspLogging.h"


sspConditionalPlayer::sspConditionalPlayer()
	: sspPlayer(), players_(), conditionals_(), default_player_()
{
}

bool sspConditionalPlayer::start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder)
{
	if (isPlaying())
		return false;

	auto sel = default_player_;

	auto pli = players_.cbegin();
	for (auto ci = conditionals_.cbegin(); ci != conditionals_.cend() && pli != players_.cend(); ++ci, ++pli) {
		auto c_ptr = ci->lock();
		if (c_ptr && c_ptr->isTrue()) {
			sel = *pli;
			break;
		}
	}
	auto ptr = sel.lock();
	if (ptr && ptr->start(channel, weak_from_this())) {
		setResponder(responder);
		selected_ = ptr;
	}

	return isPlaying();
}

void sspConditionalPlayer::stop()
{
	if (auto ptr = selected_.lock()) ptr->stop();
	selected_.reset();
}

bool sspConditionalPlayer::update()
{
	selected_.reset();
	return false;
}

bool sspConditionalPlayer::isPlaying() const
{
	return !selected_.expired();
}

bool sspConditionalPlayer::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (players_.empty()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has no players";
	}
	else if (players_.size() == 1 && default_player_.expired()) {
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
	if (conditionals_.empty()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has no conditionals";
	}
	for (auto&& cond : conditionals_) {
		if (cond.expired()) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid conditional";
		}		
	}
	if (players_.size() != conditionals_.size()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << ": The number of players and conditionals do not match";
	}
	auto ptr = default_player_.lock();
	if (ptr && ptr.get() == this) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
	}

	return bReturn;
}
