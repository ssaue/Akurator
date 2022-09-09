/*
  ==============================================================================

    sspICPinput.h
    Created: 4 May 2019 9:34:23am
    Author:  Admin

  ==============================================================================
*/

#pragma once

#include "domain\core\sspInput.h"

/*
** sspICPinput is currently guaranteed to work on Windows only - it needs to be verified on other platforms!
*/

class sspICPinput : public sspInput
{
	unsigned short	port_;

protected:
	unsigned char	channel_;
	unsigned char	address_;

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspInput);
		ar & BOOST_SERIALIZATION_NVP(port_);
		ar & BOOST_SERIALIZATION_NVP(channel_);
		ar & BOOST_SERIALIZATION_NVP(address_);
	}

public:
	sspICPinput();
	sspICPinput(const sspICPinput& inp) = delete;
	sspICPinput& operator= (const sspICPinput& inp) = delete;
	virtual ~sspICPinput() = 0;	// Ensure abstract class

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

protected:
	typedef void* HANDLE;
	HANDLE port_handle_;

private:
	bool initCom();
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(sspICPinput)
