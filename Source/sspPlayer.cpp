/*
  ==============================================================================

    sspPlayer.cpp
    Created: 17 Jan 2019 11:32:06am
    Author:  sigurds

  ==============================================================================
*/

#include "sspPlayer.h"

sspPlayer::sspPlayer()
	: sspPlayObject(), sspFinishedResponder(), responder_()
{
}

void sspPlayer::onFinished()
{
	if (isPlaying() && !update()) {
		if (auto ptr = responder_.lock()) ptr->onFinished();
	}
}
