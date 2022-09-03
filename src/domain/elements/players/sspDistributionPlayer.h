/*
  ==============================================================================

    sspDistributionPlayer.h
    Created: 17 Jan 2019 1:41:43pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "domain/core/sspPlayer.h"
#include "engine/scheduling/sspSilenceTask.h"

#include <chrono>
#include <memory>
#include <boost/serialization/weak_ptr.hpp>

class sspDistributionPlayer : public sspPlayer
{
public:
	enum class LoopMode : unsigned int { Duration, Count, Condition };

private:
	std::weak_ptr<sspPlayer> player_;
	std::weak_ptr<sspConditional> condition_;
	std::weak_ptr<sspValue> start_time_;
	std::weak_ptr<sspValue> end_time_;
	std::weak_ptr<sspValue> duration_;	// Either time or count (ref. mode)

	LoopMode loop_mode_ = LoopMode::Count;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspPlayer);
		ar & BOOST_SERIALIZATION_NVP(player_);
		ar & BOOST_SERIALIZATION_NVP(condition_);
		ar & BOOST_SERIALIZATION_NVP(start_time_);
		ar & BOOST_SERIALIZATION_NVP(end_time_);
		ar & BOOST_SERIALIZATION_NVP(duration_);
		ar & BOOST_SERIALIZATION_NVP(loop_mode_);
	}

public:
	sspDistributionPlayer();
	sspDistributionPlayer(const sspDistributionPlayer& obj) = delete;
	sspDistributionPlayer& operator= (const sspDistributionPlayer& obj) = delete;
	virtual ~sspDistributionPlayer() {}

	virtual bool start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder) override;
	virtual void stop() override;

	virtual bool isPlaying() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setPlayer(std::weak_ptr<sspPlayer> player) { player_ = player; }
	void setCondition(std::weak_ptr<sspConditional> cond) { condition_ = cond; }
	void setStartTime(std::weak_ptr<sspValue> start) { start_time_ = start; }
	void setEndTime(std::weak_ptr<sspValue> end) { end_time_ = end; }
	void setDuration(std::weak_ptr<sspValue> dur) { duration_ = dur; }
	void setLoopMode(LoopMode mode) { loop_mode_ = mode; }

	std::weak_ptr<sspPlayer> getPlayer() const { return player_; }
	std::weak_ptr<sspValue> getStartTime() const { return start_time_; }
	std::weak_ptr<sspValue> getEndTime() const { return end_time_; }
	std::weak_ptr<sspValue> getDuration() const { return duration_; }
	std::weak_ptr<sspConditional> getCondition() const { return condition_; }
	LoopMode getLoopMode() const { return loop_mode_; }

private:
	using TimePoint = std::chrono::steady_clock::time_point;
	TimePoint init_time_;

	std::shared_ptr<sspSilenceTask> silence_;
	int loop_counter_ = 0;
	bool is_silence_ = false;
	bool is_playing_ = false;

	virtual bool update() override;
};
