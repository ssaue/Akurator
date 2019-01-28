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
#include <boost/serialization/shared_ptr.hpp>

class sspSilencePlayer : public sspPlayer
{
	std::shared_ptr<sspValue> duration_;
	std::shared_ptr<sspSilenceTask> silence_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspPlayer);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(duration_);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(silence_);
	}

public:
	sspSilencePlayer();
	sspSilencePlayer(const sspSilencePlayer& obj) = delete;
	sspSilencePlayer& operator= (const sspSilencePlayer& obj) = delete;
	virtual ~sspSilencePlayer() {}

	virtual bool start(std::weak_ptr<sspFinishedResponder> responder) override;
	virtual void stop() override;

	virtual bool isPlaying() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setDuration(std::shared_ptr<sspValue> value) { duration_ = value; }
	std::shared_ptr<sspValue> getDuration() const { return duration_; }

private:
	bool is_playing_ = false;

	virtual bool update() override;
};
