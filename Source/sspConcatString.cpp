/*
  ==============================================================================

    sspConcatString.cpp
    Created: 14 Jan 2019 2:21:05pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspConcatString.h"
#include "sspLogging.h"

std::string_view sspConcatString::getString() const
{
	std::string cat;
	for (auto&& str : strings_) {
		cat += str->getString();
	}
	return cat;
}

bool sspConcatString::verify(int & nErrors, int & nWarnings) const
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

	return bReturn;
}
