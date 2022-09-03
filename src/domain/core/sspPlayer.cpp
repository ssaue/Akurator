/*
  ==============================================================================

    sspPlayer.cpp
    Created: 17 Jan 2019 11:32:06am
    Author:  sigurds

  ==============================================================================
*/

#include "domain/core/sspPlayer.h"

sspPlayer::sspPlayer()
	: sspPlayObject(), sspFinishedResponder(), responder_()
{
}

void sspPlayer::onFinished()
{
	if (isPlaying() && !update()) {
		channel_.reset();
		if (auto ptr = responder_.lock()) ptr->onFinished();
	}
}

