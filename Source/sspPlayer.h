/*
  ==============================================================================

    sspPlayer.h
    Created: 17 Jan 2019 11:32:06am
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPrimitives.h"
#include "sspFinishedResponder.h"

class sspPlayer : public sspPlayObject, public sspFinishedResponder
{
	std::weak_ptr<sspFinishedResponder> responder_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspPlayObject);
	}

public:
	sspPlayer() = default;
	sspPlayer(const sspPlayer& obj) = delete;
	sspPlayer& operator= (const sspPlayer& obj) = delete;
	virtual ~sspPlayer() {}

	virtual bool start(std::weak_ptr<sspFinishedResponder> responder) = 0;
	virtual void stop() = 0;

	virtual void onFinished() override;

protected:
	virtual bool update() = 0;
	void setResponder(std::weak_ptr<sspFinishedResponder> responder) { responder_ = responder; }
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(sspPlayer)

