/*
  ==============================================================================

    sspConditionalValue.cpp
    Created: 7 Jan 2019 3:34:18pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspConditionalValue.h"
#include "sspLogging.h"

float sspConditionalValue::getValue() const
{
	auto ci = begin(conditionals_);
	auto vi = begin(values_);
	while (ci != end(conditionals_) && vi != end(values_)) {
		if ((*ci)->isTrue()) return (*vi)->getValue();
		++vi; ++ci;
	}
	return defaultValue_->getValue();
}

bool sspConditionalValue::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (values_.size() != conditionals_.size()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << ": the number of values/conditionals don't match";
	}

	if (values_.empty()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has no values";
	}
	else if (values_.size() == 1) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << " has only one value";
	}
	for (auto&& cond : conditionals_) {
		if (!cond) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid conditionals";
		}
	}
	for (auto&& val : values_) {
		if (!val) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid values";
		}
		else if (val.get() == this) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
		}
	}
	if (!defaultValue_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid default value";
	}
	else if (defaultValue_.get() == this) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
	}

	return bReturn;
}
