/*
  ==============================================================================

    sspIndexPlayer.h
    Created: 17 Jan 2019 1:40:37pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPlayer.h"
#include "sspSharedVector.h"

class sspIndexPlayer : public sspPlayer
{
	sspWeakVector<sspPlayer> players_;
	std::weak_ptr<sspValue> index_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspPlayer);
		ar & BOOST_SERIALIZATION_NVP(players_);
		ar & BOOST_SERIALIZATION_NVP(index_);
	}

public:
	sspIndexPlayer();
	sspIndexPlayer(const sspIndexPlayer& obj) = delete;
	sspIndexPlayer& operator= (const sspIndexPlayer& obj) = delete;
	virtual ~sspIndexPlayer() {}

	virtual bool start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder) override;
	virtual void stop() override;

	virtual bool isPlaying() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setPlayers(const sspWeakVector<sspPlayer>& players) { players_ = players; }
	const sspWeakVector<sspPlayer>& getPlayers() const { return players_; }

	void setIndex(std::weak_ptr<sspValue> value) { index_ = std::move(value); }
	std::weak_ptr<sspValue> getIndex() const { return index_; }

private:
	virtual bool update() override;
	std::weak_ptr<sspPlayer> selected_;
};
