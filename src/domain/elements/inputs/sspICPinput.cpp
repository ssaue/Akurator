/*
  ==============================================================================

    sspICPinput.cpp
    Created: 4 May 2019 9:34:23am
    Author:  Admin

  ==============================================================================
*/

#include "sspICPinput.h"
#include "access/sspLogging.h"

#include <string>
#include <sstream>

#include <PacSDK.h>
#pragma comment(lib,"pacsdk.lib")

//////////////////////////////////////////////////////////////////////
// sspICPinput
//////////////////////////////////////////////////////////////////////

namespace {
	// Privately scoped enumeration
	enum { DEFAULT_PORT = 5 };
	enum { BAUDRATE = 9600L, DATABITS = 8, STOPBIT = 0, PARITY = 0, ESC_KEY = 27, TIMEOUT_DELAY = 100 };
	enum IpcCommandSlots { IPC_COMPORT, IPC_ADDRESS, IPC_ID, IPC_CHECKSUM, IPC_TIMEOUT, IPC_CHANNEL, IPC_DEBUGINFO };
}

sspICPinput::HANDLE sspICPinput::port_handle_ = nullptr;

sspICPinput::sspICPinput()
	: sspInput()
	, port_(DEFAULT_PORT)
	, address_(1)
	, channel_(0)
{
}

sspICPinput::~sspICPinput()
{
}

bool sspICPinput::initCom()
{
	std::stringstream stream;
	stream << "COM" << port_ << ",9600,N,8,1";

	if (!port_handle_ || port_handle_ == INVALID_HANDLE_VALUE) {
		port_handle_ = uart_Open(stream.str().c_str());
	}

	if (port_handle_ == INVALID_HANDLE_VALUE) {
		//pac_GetErrorMessage(pac_GetLastError(), strErr);
		//	printf("Open Error: %s. The error code is %x\n", strErr, pac_GetLastError());
		port_handle_ = nullptr;
		return false;
	}
	else {
		return true;
	}
}

bool sspICPinput::verify(int& nErrors, int& nWarnings) const
{
	bool bReturn = true;

	if (!sspInput::verify(nErrors, nWarnings))
		bReturn = false;

	if (port_ != DEFAULT_PORT) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << ": Port is non-standard";
	}
	if (channel_ > 15) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << ":Channel numer it larger than 15";
	}

	return bReturn;
}

bool sspICPinput::initialize()
{
	return initCom() ? sspInput::initialize() : false;
}

bool sspICPinput::update()
{
	return sspInput::update() && port_handle_;
}

void sspICPinput::terminate()
{
	if (port_handle_) {
		uart_Close(port_handle_);
		port_handle_ = nullptr;
	}
}
