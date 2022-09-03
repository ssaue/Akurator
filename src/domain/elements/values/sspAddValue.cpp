/*
  ==============================================================================

    sspAddValue.cpp
    Created: 7 Jan 2019 3:33:53pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspAddValue.h"
#include "access/sspLogging.h"

sspAddValue::sspAddValue()
	: sspValue(), addends_()
{
}

  double sspAddValue::getValue() const
{
	double fVal = 0.0;
	for (auto add : addends_)
		if (auto ptr = add.lock()) ptr->getValue();
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
		auto ptr = add.lock();
		if (!ptr) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid addends";
		}
		else if (ptr.get() == this) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
		}
	}

	return bReturn;
}
