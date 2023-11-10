/*
  ==============================================================================

    sspProductValue.cpp
    Created: 7 Jan 2019 3:34:05pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspProductValue.h"
#include "access/sspLogging.h"

sspProductValue::sspProductValue()
	: sspValue(), factors_()
{
}

  double sspProductValue::getValue() const
{
	double fVal = 1.0;
	for (auto fac : factors_)
		if (auto ptr = fac.lock()) fVal *= ptr->getValue();
	return fVal;
}

bool sspProductValue::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (factors_.empty()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: No factors", getName());
	}
	else if (factors_.size() == 1) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn, "{}: Only one factor", getName());
	}
	for (auto&& fac : factors_) {
		auto ptr = fac.lock();
		if (!ptr) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid factors", getName());
		}
		else if (ptr.get() == this) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Factor self reference", getName());
		}
	}

	return bReturn;
}
