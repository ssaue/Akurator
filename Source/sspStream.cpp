/*
  ==============================================================================

    sspStream.cpp
    Created: 31 Jan 2019 4:28:40pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspStream.h"
#include "sspScheduler.h"

sspStream::sspStream()
	: sspTimeline(),lock_(), task_list_()
{
}

sspStream::~sspStream()
{
	std::scoped_lock<std::mutex> lck{ lock_ };
	task_list_.reset();
}

void sspStream::start()
{
	{
		std::scoped_lock<std::mutex> lck{ lock_ };
		task_list_.reset();
	}
	sspTimeline::start();
}

void sspStream::update(double seconds)
{
	if (running_.load()) {
		std::scoped_lock<std::mutex> lck{ lock_ };
		auto task = task_list_.getFirst(getTimeStep(seconds));
		while (!task.expired()) {
			play(task);
			task = task_list_.getNext();
		}
	}
	sspTimeline::update(seconds);
}

bool sspStream::empty() const
{
	{
		std::scoped_lock<std::mutex> lck{ lock_ };
		if (!task_list_.empty()) {
			return false;
		}
	}
	return sspTimeline::empty();
}

void sspStream::handleMessage(const sspMessage& msg)
{
	sspTimeline::handleMessage(msg);

	std::scoped_lock<std::mutex> lck{ lock_ };
	switch (msg.getType())
	{
	case sspMessage::Type::Load:
		task_list_.loadTask(msg.getTask(), msg.getTime()->getValue());
		break;
	case sspMessage::Type::Mute:
	case sspMessage::Type::Solo:
		running_ = false;
		break;
	case sspMessage::Type::Unmute:
	case sspMessage::Type::Unsolo:
		running_ = true;
		break;
	default:
		break;
	}
}

void sspStream::onFinished()
{
	// No action necessary
}

void sspStream::play(std::weak_ptr<sspPlayTask> task)
{
	// sspStream have no tasks that need a send channel (e.g. OSC)
	if (auto ptr = task.lock()) {
		ptr->start(std::weak_ptr<sspSendChannel>(), weak_from_this());
		sspScheduler::Instance().add(ptr);
	}
}
