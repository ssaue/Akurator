/*
  ==============================================================================

    sspSimultaneousPlayer.h
    Created: 17 Jan 2019 1:39:47pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPlayer.h"
#include "sspObjectVector.h"

class sspSimultaneousPlayer : public sspPlayer
{
	sspObjectVector<sspPlayer> players_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspPlayer);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(players_);
	}

public:
	sspSimultaneousPlayer();
	sspSimultaneousPlayer(const sspSimultaneousPlayer& obj) = delete;
	sspSimultaneousPlayer& operator= (const sspSimultaneousPlayer& obj) = delete;
	virtual ~sspSimultaneousPlayer() {}

	virtual bool start(std::weak_ptr<sspFinishedResponder> responder) override;
	virtual void stop() override;

	virtual bool isPlaying() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setPlayers(const sspObjectVector<sspPlayer>& players) { players_ = players; }
	const sspObjectVector<sspPlayer>& getPlayers() const { return players_; }

private:
	int player_count_ = 0;

	virtual bool update() override;
};
