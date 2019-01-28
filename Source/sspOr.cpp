/*
  ==============================================================================

    sspOr.cpp
    Created: 10 Jan 2019 12:00:46pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspOr.h"
#include "sspLogging.h"

sspOr::sspOr()
	: sspConditional(), operands_()
{
}

  bool sspOr::isTrue() const
{
	for (auto op : operands_)
		if (op->isTrue()) return true;
	return false;
}

bool sspOr::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (operands_.empty()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has no operands";
	}
	else if (operands_.size() == 1) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << " has only one operand";
	}
	for (auto&& op : operands_) {
		if (!op) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid operands";
		}
		else if (op.get() == this) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
		}
	}

	return bReturn;
}
