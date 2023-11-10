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
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Number of values/conditionals don't match", getName());
	}

	if (strings_.empty()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: No strings", getName());
	}
	else if (strings_.size() == 1) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn, "{}: Only one string", getName());
	}
	for (auto&& cond : conditionals_) {
		if (cond.expired()) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid conditionals", getName());
		}
	}
	for (auto&& str : strings_) {
		auto ptr = str.lock();
		if (!ptr) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid strings", getName());
		}
		else if (ptr.get() == this) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: String self reference", getName());
		}
	}
	auto ptr = default_string_.lock();
	if (!ptr) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid default string", getName());
	}
	else if (ptr.get() == this) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Default string self reference", getName());
	}

	return bReturn;
}
