/*
  ==============================================================================

    sspICPinput.h
    Created: 4 May 2019 9:34:23am
    Author:  Admin

  ==============================================================================
*/

#pragma once

#include "sspInput.h"
#include <vector>

class SSpBoolean;
class sspBasicValue;

/*
** sspICPinput is currently guaranteed to work on Windows only - it needs to be verified on other platforms!
*/

class sspICPinput : public sspInput
{
protected:
	typedef void* HANDLE;
	HANDLE port_handle_;

	unsigned short	port_;
	unsigned char	channel_;
	unsigned char	address_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspDomainElement);
		ar & BOOST_SERIALIZATION_NVP(port_);
		ar & BOOST_SERIALIZATION_NVP(channel_);
		ar & BOOST_SERIALIZATION_NVP(address_);
	}

public:
	sspICPinput();
	sspICPinput(const sspICPinput& inp) = delete;
	sspICPinput& operator= (const sspICPinput& inp) = delete;
	virtual ~sspICPinput() {}

	virtual bool initialize() override;
	virtual bool update() override;
	virtual void terminate() override;

	virtual bool verify(int& nErrors, int& nWarnings) const override;

	void setPort(unsigned short nPort) { port_ = nPort; }
	void setChannel(unsigned char nChannel) { channel_ = nChannel; }
	void setAddress(unsigned char nAddress) { address_ = nAddress; }

	unsigned short	getPort() const { return port_; }
	unsigned char	getChannel() const { return channel_; }
	unsigned char	getAddress() const { return address_; }

private:
	bool initCom();
};

class sspICPanalogInput : public sspICPinput
{
	std::shared_ptr<sspBasicValue> value_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspDomainElement);
		ar & BOOST_SERIALIZATION_NVP(value_);
	}


public:
	sspICPanalogInput();
	sspICPanalogInput(const sspICPanalogInput& inp) = delete;
	sspICPanalogInput& operator= (const sspICPanalogInput& inp) = delete;
	virtual ~sspICPanalogInput();

	virtual bool update() override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	void setValue(std::shared_ptr<sspBasicValue> value) { value_ = std::move(value); }
	std::shared_ptr<sspBasicValue> getValue() const { return value_; }
};
//
//
//class sspICPdigitalInput : public sspICPinput
//{
//protected:
//	DECLARE_SERIAL(sspICPdigitalInput)
//	int			m_nCondIndex;
//	SSpBoolean*	m_pCond;
//
//public:
//	sspICPdigitalInput();
//	sspICPdigitalInput(const sspICPdigitalInput& inp);
//	sspICPdigitalInput& operator= (const sspICPdigitalInput& inp);
//	virtual ~sspICPdigitalInput();
//	void Serialize(CArchive& ar);
//
//	void printASCII(sspOutStream& outStr);
//	bool verify(sspOutStream& outStr, int& nErrors, int& nWarnings);
//	bool initialize(LPVOID pWnd);
//	bool update();
//
//	void setConditional(int nCond) { m_nCondIndex = nCond; }
//	int getConditional() const { return m_nCondIndex; }
//};
