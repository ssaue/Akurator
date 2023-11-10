/*
  ==============================================================================

    sspOr.cpp
    Created: 10 Jan 2019 12:00:46pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspOr.h"
#include "access/sspLogging.h"

sspOr::sspOr()
	: sspConditional(), operands_()
{
}

bool sspOr::isTrue() const
{
	for (auto op : operands_) {
		auto ptr = op.lock();
		if (ptr && ptr->isTrue()) return true;
	}
	return false;
}

bool sspOr::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (operands_.empty()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: No operands", getName());
	}
	else if (operands_.size() == 1) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn, "{}: Only one operand", getName());
	}
	for (auto&& op : operands_) {
		auto ptr = op.lock();
		if (!ptr) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid operands", getName());
		}
		else if (ptr.get() == this) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Self reference in operands", getName());
		}
	}

	return bReturn;
}
