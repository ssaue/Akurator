/*
  ==============================================================================

    sspSchedulePlayTaskList.h
    Created: 31 Jan 2019 1:12:32pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspSchedulePlayTask.h"

#include <list>

class sspSchedulePlayTaskList 
{
	std::list<std::unique_ptr<sspSchedulePlayTask>> tasks_;
	double time_counter_ = 0.0;
	static double look_ahead_;

public:
	sspSchedulePlayTaskList();
	sspSchedulePlayTaskList(const sspSchedulePlayTaskList& obj) = delete;
	sspSchedulePlayTaskList& operator= (const sspSchedulePlayTaskList& obj) = delete;
	virtual ~sspSchedulePlayTaskList() { reset(); }
	
	void reset();
	void loadTask(std::weak_ptr<sspPlayTask> task, double seconds);
	bool empty() const { return tasks_.empty(); }

	std::weak_ptr<sspPlayTask> getFirst(double time);
	std::weak_ptr<sspPlayTask> getNext();
};
