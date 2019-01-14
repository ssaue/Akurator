/*
  ==============================================================================

    sspAddValue.cpp
    Created: 7 Jan 2019 3:33:53pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspAddValue.h"
#include "sspLogging.h"

double sspAddValue::getValue() const
{
	double fVal = 0.0;
	for (auto add : addends_)
		fVal += add->getValue();
	return fVal;
}

bool sspAddValue::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (addends_.empty()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has no addends";
	}
	else if (addends_.size() == 1) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << " has only one addend";
	}
	for (auto&& add : addends_) {
		if (!add) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid addends";
		}
		else if (add.get() == this) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
		}
	}

	return bReturn;
}
