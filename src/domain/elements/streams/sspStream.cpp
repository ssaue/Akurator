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
	: sspTimeline(), task_list_(), send_channel_()
{
}

sspStream::~sspStream()
{
	task_list_.reset();
}

void sspStream::start()
{
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

bool sspStream::empty() const
{
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
	// No action necessary
}

void sspStream::play(std::weak_ptr<sspPlayTask> task)
{
	if (auto ptr = task.lock()) {
		ptr->start(send_channel_, weak_from_this());
		sspScheduler::Instance().add(ptr);
	}
}
