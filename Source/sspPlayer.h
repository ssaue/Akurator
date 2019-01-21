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

	virtual bool initialize() = 0;
	virtual void terminate() {}

	virtual bool start(std::weak_ptr<sspFinishedResponder> responder);
	virtual bool update();
	virtual void stop();

	virtual bool isPlaying() const override { return (play_count_ > 0); }
	virtual void onFinished() override;

protected:
	std::weak_ptr<sspFinishedResponder> responder_;
	short play_count_;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(sspPlayer)

