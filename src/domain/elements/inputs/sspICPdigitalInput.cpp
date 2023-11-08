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

namespace icp {
	const size_t read_bytes = 5;
}

sspICPdigitalInput::sspICPdigitalInput()
	: sspICPinput(), conditional_()
{
}

sspICPdigitalInput::~sspICPdigitalInput()
{
	terminate();
}

bool sspICPdigitalInput::initialize()
{
	auto address = getAddress();

	auto cmd = (address > 9 ? "@" : "@0") + std::to_string(address) + "\r";
	setCommand(cmd, [&](const std::string& str) { this->received(str); });

	return sspICPinput::initialize();
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

void sspICPdigitalInput::setConditional(std::weak_ptr<sspConditional> cond)
{ 
	conditional_ = cond; 
	set_conditional_ = std::dynamic_pointer_cast<sspBoolean>(conditional_.lock());
}

void sspICPdigitalInput::received(const std::string& response)
{
	// This must be tested with a digital module!
	if (response.size() != icp::read_bytes) return;

	if (auto ptr = set_conditional_.lock()) {
		auto recv_value = std::stoul(response.substr(1), nullptr, 16);
		bool bOn = (recv_value & (1 << getChannel())) != 0;
		ptr->setValue(bOn);
	}
}
