/*
  ==============================================================================

    sspConditionalString.cpp
    Created: 14 Jan 2019 2:20:50pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspConditionalString.h"
#include "access/sspLogging.h"

sspConditionalString::sspConditionalString()
	: sspString(), conditionals_(), strings_(), default_string_()
{
}

std::string sspConditionalString::getString() const
{
	auto ci = conditionals_.cbegin();
	auto vi = strings_.cbegin();
	for (; ci != conditionals_.cend() && vi != strings_.cend(); ++vi, ++ci) {
		auto c_ptr = ci->lock(); auto v_ptr = vi->lock();
		if (c_ptr && v_ptr && c_ptr->isTrue()) {
			return v_ptr->getString();
		}
	}
	auto ptr = default_string_.lock();
	return ptr ? ptr->getString() : std::string("");
}

bool sspConditionalString::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (strings_.size() != conditionals_.size()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << ": the number of values/conditionals don't match";
	}

	if (strings_.empty()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has no strings";
	}
	else if (strings_.size() == 1) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << " has only one string";
	}
	for (auto&& cond : conditionals_) {
		if (cond.expired()) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid conditionals";
		}
	}
	for (auto&& str : strings_) {
		auto ptr = str.lock();
		if (!ptr) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid strings";
		}
		else if (ptr.get() == this) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
		}
	}
	auto ptr = default_string_.lock();
	if (!ptr) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid default string";
	}
	else if (ptr.get() == this) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
	}

	return bReturn;
}
