/*
  ==============================================================================

    sspTaskQueue.cpp
    Created: 30 Jan 2019 2:33:43pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspTaskQueue.h"

sspTaskQueue::sspTaskQueue()
	: max_active_(0), max_waiting_(0), lock_(), active_(), waiting_()
{
}

sspTaskQueue::~sspTaskQueue()
{
	clear();
}

sspTaskQueue::TaskReturn sspTaskQueue::loadTask(std::weak_ptr<sspPlayTask> task)
{
	std::scoped_lock<std::mutex> lock{ lock_ };

	if (max_active_ == 0 || active_.size() < max_active_) {
		active_.push_back(task);
		return std::make_tuple(true, true, std::weak_ptr<sspPlayTask>());
	}
	else if (auto load_task = task.lock()) {
		auto pri = load_task->getPriority();
		switch (pri)
		{
		case sspPlayTask::Priority::Cancel:
			return std::make_tuple(false, true, std::weak_ptr<sspPlayTask>());
			break;
		case sspPlayTask::Priority::Wait:
			if (max_waiting_ == 0 || waiting_.size() < max_waiting_) {
				waiting_.push(task);
				return std::make_tuple(false, false, std::weak_ptr<sspPlayTask>());
			}
			else {
				return std::make_tuple(false, true, std::weak_ptr<sspPlayTask>());
			}
			break;
		case sspPlayTask::Priority::Load:
			for (auto qe = active_.begin(); qe != active_.end(); ++qe) {
				auto ptr = qe->lock();
				if (ptr && ptr->getPriority() < pri) {
					active_.erase(qe);
					active_.push_back(task);
					return std::make_tuple(true, true, ptr);
				}
			}
			return std::make_tuple(false, true, std::weak_ptr<sspPlayTask>());
			break;
		case sspPlayTask::Priority::LoadAlways:
			for (auto qe = active_.begin(); qe != active_.end(); ++qe) {
				auto ptr = qe->lock();
				if (ptr && ptr != load_task) {	// A task cannot remove itself
					active_.erase(qe);
					active_.push_back(task);
					return std::make_tuple(true, true, ptr);
				}
			}
			return std::make_tuple(false, true, std::weak_ptr<sspPlayTask>());
			break;
		default:
			return std::make_tuple(false, true, std::weak_ptr<sspPlayTask>());
			break;
		}

	}
	return std::make_tuple(false, true, std::weak_ptr<sspPlayTask>());
}

void sspTaskQueue::removeInactive()
{
	std::scoped_lock<std::mutex> lock{ lock_ };
	active_.remove_if([](std::weak_ptr< sspPlayTask> p) {
		auto sp = p.lock();
		return sp && !sp->isPlaying();
	});
}

std::weak_ptr<sspPlayTask> sspTaskQueue::getWaitingTask()
{
	std::scoped_lock<std::mutex> lock{ lock_ };
	if (!waiting_.empty() && active_.size() < max_active_) {
		auto task = waiting_.front();
		waiting_.pop();
		if (!task.expired()) {
			active_.push_back(task);
			return task;
		}
	}
	return std::weak_ptr<sspPlayTask>();
}

bool sspTaskQueue::empty() const
{
	std::scoped_lock<std::mutex> lock{ lock_ };
	return active_.empty() && waiting_.empty();
}

void sspTaskQueue::clear()
{
	std::scoped_lock<std::mutex> lock{ lock_ };
	for (auto& task : active_) {
		if (auto ptr = task.lock()) {
			ptr->stop();
		}
	}
	active_.clear();
	waiting_ = {};	// Trick for clearing the queue
}

void sspTaskQueue::setMaxTasks(size_t active, size_t waiting)
{
	max_active_ = active; 
	max_waiting_ = waiting;
}

