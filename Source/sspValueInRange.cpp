/*
  ==============================================================================

    sspValueInRange.cpp
    Created: 10 Jan 2019 11:58:05am
    Author:  sigurds

  ==============================================================================
*/

#include "sspValueInRange.h"
#include "sspLogging.h"

#include <limits>

sspValueInRange::sspValueInRange()
	: sspConditional(), min_(), max_(), test_()
{
}

  bool sspValueInRange::isTrue() const
{
	auto test = test_->getValue();
	auto min = min_->getValue();
	auto max = max_->getValue();

	return ((test >= min && test <= max) || (test >= max && test <= min));
}

bool sspValueInRange::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (!test_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid test value";
	}
	if (!min_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid threshold value";
	}
	if (!max_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid threshold value";
	}
	if (test_.get() == min_.get() || test_.get() == max_.get()) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << ": test value is a range extreme";
	}
	if (min_.get() == max_.get()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << ": min and max are equal values";
	}

	return bReturn;
}
