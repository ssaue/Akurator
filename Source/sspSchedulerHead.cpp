/*
  ==============================================================================

    sspSchedulerHead.cpp
    Created: 21 Jan 2019 5:22:34pm
    Author:  sigurds
	Adapted from: seccpur

  ==============================================================================
*/

#include "sspSchedulerHead.h"

sspSchedulerHead::sspSchedulerHead(std::pair<time_point, std::weak_ptr<sspScheduleObject>> task) 
	:task_(task)
{
	wasted_ = false;
	thread_ = std::make_unique<std::thread>(([&]() { run(); }));
}

sspSchedulerHead::~sspSchedulerHead() 
{
	thread_->join();
}

void sspSchedulerHead::run()
{
	auto now = std::chrono::steady_clock::now();
	auto lapse = std::chrono::duration_cast<std::chrono::milliseconds>(task_.first - now);
	std::this_thread::sleep_for(std::chrono::milliseconds(lapse));
	if (!wasted_)
	{
		auto ptr = task_.second.lock();
		if (ptr) ptr->start();
		scheduler::get_instance()->executed(task_.first);
	}
}
