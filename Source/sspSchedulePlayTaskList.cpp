/*
  ==============================================================================

    sspSchedulePlayTaskList.cpp
    Created: 31 Jan 2019 1:12:32pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspSchedulePlayTaskList.h"

double sspSchedulePlayTaskList::look_ahead_ = 2.0;

sspSchedulePlayTaskList::sspSchedulePlayTaskList()
	: tasks_()
{
}

void sspSchedulePlayTaskList::reset()
{
	tasks_.clear();
	time_counter_ = 0.0;
}

void sspSchedulePlayTaskList::loadTask(std::weak_ptr<sspPlayTask> task, double seconds)
{
	auto schedule_task = std::make_unique<sspSchedulePlayTask>(task, seconds);

	auto iter = tasks_.begin();
	for (; iter != tasks_.end(); ++iter) {
		if (schedule_task->getTime() < (*iter)->getTime()) {
			(*iter)->getTime() -= schedule_task->getTime();
			tasks_.insert(iter, std::move(schedule_task));
			break;
		}
		else {
			schedule_task->getTime() -= (*iter)->getTime();
		}
	}
	if (iter == tasks_.end()) {
		tasks_.push_back(std::move(schedule_task));
	}
}

std::weak_ptr<sspPlayTask> sspSchedulePlayTaskList::getFirst(double time)
{
	time_counter_ += time;
	return getNext();
}

std::weak_ptr<sspPlayTask> sspSchedulePlayTaskList::getNext()
{
	if (tasks_.empty()) {
		time_counter_ = 0.0;
		return std::weak_ptr<sspPlayTask>();
	}
	else if (time_counter_ + look_ahead_ > tasks_.front()->getTime()) {
		auto task = std::move(tasks_.front());
		tasks_.pop_front();
		auto ptr = task->getTask().lock();
		if (ptr) ptr->setScheduleTime(task->getTime() - time_counter_);
		time_counter_ -= task->getTime();
		return ptr;
	}
	else {
		return std::weak_ptr<sspPlayTask>();
	}
}
