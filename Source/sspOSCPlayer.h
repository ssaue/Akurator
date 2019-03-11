/*
  ==============================================================================

    sspOSCPlayer.h
    Created: 17 Jan 2019 1:38:16pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPlayer.h"

#include <memory>
#include <boost/serialization/shared_ptr.hpp>

class sspOSCPlayer : public sspPlayer
{
	std::shared_ptr<sspString> address_;


	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspPlayer);
		ar & BOOST_SERIALIZATION_NVP(duration_);
		ar & BOOST_SERIALIZATION_NVP(silence_);
	}

public:
	sspOSCPlayer();
	sspOSCPlayer(const sspOSCPlayer& obj) = delete;
	sspOSCPlayer& operator= (const sspOSCPlayer& obj) = delete;
	virtual ~sspOSCPlayer() {}

	virtual bool start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder) override;
	virtual void stop() override;

	virtual bool isPlaying() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors

private:
	virtual bool update() override;
};
