/*
  ==============================================================================

    sspSchedulerHead.h
    Created: 21 Jan 2019 5:22:33pm
    Author:  sigurds
	Adapted from: seccpur

  ==============================================================================
*/

#pragma once

#include "sspScheduleObject.h"

#include <memory>
#include <map>
#include <chrono>
#include <condition_variable>

class sspSchedulerHead
{
	using time_point = std::chrono::steady_clock::time_point;

	std::pair<time_point, std::weak_ptr<sspScheduleObject>>  task_;
	std::unique_ptr<std::thread> thread_;
	bool wasted_;
	bool done_;

public:
	sspSchedulerHead(std::pair<time_point, std::weak_ptr<sspScheduleObject>> task, std::condition_variable& signal);
	sspSchedulerHead(const sspSchedulerHead&) = delete;
	sspSchedulerHead& operator=(const sspSchedulerHead&) = delete;
	~sspSchedulerHead();

	std::pair<time_point, std::weak_ptr<sspScheduleObject>> get() const {return task_;}
	void set_wasted() { wasted_ = true; }
	bool done() { return done_; }

private:
	void run();
};
