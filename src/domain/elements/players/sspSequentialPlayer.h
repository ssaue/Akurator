/*
  ==============================================================================

    sspSequentialPlayer.h
    Created: 17 Jan 2019 1:40:02pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "domain/core/sspPlayer.h"
#include "domain/core/sspSharedVector.h"

class sspSequentialPlayer : public sspPlayer
{
	sspWeakVector<sspPlayer> players_;
	
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspPlayer);
		ar & BOOST_SERIALIZATION_NVP(players_);
	}

public:
	sspSequentialPlayer();
	sspSequentialPlayer(const sspSequentialPlayer& obj) = delete;
	sspSequentialPlayer& operator= (const sspSequentialPlayer& obj) = delete;
	virtual ~sspSequentialPlayer() {}

	virtual bool start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder) override;
	virtual void stop() override;

	virtual bool isPlaying() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setPlayers(const sspWeakVector<sspPlayer>& players);
	const sspWeakVector<sspPlayer>& getPlayers() const { return players_; }

private:
	sspWeakVector<sspPlayer>::iterator iterator_;
	bool is_playing_ = false;

	virtual bool update() override;
};
