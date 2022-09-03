/*
  ==============================================================================

    sspICPanalogInput.cpp
    Created: 5 May 2019 2:50:45pm
    Author:  Admin

  ==============================================================================
*/

#include "sspICPanalogInput.h"
#include "access/sspLogging.h"
#include "domain/elements/values/sspBasicValue.h"

#include <PacSDK.h>
#pragma comment(lib,"pacsdk.lib")



sspICPanalogInput::sspICPanalogInput()
	: sspICPinput(), value_()
{
}

sspICPanalogInput::~sspICPanalogInput()
{
	terminate();
}

bool sspICPanalogInput::verify(int& nErrors, int& nWarnings) const
{
	bool bReturn = true;

	if (!sspICPinput::verify(nErrors, nWarnings))
		bReturn = false;

	if (value_.expired()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid value";
	}

	return bReturn;
}

bool sspICPanalogInput::update()
{
	if (!sspICPinput::update())
		return false;

	auto ptr = set_value_.lock();
	if (!ptr) return false;

	float read_value;
	if (pac_ReadAI(port_handle_, PAC_REMOTE_IO(address_), channel_, 8, &read_value)) {
		bool bRtn = read_value != ptr->getValue();
		ptr->setValue(read_value);
		return bRtn;
	}
	else {
		return false;
	}
}

void sspICPanalogInput::setValue(std::weak_ptr<sspValue> value)
{ 
	value_ = value; 
	set_value_ = std::dynamic_pointer_cast<sspBasicValue>(value_.lock());
}
