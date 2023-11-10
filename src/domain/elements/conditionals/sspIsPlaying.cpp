/*
  ==============================================================================

    sspIsPlaying.cpp
    Created: 10 Jan 2019 12:00:30pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspIsPlaying.h"
#include "access/sspLogging.h"

sspIsPlaying::sspIsPlaying()
	: sspConditional(), players_()
{
}

bool sspIsPlaying::isTrue() const
{
	for (auto play : players_) {
		auto ptr = play.lock();
		if (ptr && ptr->isPlaying()) return true;
	}
	return false;
}

bool sspIsPlaying::verify(int & nErrors, int & /*nWarnings*/) const
{
	bool bReturn = true;

	if (players_.empty()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "No play objects");
	}
	for (auto&& play : players_) {
		if (play.expired()) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "Invalid play objects");
		}
	}

	return bReturn;
}
