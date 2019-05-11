/*
  ==============================================================================

    sspSilencePlayer.h
    Created: 17 Jan 2019 1:39:11pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPlayer.h"
#include "sspSilenceTask.h"

#include <memory>
#include <boost/serialization/weak_ptr.hpp>

class sspSilencePlayer : public sspPlayer
{
	std::weak_ptr<sspValue> duration_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspPlayer);
		ar & BOOST_SERIALIZATION_NVP(duration_);
	}

public:
	sspSilencePlayer();
	sspSilencePlayer(const sspSilencePlayer& obj) = delete;
	sspSilencePlayer& operator= (const sspSilencePlayer& obj) = delete;
	virtual ~sspSilencePlayer() {}

	virtual bool start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder) override;
	virtual void stop() override;

	virtual bool isPlaying() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setDuration(std::weak_ptr<sspValue> value) { duration_ = value; }
	std::weak_ptr<sspValue> getDuration() const { return duration_; }

private:
	bool is_playing_ = false;
	std::shared_ptr<sspSilenceTask> silence_;

	virtual bool update() override;
};
