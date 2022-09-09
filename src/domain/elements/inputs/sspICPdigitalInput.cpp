/*
  ==============================================================================

    sspICPdigitalInput.cpp
    Created: 5 May 2019 2:50:45pm
    Author:  Admin

  ==============================================================================
*/

#include "sspICPdigitalInput.h"
#include "access/sspLogging.h"
#include "domain/elements/conditionals/sspBoolean.h"

#include <PacSDK.h>
#pragma comment(lib,"pacsdk.lib")



sspICPdigitalInput::sspICPdigitalInput()
	: sspICPinput(), conditional_()
{
}

sspICPdigitalInput::~sspICPdigitalInput()
{
	terminate();
}

bool sspICPdigitalInput::verify(int& nErrors, int& nWarnings) const
{
	bool bReturn = true;

	if (!sspICPinput::verify(nErrors, nWarnings))
		bReturn = false;

	if (conditional_.expired()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid conditional";
	}

	return bReturn;
}

bool sspICPdigitalInput::update()
{
	if (!sspICPinput::update())
		return false;

	auto ptr = set_conditional_.lock();
	if (!ptr) return false;

	DWORD read_digitals;
	if (pac_ReadDI(port_handle_, PAC_REMOTE_IO(address_), 8, &read_digitals)) {

		bool bVal = (read_digitals & (1 << channel_)) != 0;
		bool bRtn = bVal ^ ptr->isTrue();
		ptr->setValue(bVal);
		return bRtn;
	}
	else {
		return false;
	}
}

void sspICPdigitalInput::setConditional(std::weak_ptr<sspConditional> cond)
{ 
	conditional_ = cond; 
	set_conditional_ = std::dynamic_pointer_cast<sspBoolean>(conditional_.lock());
}
