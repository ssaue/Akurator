/*
  ==============================================================================

    sspValueInRange.cpp
    Created: 10 Jan 2019 11:58:05am
    Author:  sigurds

  ==============================================================================
*/

#include "sspValueInRange.h"
#include "access/sspLogging.h"

#include <limits>

sspValueInRange::sspValueInRange()
	: sspConditional(), min_(), max_(), test_()
{
}

bool sspValueInRange::isTrue() const
{
	auto test_ptr = test_.lock();
	if (!test_ptr) return false;
	auto test = test_ptr->getValue();

	auto min_ptr = min_.lock();
	if (!min_ptr) return false;
	auto min = min_ptr->getValue();

	auto max_ptr = max_.lock();
	if (!max_ptr) return false;
	auto max = max_ptr->getValue();

	return ((test >= min && test <= max) || (test >= max && test <= min));
}

bool sspValueInRange::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	auto test_ptr = test_.lock();
	auto min_ptr = min_.lock();
	auto max_ptr = max_.lock();

	if (!test_ptr) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid test value", getName());
	}
	if (!min_ptr) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid minimum value", getName());
	}
	if (!max_ptr) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid maximum value", getName());
	}
	if (test_ptr == min_ptr || test_ptr == max_ptr) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn, "{}: Test value refer to either min or max value", getName());
	}
	if (min_ptr == max_ptr) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Min and max refer to the same value", getName());
	}

	return bReturn;
}
