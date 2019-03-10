/*
  ==============================================================================

    sspDistributionPlayer.h
    Created: 17 Jan 2019 1:41:43pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPlayer.h"
#include "sspSilenceTask.h"

#include <chrono>
#include <memory>
#include <boost/serialization/shared_ptr.hpp>


class sspDistributionPlayer : public sspPlayer
{
public:
	enum class LoopMode : unsigned int { Duration, Count, Condition };

private:
	std::shared_ptr<sspPlayer> player_;
	std::shared_ptr<sspConditional> condition_;
	std::shared_ptr<sspValue> start_time_;
	std::shared_ptr<sspValue> end_time_;
	std::shared_ptr<sspValue> duration_;	// Either time or count (ref. mode)

	LoopMode loop_mode_ = LoopMode::Count;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspPlayer);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(player_);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(condition_);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(start_time_);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(end_time_);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(duration_);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(loop_mode_);
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
	void setDefaultPlayer(std::shared_ptr<sspPlayer> player) { player_ = player; }
	void setCondition(std::shared_ptr<sspConditional> cond) { condition_ = cond; }
	void setStartTime(std::shared_ptr<sspValue> start) { start_time_ = start; }
	void setEndTime(std::shared_ptr<sspValue> end) { end_time_ = end; }
	void setDuration(std::shared_ptr<sspValue> dur) { duration_ = dur; }
	void setLoopMode(LoopMode mode) { loop_mode_ = mode; }

	std::shared_ptr<sspPlayer> getDefaultPlayer() const { return player_; }
	std::shared_ptr<sspValue> getStartTime() const { return start_time_; }
	std::shared_ptr<sspValue> getEndTime() const { return end_time_; }
	std::shared_ptr<sspValue> getDuration() const { return duration_; }
	std::shared_ptr<sspConditional> getCondition() const { return condition_; }
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
