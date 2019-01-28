/*
  ==============================================================================

    sspScheduleTask.h
    Created: 21 Jan 2019 2:52:26pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

class sspScheduleTask
{
protected:
	long	next_time_ = 0;		// Duration in milliseconds

public:
	sspScheduleTask() = default;
	sspScheduleTask(const sspScheduleTask& obj) = delete;
	sspScheduleTask& operator= (const sspScheduleTask& obj) = delete;
	virtual ~sspScheduleTask() {}

	// Execute action, return true if the object should be added to the scheduler once more
	virtual bool run() = 0;

	long getNextTime() const { return next_time_; }
};
