/*
  ==============================================================================

    sspRandomPlayer.h
    Created: 17 Jan 2019 1:40:50pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPlayer.h"
#include "sspDomainVector.h"

class sspRandomPlayer : public sspPlayer
{
	sspDomainVector<sspPlayer> players_;
	sspDomainVector<sspValue> weights_;
	std::vector<double> const_weights_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspPlayer);
		ar & BOOST_SERIALIZATION_NVP(players_);
		ar & BOOST_SERIALIZATION_NVP(weights_);
		ar & BOOST_SERIALIZATION_NVP(const_weights_);
	}

public:
	sspRandomPlayer();
	sspRandomPlayer(const sspRandomPlayer& obj) = delete;
	sspRandomPlayer& operator= (const sspRandomPlayer& obj) = delete;
	virtual ~sspRandomPlayer() {}

	virtual bool start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder) override;
	virtual void stop() override;

	virtual bool isPlaying() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setPlayers(const sspDomainVector<sspPlayer>& players) { players_ = players; }
	void setWeights(const sspDomainVector<sspValue>& values) { weights_ = values; }
	void setConstantWeights(const std::vector<double>& nums) { const_weights_ = nums; }

	const sspDomainVector<sspPlayer>& getPlayers() const { return players_; }
	const sspDomainVector<sspValue>& getWeights() const { return weights_; }
	const std::vector<double>& getConstantWeights() const { return const_weights_; }

private:
	std::weak_ptr<sspPlayer> selected_;

	virtual bool update() override;
};
