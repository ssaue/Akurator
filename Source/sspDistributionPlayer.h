/*
  ==============================================================================

    sspDistributionPlayer.h
    Created: 17 Jan 2019 1:41:43pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPlayer.h"
#include "sspObjectVector.h"

class sspDistributionPlayer : public sspPlayer
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
	sspDistributionPlayer() = default;
	sspDistributionPlayer(const sspDistributionPlayer& obj) = delete;
	sspDistributionPlayer& operator= (const sspDistributionPlayer& obj) = delete;
	virtual ~sspDistributionPlayer() {}

	virtual bool initialize() override;
	virtual bool start(std::weak_ptr<sspFinishedResponder> responder) override;
	virtual bool update() override;
	virtual void stop() override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setPlayers(const sspObjectVector<sspPlayer>& players) { players_ = players; }
	const sspObjectVector<sspPlayer>& getPlayers() const { return players_; }
};
