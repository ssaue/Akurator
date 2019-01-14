/*
  ==============================================================================

    sspNot.cpp
    Created: 10 Jan 2019 12:00:54pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspNot.h"
#include "sspLogging.h"

bool sspNot::isTrue() const
{
	return !operand_->isTrue();
}

bool sspNot::verify(int & nErrors, int & /*nWarnings*/) const
{
	bool bReturn = true;

	if (!operand_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid operands";
	}
	else if (operand_.get() == this) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
	}

	return bReturn;
}
