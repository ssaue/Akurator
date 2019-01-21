/*
  ==============================================================================

    sspScheduler.h
    Created: 21 Jan 2019 4:26:05pm
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

class sspSchedulerHead;

class sspScheduler
{
	using time_point = std::chrono::steady_clock::time_point;

	static sspScheduler* s_instance_;
	static bool s_destroyed_;

	std::map<time_point, std::weak_ptr<sspScheduleObject>> timed_tasks;
	std::condition_variable signal_;
	std::mutex lock_;
	std::unique_ptr<sspSchedulerHead> head_;
	std::unique_ptr<std::thread> thread_;
	bool running_;
	bool update_head_;

public:
	static sspScheduler& Instance();

	void insert(std::pair<time_point, std::weak_ptr<sspScheduleObject>> node);
	void remove(time_point tp);
	void close();
	void executed(time_point tp);

private:
	sspScheduler();
	sspScheduler(const sspScheduler&) = delete;
	sspScheduler& operator=(const sspScheduler&) = delete;
	~sspScheduler();

	static void create();
	static void onDeadReference();

	void run();
};
