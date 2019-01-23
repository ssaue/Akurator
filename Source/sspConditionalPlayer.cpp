/*
  ==============================================================================

    sspConditionalPlayer.cpp
    Created: 17 Jan 2019 1:41:20pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspConditionalPlayer.h"
#include "sspLogging.h"


bool sspConditionalPlayer::start(std::weak_ptr<sspFinishedResponder> responder)
{
	if (isPlaying())
		return false;

	auto ptr = default_player_;
	assert(conditionals_.size() == players_.size());
	for (size_t i = 0; i < conditionals_.size(); ++i) {
		if (conditionals_.getAt(i)->isTrue())
			selected_ = players_.getAt(i);
	}
	if (ptr->start(weak_from_this())) {
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
	else if (players_.size() == 1 && !default_player_) {
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
	if (conditionals_.empty()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has no conditionals";
	}
	else if (conditionals_.size() == 1) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << " has only one conditional";
	}
	for (auto&& cond : conditionals_) {
		if (!cond) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid conditional";
		}		
	}
	if (players_.size() != conditionals_.size()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << ": The number of players and conditionals do not match";
	}
	if (default_player_ && default_player_.get() == this) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
	}

	return bReturn;
}
