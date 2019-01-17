/*
  ==============================================================================

    sspSequentialPlayer.h
    Created: 17 Jan 2019 1:40:02pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPlayer.h"
#include "sspObjectVector.h"

class sspSequentialPlayer : public sspPlayer
{
	sspObjectVector<sspPlayer> players_;
	sspObjectVector_iterator<sspPlayer> iterator_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspPlayer);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(players_);
	}

public:
	sspSequentialPlayer() = default;
	sspSequentialPlayer(const sspSequentialPlayer& obj) = delete;
	sspSequentialPlayer& operator= (const sspSequentialPlayer& obj) = delete;
	virtual ~sspSequentialPlayer() {}

	virtual bool initialize() override;
	virtual bool start(std::weak_ptr<sspFinishedResponder> responder) override;
	virtual bool update() override;
	virtual void stop() override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setPlayers(const sspObjectVector<sspPlayer>& players) { players_ = players; }
	const sspObjectVector<sspPlayer>& getPlayers() const { return players_; }
};
