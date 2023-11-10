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
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: No players", getName());
	}
	else if (players_.size() == 1 && default_player_.expired()) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn, "{}: Only one player", getName());
	}
	for (auto&& player : players_) {
		auto ptr = player.lock();
		if (!ptr) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid player", getName());
		}
		else if (ptr.get() == this) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Players have self reference", getName());
		}
	}
	if (conditionals_.empty()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: No conditionals", getName());
	}
	for (auto&& cond : conditionals_) {
		if (cond.expired()) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid conditional", getName());
		}		
	}
	if (players_.size() != conditionals_.size()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: The number of players and conditionals do not match", getName());
	}
	auto ptr = default_player_.lock();
	if (ptr && ptr.get() == this) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Default player is a self reference", getName());
	}

	return bReturn;
}
