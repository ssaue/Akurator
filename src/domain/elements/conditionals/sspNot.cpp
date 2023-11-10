/*
  ==============================================================================

    sspNot.cpp
    Created: 10 Jan 2019 12:00:54pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspNot.h"
#include "access/sspLogging.h"

sspNot::sspNot()
	: sspConditional(), operand_()
{
}

bool sspNot::isTrue() const
{
	auto ptr = operand_.lock();
	return !ptr || !ptr->isTrue();
}

bool sspNot::verify(int & nErrors, int & /*nWarnings*/) const
{
	bool bReturn = true;

	auto ptr = operand_.lock();
	if (!ptr) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid operands", getName());
	}
	else if (ptr.get() == this) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Self reference in operands", getName());
	}

	return bReturn;
}
