/*
  ==============================================================================

    sspChannelMessage.h
    Created: 24 Jan 2019 4:50:58pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspMessageHandler.h"

class sspChannelMessage
{
	std::shared_ptr<sspMessageHandler> receiver_;
	sspMessage message_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(receiver_);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(message_);
	}

public:
	sspChannelMessage();
	sspChannelMessage(const sspChannelMessage& obj) = delete;
	sspChannelMessage& operator= (const sspChannelMessage& obj) = delete;
	virtual ~sspChannelMessage() {}

	bool verify(int& nErrors, int& nWarnings) const;
	void send() const;

	// Accessors
	void setReceiver(std::shared_ptr<sspMessageHandler> handler) { receiver_ = handler; }
	std::shared_ptr<sspMessageHandler> getReceiver() const { return receiver_; }

	const sspMessage& getMessage() const { return message_; }
	sspMessage& getMessage() { return message_; }
};
