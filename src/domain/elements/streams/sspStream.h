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

class sspStream : public sspTimeline
{
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspTimeline);
	}

public:
	sspStream();
	sspStream(const sspStream& obj) = delete;
	sspStream& operator= (const sspStream& obj) = delete;
	virtual ~sspStream();

	virtual void start() override;
	virtual void update(double seconds) override;
	virtual bool empty() const override;

	virtual void handleMessage(const sspMessage& msg) override;
	virtual void onFinished() override;

	void setSendChannel(std::shared_ptr<sspSendChannel> channel_ptr) { send_channel_ = channel_ptr; }

private:
	virtual void play(std::weak_ptr<sspPlayTask> task);

	sspSchedulePlayTaskList task_list_;
	std::shared_ptr<sspSendChannel> send_channel_;
};
