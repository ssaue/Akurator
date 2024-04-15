/*
  ==============================================================================

    sspStream.cpp
    Created: 31 Jan 2019 4:28:40pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspStream.h"
#include "engine/scheduling/sspScheduler.h"

sspStream::sspStream()
	: sspTimeline(), task_list_(), task_queue_(), send_channel_()
{
}

sspStream::~sspStream()
{
	task_queue_.clear();
	task_list_.reset();
}

void sspStream::start()
{
	task_queue_.clear();
	task_queue_.setMaxTasks(max_active_, max_waiting_);
	task_list_.reset();
	sspTimeline::start();
}

void sspStream::update(double seconds)
{
	if (running_.load()) {
		std::weak_ptr<sspPlayTask> task;
		task = task_list_.getFirst(getTimeStep(seconds));
		while (!task.expired()) {
			play(task);
			task = task_list_.getNext();
		}
	}
	sspTimeline::update(seconds);
}

void sspStream::stop()
{
	task_queue_.clear();
}

bool sspStream::empty() const
{
	if (!task_queue_.empty()) {
		return false;
	}
	if (!task_list_.empty()) {
		return false;
	}
	return sspTimeline::empty();
}

void sspStream::handleMessage(const sspMessage& msg)
{
	sspTimeline::handleMessage(msg);

	switch (msg.getType())
	{
	case sspMessage::Type::Load:
		if (auto ptr = msg.getTime().lock()) {
			task_list_.loadTask(msg.getTask(), ptr->getValue());
		}
		break;
	case sspMessage::Type::Mute:
	case sspMessage::Type::Solo:
	case sspMessage::Type::MuteOnSolo:
		running_ = false;
		break;
	case sspMessage::Type::Unmute:
	case sspMessage::Type::Unsolo:
	case sspMessage::Type::UnmuteOnSolo:
		running_ = true;
		break;
	default:
		break;
	}
}

void sspStream::onFinished()
{
	task_queue_.removeInactive();

	if (running_) {
		auto task = task_queue_.getWaitingTask();
		while (auto ptr = task.lock()) {
			replace(task, std::weak_ptr<sspPlayTask>());
			task = task_queue_.getWaitingTask();
		}
	}
}

void sspStream::setMaxTasks(unsigned int active, unsigned int waiting)
{
	max_active_ = active;
	max_waiting_ = waiting;
	task_queue_.setMaxTasks(active, waiting);
}

void sspStream::play(std::weak_ptr<sspPlayTask> task)
{
	auto [is_play_ready, is_exit_ready, old_task] = task_queue_.loadTask(task);
	if (is_play_ready) {
		is_play_ready = replace(task, old_task);
	}
	if (!is_play_ready && is_exit_ready) {
		if (auto ptr = task.lock()) {
			ptr->execute(false);
		}
	}
}

bool sspStream::replace(std::weak_ptr<sspPlayTask> task, std::weak_ptr<sspPlayTask>)
{
	if (auto ptr = task.lock()) {
		ptr->start(send_channel_, weak_from_this());
		sspScheduler::Instance().add(ptr);
		return true;
	}
	return false;
}
