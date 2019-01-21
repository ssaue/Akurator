/*
  ==============================================================================

    sspChainPlayer.h
    Created: 17 Jan 2019 1:41:04pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPlayer.h"
#include "sspObjectVector.h"

class sspChainPlayer : public sspPlayer
{
	sspObjectVector<sspPlayer> players_;
	size_t chain_length_;
	size_t chain_hop_;

	size_t chain_count_;
	size_t selected_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspPlayer);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(players_);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(chain_length_);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(chain_hop_);
	}

public:
	sspChainPlayer() = default;
	sspChainPlayer(const sspChainPlayer& obj) = delete;
	sspChainPlayer& operator= (const sspChainPlayer& obj) = delete;
	virtual ~sspChainPlayer() {}

	virtual bool initialize() override;
	virtual bool start(std::weak_ptr<sspFinishedResponder> responder) override;
	virtual void stop() override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setPlayers(const sspObjectVector<sspPlayer>& players) { players_ = players; }
	void setChainLength(size_t length) { chain_length_ = length; }
	void setChainHop(size_t hop) { chain_hop_ = hop; }

	const sspObjectVector<sspPlayer>& getPlayers() const { return players_; }
	size_t getChainLength() const { return chain_length_; }
	size_t getChainHop() const { return chain_hop_; }
};
