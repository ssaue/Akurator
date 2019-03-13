/*
  ==============================================================================

    sspMessageHandler.h
    Created: 24 Jan 2019 4:54:00pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspDomainElement.h"
#include "sspMessage.h"

class sspMessageHandler : public sspDomainElement
{
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspDomainElement);
	}

public:
	sspMessageHandler() : sspDomainElement() {}
	sspMessageHandler(const sspMessageHandler& obj) = delete;
	sspMessageHandler& operator= (const sspMessageHandler& obj) = delete;
	virtual ~sspMessageHandler() {}

	virtual void handleMessage(const sspMessage& msg) = 0;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(sspMessageHandler)
