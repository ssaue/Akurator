/*
  ==============================================================================

    sspMessageWithReceiver.h
    Created: 24 Jan 2019 4:50:58pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspMessageHandler.h"

class sspMessageWithReceiver
{
	std::weak_ptr<sspMessageHandler> receiver_;
	sspMessage message_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_NVP(receiver_);
		ar & BOOST_SERIALIZATION_NVP(message_);
	}

public:
	sspMessageWithReceiver();
	sspMessageWithReceiver(const sspMessageWithReceiver& obj) = delete;
	sspMessageWithReceiver& operator= (const sspMessageWithReceiver& obj) = delete;
	virtual ~sspMessageWithReceiver() {}

	bool verify(int& nErrors, int& nWarnings) const;
	void send() const;

	// Accessors
	void setReceiver(std::weak_ptr<sspMessageHandler> handler) { receiver_ = handler; }
	std::weak_ptr<sspMessageHandler> getReceiver() const { return receiver_; }

	const sspMessage& getMessage() const { return message_; }
	sspMessage& getMessage() { return message_; }
};
