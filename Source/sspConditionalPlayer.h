/*
  ==============================================================================

    sspConditionalPlayer.h
    Created: 17 Jan 2019 1:41:20pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPlayer.h"
#include "sspObjectVector.h"

class sspConditionalPlayer : public sspPlayer
{
	sspObjectVector<sspPlayer> players_;
	sspObjectVector<sspConditional> conditionals_;
	std::shared_ptr<sspPlayer> default_player_;

	std::weak_ptr<sspPlayer> selected_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspPlayer);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(conditionals_);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(default_player_);
	}

public:
	sspConditionalPlayer() = default;
	sspConditionalPlayer(const sspConditionalPlayer& obj) = delete;
	sspConditionalPlayer& operator= (const sspConditionalPlayer& obj) = delete;
	virtual ~sspConditionalPlayer() {}

	virtual bool initialize() override;
	virtual bool start(std::weak_ptr<sspFinishedResponder> responder) override;
	virtual void stop() override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setPlayers(const sspObjectVector<sspPlayer>& players) { players_ = players; }
	void setConditionals(const sspObjectVector<sspConditional>& conds) { conditionals_ = conds; }
	void setDefaultPlayer(std::shared_ptr<sspPlayer> player) { default_player_ = player; }

	const sspObjectVector<sspPlayer>& getPlayers() const { return players_; }
	const sspObjectVector<sspConditional>& getConditionals() const { return conditionals_; }
	std::shared_ptr<sspPlayer> getDefaultPlayer() const { return default_player_; }
};
