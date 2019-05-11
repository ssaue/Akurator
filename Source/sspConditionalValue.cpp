/*
  ==============================================================================

    sspConditionalValue.cpp
    Created: 7 Jan 2019 3:34:18pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspConditionalValue.h"
#include "sspLogging.h"

sspConditionalValue::sspConditionalValue()
	: sspValue(), conditionals_(), values_(), default_value_()
{
}

double sspConditionalValue::getValue() const
{
	auto ci = conditionals_.cbegin();
	auto vi = values_.cbegin();
	for (; ci != conditionals_.cend() && vi != values_.cend(); ++vi, ++ci) {
		auto c_ptr = ci->lock(); auto v_ptr = vi->lock();
		if (c_ptr && v_ptr && c_ptr->isTrue()) {
			return v_ptr->getValue();
		}
	}
	auto ptr = default_value_.lock();
	return ptr ? ptr->getValue() : 0.0;
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
		if (cond.expired()) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid conditionals";
		}
	}
	for (auto&& val : values_) {
		auto ptr = val.lock();
		if (!ptr) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid values";
		}
		else if (ptr.get() == this) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
		}
	}
	auto ptr = default_value_.lock();
	if (!ptr) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid default value";
	}
	else if (ptr.get() == this) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
	}

	return bReturn;
}
