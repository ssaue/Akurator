/*
  ==============================================================================

    sspScheduler.h
    Created: 21 Jan 2019 4:26:05pm
    Author:  sigurds
	Adapted from: LWimsey

  ==============================================================================
*/

#pragma once

#include "sspScheduleTask.h"

#include <memory>
#include <chrono>
#include <vector>
#include <queue>
#include <condition_variable>
#include <atomic>

class sspScheduler
{
public:
	static sspScheduler& Instance();
	bool add(std::weak_ptr<sspScheduleTask> task);

	void enableTasks();
	void disableTasks();

	bool empty();

private:
	using TimePoint = std::chrono::steady_clock::time_point;

	struct Key {
		TimePoint tp;
		std::weak_ptr<sspScheduleTask> task;
	};

	const int threadpool_size_ = 10;
	std::vector<std::thread> threadpool_;
	std::vector<std::weak_ptr<sspScheduleTask>> ready_tasks_;

	struct TimeComparator {
		bool operator()(const Key &a, const Key &b) const {return a.tp > b.tp;}
	};
	std::priority_queue<Key, std::vector<Key>, TimeComparator> task_queue_;

	std::thread timer_thread_;
	std::mutex  timer_lock_, worker_lock_;
	std::condition_variable timer_cv_, worker_cv_;

	bool worker_is_running_ = true;
	bool timer_is_running_ = true;

	std::atomic_bool enable_tasks_ = true;

	void timer_thread();
	void worker_thread();

private:
	// Singleton stuff
	static sspScheduler* s_instance_;
	static bool s_destroyed_;

	sspScheduler();
	sspScheduler(const sspScheduler&) = delete;
	sspScheduler& operator=(const sspScheduler&) = delete;
	~sspScheduler();

	static void create();
	static void onDeadReference();
};
