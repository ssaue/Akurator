/*
  ==============================================================================

    sspSelectString.cpp
    Created: 14 Jan 2019 2:20:50pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspSelectString.h"
#include "sspLogging.h"

std::string_view sspSelectString::getString() const
{
	auto val = value_->getValue();
	auto index = val < 0.0 ? 0 : static_cast<size_t>(val + 0.5);	// rounding
	auto select = index < strings_.size() ? strings_.getAt(index) : strings_.getAt(strings_.size() - 1);
	return select->getString();
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
		if (!str) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid strings";
		}
		else if (str.get() == this) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
		}
	}
	if (!value_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid select value";
	}

	return bReturn;
}
