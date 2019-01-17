/*
  ==============================================================================

    sspPlayer.cpp
    Created: 17 Jan 2019 11:32:06am
    Author:  sigurds

  ==============================================================================
*/

#include "sspPlayer.h"

bool sspPlayer::start(std::weak_ptr<sspFinishedResponder> responder)
{
	responder_ = responder;
	play_count_++;
	return true;
}

bool sspPlayer::update()
{
	play_count_--;
	return (play_count_ > 0);
}

void sspPlayer::stop()
{
	play_count_ = 0;
}

void sspPlayer::onFinished()
{
	if (isPlaying() && !update()) {
		if (auto ptr = responder_.lock()) ptr->onFinished();
	}
}
