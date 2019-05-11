/*
  ==============================================================================

    sspConditionalPlayer.h
    Created: 17 Jan 2019 1:41:20pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPlayer.h"
#include "sspSharedVector.h"

class sspConditionalPlayer : public sspPlayer
{
	sspWeakVector<sspPlayer> players_;
	sspWeakVector<sspConditional> conditionals_;
	std::weak_ptr<sspPlayer> default_player_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspPlayer);
		ar & BOOST_SERIALIZATION_NVP(conditionals_);
		ar & BOOST_SERIALIZATION_NVP(default_player_);
	}

public:
	sspConditionalPlayer();
	sspConditionalPlayer(const sspConditionalPlayer& obj) = delete;
	sspConditionalPlayer& operator= (const sspConditionalPlayer& obj) = delete;
	virtual ~sspConditionalPlayer() {}

	virtual bool start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder) override;
	virtual void stop() override;

	virtual bool isPlaying() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setPlayers(const sspWeakVector<sspPlayer>& players) { players_ = players; }
	void setConditionals(const sspWeakVector<sspConditional>& conds) { conditionals_ = conds; }
	void setDefaultPlayer(std::weak_ptr<sspPlayer> player) { default_player_ = player; }

	const sspWeakVector<sspPlayer>& getPlayers() const { return players_; }
	const sspWeakVector<sspConditional>& getConditionals() const { return conditionals_; }
	std::weak_ptr<sspPlayer> getDefaultPlayer() const { return default_player_; }

private:
	std::weak_ptr<sspPlayer> selected_;

	virtual bool update() override;
};
