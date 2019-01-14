/*
  ==============================================================================

    sspTrigger.cpp
    Created: 10 Jan 2019 12:01:11pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspTrigger.h"
#include "sspLogging.h"

bool sspTrigger::isTrue() const
{
	bool ret = false;
	bool now = conditional_->isTrue();
	switch (change_) {
	case Trigger::False:
		ret = !now & old_state_;
		break;
	case Trigger::True:
		ret = now & !old_state_;
		break;
	case Trigger::Both:
		ret = now ^ old_state_;
		break;
	default:
		break;
	}
	old_state_ = now;
	return ret;
}

bool sspTrigger::verify(int & nErrors, int & /*nWarnings*/) const
{
	bool bReturn = true;

	if (!conditional_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid conditional";
	}
	else if (conditional_.get() == this) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
	}

	return bReturn;
}

void sspTrigger::reset()
{
	old_state_ = conditional_->isTrue();
}
