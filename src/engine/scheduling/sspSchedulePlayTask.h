/*
  ==============================================================================

    sspSchedulePlayTask.h
    Created: 31 Jan 2019 11:15:53am
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "domain\core\sspPlayTask.h"

#include <memory>

class sspSchedulePlayTask
{
	std::weak_ptr<sspPlayTask> task_;
	double seconds_ = 0.0;

public:
	sspSchedulePlayTask();
	sspSchedulePlayTask(std::weak_ptr<sspPlayTask> task, double seconds);
	sspSchedulePlayTask(const sspSchedulePlayTask& obj) = delete;
	sspSchedulePlayTask& operator= (const sspSchedulePlayTask& obj) = delete;
	virtual ~sspSchedulePlayTask() {}

	void setTask(std::weak_ptr<sspPlayTask> task, double seconds);
	std::weak_ptr<sspPlayTask> getTask() const { return task_; }

	double getTime() const { return seconds_; }
	double& getTime() { return seconds_; }
};
