/*
  ==============================================================================

    sspProductValue.cpp
    Created: 7 Jan 2019 3:34:05pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspProductValue.h"
#include "sspLogging.h"

sspProductValue::sspProductValue()
	: sspValue(), factors_()
{
}

  double sspProductValue::getValue() const
{
	double fVal = 1.0;
	for (auto fac : factors_)
		fVal *= fac->getValue();
	return fVal;
}

bool sspProductValue::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (factors_.empty()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has no factors";
	}
	else if (factors_.size() == 1) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << " has only one factor";
	}
	for (auto&& fac : factors_) {
		if (!fac) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid factors";
		}
		else if (fac.get() == this) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
		}
	}

	return bReturn;
}
