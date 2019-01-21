/*
  ==============================================================================

    sspSilenceObject.cpp
    Created: 21 Jan 2019 2:52:40pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspSilenceObject.h"

bool sspSilenceObject::start(void)
{
	next_time_ = static_cast<long>(1000 * duration_);
	return true;
}

bool sspSilenceObject::update(void)
{
	next_time_ = 0;
	return false;
}

void sspSilenceObject::finish(void)
{
	if (auto ptr = responder_.lock()) ptr->onFinished();
}
