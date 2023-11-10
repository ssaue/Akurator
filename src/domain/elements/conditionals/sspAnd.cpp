/*
  ==============================================================================

    sspAnd.cpp
    Created: 10 Jan 2019 12:00:41pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspAnd.h"
#include "access/sspLogging.h"

sspAnd::sspAnd()
	: sspConditional(), operands_()
{
}

bool sspAnd::isTrue() const
{
	for (auto op : operands_) {
		auto ptr = op.lock();
		if (!ptr || !ptr->isTrue()) return false;
	}
	return true;
}

bool sspAnd::verify(int & nErrors, int & nWarnings) const
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
