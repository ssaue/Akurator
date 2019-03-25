/*
  ==============================================================================

    sspScheduler.cpp
    Created: 21 Jan 2019 4:26:05pm
    Author:  sigurds
	Adapted from: LWimsey

  ==============================================================================
*/

#include "sspScheduler.h"

#include <stdexcept>

sspScheduler* sspScheduler::s_instance_ = nullptr;
bool sspScheduler::s_destroyed_ = false;

sspScheduler::sspScheduler(void)
	: threadpool_(), ready_tasks_(), task_queue_(), timer_lock_(), worker_lock_()
	, timer_cv_(), worker_cv_()
{
	for (int i = 0; i < threadpool_size_; ++i) {
		threadpool_.push_back(std::thread(&sspScheduler::worker_thread, this));
	}
	timer_thread_ = std::thread(&sspScheduler::timer_thread, this);
}

sspScheduler::~sspScheduler(void)
{
	{
		std::scoped_lock<std::mutex> lck{ timer_lock_ };
		timer_is_running_ = false;
		timer_cv_.notify_one();
	}
	timer_thread_.join();

	{
		std::scoped_lock<std::mutex> lck{ worker_lock_ };
		worker_is_running_ = false;
		worker_cv_.notify_all();
	}
	for (auto &thread : threadpool_)
		thread.join();

	s_instance_ = NULL;
	s_destroyed_ = true;
}

bool sspScheduler::add(std::weak_ptr<sspScheduleTask> task)
{
	auto ptr = task.lock();
	if (!ptr) return false;

	auto now = std::chrono::steady_clock::now();
	TimePoint tp = now + std::chrono::milliseconds(ptr->getNextTime());

	if (now >= tp) {
		std::scoped_lock<std::mutex> lck{ worker_lock_ };
		ready_tasks_.push_back(task);
		worker_cv_.notify_one();
	}
	else {
		std::scoped_lock<std::mutex> lck{ timer_lock_ };
		task_queue_.push({ tp, task });
		timer_cv_.notify_one();
	}
	return true;
}

void sspScheduler::timer_thread()
{
	for (;;) {
		std::unique_lock<std::mutex> lck{ timer_lock_ };

		if (!timer_is_running_)
			break;

		auto duration = std::chrono::nanoseconds(1000000000);

		if (!task_queue_.empty()) {

			auto now = std::chrono::steady_clock::now();
			auto head = task_queue_.top();
			duration = head.tp - now;
			
			if (now >= head.tp) {

				// A Task is due, pass to worker threads
				std::unique_lock<std::mutex> ulck{ worker_lock_ };
				ready_tasks_.push_back(head.task);
				worker_cv_.notify_one();
				ulck.unlock();
			}
			task_queue_.pop();
		}

		timer_cv_.wait_for(lck, duration);
	}
}

void sspScheduler::worker_thread()
{
	for (;;)
	{
		std::unique_lock<std::mutex> lck{ worker_lock_ };
		worker_cv_.wait(lck, [this] { return !ready_tasks_.empty() || !worker_is_running_; });

		if (!worker_is_running_)
			break;

		auto task = ready_tasks_.back();
		ready_tasks_.pop_back();
		lck.unlock();

		if (auto ptr = task.lock()) {
			if (ptr->run()) add(ptr);
		}
	}
}


/*
** Singleton stuff
*/

sspScheduler& sspScheduler::Instance()
{
	if (!s_instance_) {
		if (s_destroyed_) {
			onDeadReference();
		}
		else {
			create();
		}
	}
	return *s_instance_;
}

void sspScheduler::create()
{
	static sspScheduler theInstance;
	s_instance_ = &theInstance;
}

void sspScheduler::onDeadReference()
{
	throw std::runtime_error("Dead reference to sspScheduler detected");
}
