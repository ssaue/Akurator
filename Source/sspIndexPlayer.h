/*
  ==============================================================================

    sspIndexPlayer.h
    Created: 17 Jan 2019 1:40:37pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPlayer.h"
#include "sspObjectVector.h"

class sspIndexPlayer : public sspPlayer
{
	sspObjectVector<sspPlayer> players_;
	std::shared_ptr<sspValue> index_;

	std::weak_ptr<sspPlayer> selected_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspPlayer);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(players_);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(index_);
	}

public:
	sspIndexPlayer() = default;
	sspIndexPlayer(const sspIndexPlayer& obj) = delete;
	sspIndexPlayer& operator= (const sspIndexPlayer& obj) = delete;
	virtual ~sspIndexPlayer() {}

	virtual bool start(std::weak_ptr<sspFinishedResponder> responder) override;
	virtual void stop() override;

	virtual bool update() override;
	virtual bool isPlaying() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setPlayers(const sspObjectVector<sspPlayer>& players) { players_ = players; }
	const sspObjectVector<sspPlayer>& getPlayers() const { return players_; }

	void setIndex(std::shared_ptr<sspValue> value) { index_ = std::move(value); }
	std::shared_ptr<sspValue> getIndex() const { return index_; }
};
