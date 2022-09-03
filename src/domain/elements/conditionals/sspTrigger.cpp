/*
  ==============================================================================

    sspTrigger.cpp
    Created: 10 Jan 2019 12:01:11pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspTrigger.h"
#include "access/sspLogging.h"

sspTrigger::sspTrigger()
	: sspConditional(), conditional_()
{
}

  bool sspTrigger::isTrue() const
{
	bool ret = false;
	auto ptr = conditional_.lock();
	bool now = ptr && ptr->isTrue();
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

	auto ptr = conditional_.lock();
	if (!ptr) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid conditional";
	}
	else if (ptr.get() == this) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
	}

	return bReturn;
}

void sspTrigger::reset()
{
	if (auto ptr = conditional_.lock()) {
		old_state_ = ptr->isTrue();
	}
}
