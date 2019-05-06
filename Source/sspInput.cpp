/*
  ==============================================================================

    sspInput.cpp
    Created: 16 Apr 2019 12:08:10pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "sspInput.h"
#include "sspLogging.h"

sspInput::sspInput()
	: sspDomainElement(), update_interval_(1.0), updater_(update_interval_)
{
}

bool sspInput::initialize()
{
	updater_.setInterval(update_interval_);
	updater_.initialize(false);
	return true;
}

bool sspInput::update()
{
	return updater_.update();
}

bool sspInput::verify(int & nErrors, int & /*nWarnings*/) const
{
	bool bReturn = true;

	if (update_interval_ <= 0.0) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << ": Update interval is too small";
	}

	return bReturn;
}
