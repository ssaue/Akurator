/*
  ==============================================================================

    sspSilenceTask.cpp
    Created: 21 Jan 2019 2:52:40pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspSilenceTask.h"

bool sspSilenceTask::run(void)
{
	// This object does nothing except pass time
	next_time_ = 0;
	if (auto ptr = responder_.lock()) ptr->onFinished();
	return false;
}

void sspSilenceTask::setDuration(double time)
{
	next_time_ = static_cast<long>(1000 * time);
}
