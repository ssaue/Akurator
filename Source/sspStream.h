/*
  ==============================================================================

    sspStream.h
    Created: 31 Jan 2019 4:28:40pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspTimeline.h"
#include "sspFinishedResponder.h"
#include "sspSchedulePlayTaskList.h"

#include <mutex>

class sspStream : public sspTimeline,
				  public sspFinishedResponder
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

protected:
	virtual void play(std::weak_ptr<sspPlayTask> task);

private:
	mutable std::mutex lock_;
	sspSchedulePlayTaskList task_list_;
};
