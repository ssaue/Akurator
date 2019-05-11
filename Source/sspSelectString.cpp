/*
  ==============================================================================

    sspSelectString.cpp
    Created: 14 Jan 2019 2:20:50pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspSelectString.h"
#include "sspLogging.h"

sspSelectString::sspSelectString()
	: sspString(), strings_(), value_()
{
}

std::string sspSelectString::getString() const
{
	auto ptr = value_.lock();
	auto val = ptr ? ptr->getValue() : 0.0;
	auto index = val < 0.0 ? 0 : static_cast<size_t>(val + 0.5);	// rounding
	auto select = index < strings_.size() ? strings_[index] : strings_.back();
	auto select_ptr = select.lock();
	return select_ptr ? select_ptr->getString() : std::string("");
}

bool sspSelectString::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (strings_.empty()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has no strings";
	}
	else if (strings_.size() == 1) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << " has only one string";
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
	if (value_.expired()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid select value";
	}

	return bReturn;
}
