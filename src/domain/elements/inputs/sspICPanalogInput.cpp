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

namespace icp {
	const size_t read_bytes = 8;
}

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
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid value", getName());
	}

	return bReturn;
}

bool sspICPanalogInput::initialize()
{
	auto cmd = "#0" + std::to_string(getAddress()) + std::to_string(getChannel()) + "\r";
	setCommand(cmd, [&](const std::string& str) { this->received(str); });

	return sspICPinput::initialize();
}

void sspICPanalogInput::setValue(std::weak_ptr<sspValue> value)
{
	value_ = value;
	set_value_ = std::dynamic_pointer_cast<sspBasicValue>(value_.lock());
}

void sspICPanalogInput::received(const std::string& response)
{
	if (response.size() != icp::read_bytes) return;

	if (auto ptr = set_value_.lock()) {
		auto recv_value = std::stof(response.substr(1));
		ptr->setValue(recv_value);
	}
}
