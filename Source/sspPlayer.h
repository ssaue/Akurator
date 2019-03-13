/*
  ==============================================================================

    sspPlayer.h
    Created: 17 Jan 2019 11:32:06am
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspDomainPrimitives.h"
#include "sspSendChannel.h"
#include "sspFinishedResponder.h"

class sspPlayer : public sspPlayObject, 
				  public sspFinishedResponder
{
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspPlayObject);
	}

public:
	sspPlayer();
	sspPlayer(const sspPlayer& obj) = delete;
	sspPlayer& operator= (const sspPlayer& obj) = delete;
	virtual ~sspPlayer() {}

	virtual bool start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder) = 0;
	virtual void stop() = 0;

	virtual void onFinished() override;
	
	// Accessors

protected:
	void setResponder(std::weak_ptr<sspFinishedResponder> responder) { responder_ = responder; }
	void setSendChannel(std::weak_ptr<sspSendChannel> channel) { channel_ = channel; }
	std::weak_ptr<sspFinishedResponder> getResponder() const { return responder_; }
	std::weak_ptr<sspSendChannel> getSendChannel() const { return channel_; }

	virtual bool update() = 0;

private:
	std::weak_ptr<sspFinishedResponder> responder_;
	std::weak_ptr<sspSendChannel> channel_;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(sspPlayer)

