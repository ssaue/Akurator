/*
  ==============================================================================

    sspConcatString.cpp
    Created: 14 Jan 2019 2:21:05pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspConcatString.h"
#include "access/sspLogging.h"

sspConcatString::sspConcatString()
	: sspString(), strings_()
{
}

std::string sspConcatString::getString() const
{
	std::string cat;
	for (auto&& str : strings_) {
		if (auto ptr = str.lock()) cat += ptr->getString();
	}
	return cat;
}

bool sspConcatString::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (strings_.empty()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: No strings", getName());
	}
	else if (strings_.size() == 1) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn, "{}: Only one string", getName());
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

	return bReturn;
}
