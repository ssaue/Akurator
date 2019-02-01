/*
  ==============================================================================

    sspTaskQueue.h
    Created: 30 Jan 2019 2:33:43pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPlayTask.h"

#include <queue>
#include <memory>
#include <mutex>

class sspTaskQueue
{
	size_t max_active_;
	size_t max_waiting_;

public:
	sspTaskQueue();
	sspTaskQueue(const sspTaskQueue& obj) = delete;
	sspTaskQueue& operator= (const sspTaskQueue& obj) = delete;
	virtual ~sspTaskQueue();

	std::pair<bool, std::weak_ptr<sspPlayTask>> loadTask(std::weak_ptr<sspPlayTask> task);
	void remove(std::weak_ptr<sspPlayTask> task);
	std::weak_ptr<sspPlayTask> getWaitingTask();
	bool empty() const;
	void clear();

	void setMaxTasks(size_t active, size_t waiting);

private:
	mutable std::mutex lock_;
	std::list<std::weak_ptr<sspPlayTask>> active_;
	std::queue<std::weak_ptr<sspPlayTask>> waiting_;
};
