/*
  ==============================================================================

    sspSecondsRun.cpp
    Created: 7 Jan 2019 3:34:39pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspSecondsRun.h"
#include "sspExecutionState.h"

double sspSecondsRun::getValue() const
{
	return sspExecutionState::Instance().secondsRunning();
}
