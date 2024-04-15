/*
  ==============================================================================

	sspStream.h
	Created: 31 Jan 2019 4:28:40pm
	Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "domain/core/sspTimeline.h"
#include "engine/scheduling/sspSchedulePlayTaskList.h"
#include "engine/scheduling/sspTaskQueue.h"

class sspStream : public sspTimeline
{
	unsigned int max_active_ = 0;
	unsigned int max_waiting_ = 0;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int /*version*/) {
		ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspTimeline);
		ar& BOOST_SERIALIZATION_NVP(max_active_);
		ar& BOOST_SERIALIZATION_NVP(max_waiting_);
	}

public:
	sspStream();
	sspStream(const sspStream& obj) = delete;
	sspStream& operator= (const sspStream& obj) = delete;
	virtual ~sspStream();

	virtual void start() override;
	virtual void update(double seconds) override;
	virtual void stop() final;
	virtual bool empty() const override;

	virtual void handleMessage(const sspMessage& msg) override;
	virtual void onFinished() override;

	void setSendChannel(std::shared_ptr<sspSendChannel> channel_ptr) { send_channel_ = channel_ptr; }

	// Set max number of tasks in each list (0 implies no limit)
	void   setMaxTasks(unsigned int active, unsigned int waiting);
	unsigned int getMaxActive() const { return max_active_; }
	unsigned int getMaxWaiting() const { return max_waiting_; }

private:
	void play(std::weak_ptr<sspPlayTask> task);
	virtual bool replace(std::weak_ptr<sspPlayTask> task, std::weak_ptr<sspPlayTask> old_task);

	sspSchedulePlayTaskList task_list_;
	sspTaskQueue task_queue_;
	std::shared_ptr<sspSendChannel> send_channel_;
};
