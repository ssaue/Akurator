/*
  ==============================================================================

    sspICPinput.cpp
    Created: 4 May 2019 9:34:23am
    Author:  Admin

  ==============================================================================
*/

#include "sspICPinput.h"
#include "sspLogging.h"

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

sspICPinput::sspICPinput()
	: sspInput()
	, port_(DEFAULT_PORT)
	, address_(1)
	, channel_(0)
	, port_handle_(nullptr)
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
	if (port_handle_) uart_Close(port_handle_);
}
//
////////////////////////////////////////////////////////////////////////
//// sspICPdigitalInput
////////////////////////////////////////////////////////////////////////
//
//sspICPdigitalInput::sspICPdigitalInput() : sspICPinput(SSP_ICPCON_DIGITAL)
//{
//	m_nCondIndex = -1;
//	m_command[IPC_ID] = 0x7052; // Digital module
//}
//
//sspICPdigitalInput::sspICPdigitalInput(const sspICPdigitalInput& inp) : sspICPinput(inp)
//{
//	m_nCondIndex = inp.m_nCondIndex;
//	m_command[IPC_ID] = 0x7052; // Digital module
//}
//
//sspICPdigitalInput& sspICPdigitalInput::operator= (const sspICPdigitalInput& inp)
//{
//	sspICPinput::operator=(inp);
//	m_nCondIndex = inp.m_nCondIndex;
//	return *this;
//}
//
//sspICPdigitalInput::~sspICPdigitalInput()
//{
//	end();
//}
//
//void sspICPdigitalInput::Serialize(CArchive& ar)
//{
//	sspICPinput::Serialize(ar);
//	if (ar.IsStoring())
//		ar << m_nCondIndex;
//	else
//		ar >> m_nCondIndex;
//}
//
//void sspICPdigitalInput::printASCII(sspOutStream& outStr)
//{
//	outStr << endl << ": sspICPdigitalInput " << m_strName;
//	sspICPinput::printASCII(outStr);
//	outStr << endl << "   - m_nCondIndex: " << sspPool::Instance().conditionals.GetName(m_nCondIndex);
//}
//
//bool sspICPdigitalInput::verify(sspOutStream& outStr, int& nErrors, int& nWarnings)
//{
//	bool bRet = true;
//	if (!sspICPinput::verify(outStr, nErrors, nWarnings))
//		bRet = false;
//	if (m_nCondIndex < 0 || m_nCondIndex >= (int)sspPool::Instance().conditionals.GetSize()) {
//		printError(outStr, _T("(sspICPdigitalInput): m_nCondIndex is not valid"), nErrors);
//		bRet = false;
//	}
//	else if (sspPool::Instance().conditionals.GetConditional(m_nCondIndex)->getType() != SSP_COND_BOOLEAN) {
//		printError(outStr, _T("(sspICPdigitalInput): m_nCondIndex must be of basic type"), nErrors);
//		bRet = false;
//	}
//	return bRet;
//}
//
//bool sspICPdigitalInput::initialize(LPVOID pWnd)
//{
//	m_pCond = dynamic_cast<SSpBoolean*> (sspPool::Instance().conditionals.GetConditional(m_nCondIndex));
//	if (!m_pCond) return false;
//	return sspICPinput::initialize(pWnd);
//}
//
//bool sspICPdigitalInput::update()
//{
//	if (!sspInput::update())
//		return false;
//
//	if (DigitalIn(m_command, NULL, NULL, NULL) != NoError)
//		return false;
//
//	bool bVal = (m_command[5] & (1 << m_nChannel)) != 0;
//	bool bRtn = bVal ^ m_pCond->isTrue();
//	m_pCond->setValue(bVal);
//	return bRtn;
//}
