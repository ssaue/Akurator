/*
  ==============================================================================

    sspPlayTask.h
    Created: 28 Jan 2019 9:54:07am
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "domain/core/sspPlayer.h"
#include "engine/scheduling/sspScheduleTask.h"
#include "domain/elements/messages/sspConditionalMsgList.h"

#include <array>
#include <memory>
#include <boost/serialization/array.hpp>
#include <boost/serialization/weak_ptr.hpp>
#include <boost/serialization/shared_ptr.hpp>

class sspPlayTask : public sspPlayer, public sspScheduleTask
{
public:
	enum class Priority : unsigned int { Cancel, Wait, Load, LoadAlways };
	enum Messages { Enter, Start, End, Exit, Num };

private:
	std::weak_ptr<sspPlayer> player_;
	std::weak_ptr<sspConditional> condition_;
	std::weak_ptr<sspValue> volume_factor_;
	std::array<std::shared_ptr<sspConditionalMsgList>, Messages::Num> messages_;
	Priority priority_ = Priority::Cancel;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspPlayer);
		ar & BOOST_SERIALIZATION_NVP(player_);
		ar & BOOST_SERIALIZATION_NVP(condition_);
		ar & BOOST_SERIALIZATION_NVP(volume_factor_);
		ar & BOOST_SERIALIZATION_NVP(messages_);
		ar & BOOST_SERIALIZATION_NVP(priority_);
	}

public:
	sspPlayTask();
	sspPlayTask(const sspPlayTask& obj) = delete;
	sspPlayTask& operator= (const sspPlayTask& obj) = delete;
	virtual ~sspPlayTask() {}

	// Methods related to sspPlayer
	virtual bool start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder) override;
	virtual void stop() override;
	virtual void onFinished() override;

	virtual bool isPlaying() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Methods related to ScheduleTask
	void setScheduleTime(double seconds);
	virtual bool run() override;

	// The internals of run(), with an option for not playing
	bool execute(bool run_now);

	// Accessors
	void setPlayer(std::weak_ptr<sspPlayer> player) { player_ = player; }
	void setCondition(std::weak_ptr<sspConditional> cond) { condition_ = cond; }
	void setVolumeFactor(std::weak_ptr<sspValue> value) { volume_factor_ = value; }
	void setMessageList(Messages type, std::shared_ptr<sspConditionalMsgList> list);
	void setPriority(Priority priority) { priority_ = priority; }

	std::weak_ptr<sspPlayer> getPlayer() const { return player_; }
	std::weak_ptr<sspConditional> getCondition() const { return condition_; }
	std::weak_ptr<sspValue> getVolumeFactor() const { return volume_factor_; }
	std::shared_ptr<sspConditionalMsgList> getMessageList(Messages type);
	Priority getPriority() const { return priority_; }
	int getChannelID() const;

private:
	bool is_playing_ = false;
	virtual bool update() override;
};
