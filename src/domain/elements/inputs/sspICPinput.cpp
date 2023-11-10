/*
  ==============================================================================

    sspICPinput.cpp
    Created: 4 May 2019 9:34:23am
    Author:  Admin

  ==============================================================================
*/

#include "sspICPinput.h"
#include "access/sspLogging.h"
#include "CallbackAsyncSerial.h"

#include <string>
#include <sstream>

//////////////////////////////////////////////////////////////////////
// sspICPinput
//////////////////////////////////////////////////////////////////////

using namespace boost;

namespace icp {
	const int baud_rate = 9600L;
	const uint8_t data_bits = 8;
	const uint8_t default_port = 8;
}

sspICPinput::sspICPinput()
	: sspInput()
	, port_(icp::default_port)
	, address_(1)
	, channel_(0)
{
}

sspICPinput::~sspICPinput()
{
}

void sspICPinput::received(const char* data, size_t len)
{
	static std::stringstream char_stream;

	for (size_t i = 0; i < len; i++, data++) {
		if (*data == '\r') {
			if (callback_) callback_(char_stream.str());
			char_stream.clear();//clear any bits set
			char_stream.str(std::string());
		}
		else {
			char_stream << *data;
		}
	}
}

bool sspICPinput::initSerialCommunication()
{
	auto devname = std::string("COM") + std::to_string(port_);

	try {
		serial_ = std::make_unique<CallbackAsyncSerial>(devname, icp::baud_rate,
			asio::serial_port_base::parity(asio::serial_port_base::parity::none),
			asio::serial_port_base::character_size(icp::data_bits),
			asio::serial_port_base::flow_control(asio::serial_port_base::flow_control::none),
			asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::one));
	}
	catch (boost::system::system_error&) {
		return false;
	}

	if (!serial_->isOpen()) {
		terminate();
		return false;
	}

	serial_->setCallback([&](const char* data, size_t len) { this->received(data, len); });

	return true;
}

bool sspICPinput::verify(int& nErrors, int& nWarnings) const
{
	bool bReturn = true;

	if (!sspInput::verify(nErrors, nWarnings))
		bReturn = false;

	if (port_ != icp::default_port) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn, "{}: Port is non-standard", getName());
	}
	if (channel_ > 15) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Channel number it larger than 15", getName());
	}

	return bReturn;
}

void sspICPinput::setCommand(const std::string& cmd, const std::function<void(const std::string&)>& callback)
{
	cmd_string_ = cmd;
	callback_ = callback;
}

bool sspICPinput::initialize()
{
	return initSerialCommunication() ? sspInput::initialize() : false;
}

bool sspICPinput::update()
{
	if (sspInput::update() && serial_ != nullptr) {
		serial_->writeString(cmd_string_);
		return true;
	}
	return false;
}

void sspICPinput::terminate()
{
	if (serial_ != nullptr) serial_->close();
	serial_.reset();
}
