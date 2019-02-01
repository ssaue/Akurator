/*
  ==============================================================================

    sspAudioStream.cpp
    Created: 1 Feb 2019 3:37:42pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspAudioStream.h"
#include "sspLogging.h"

sspAudioStream::sspAudioStream()
	: sspStream(), volume_factor_(), task_queue_()
{
}

sspAudioStream::~sspAudioStream()
{
	task_queue_.clear();
}

void sspAudioStream::start()
{
	task_queue_.clear();
	task_queue_.setMaxTasks(max_active_, max_waiting_);
	sspStream::start();
}

void sspAudioStream::stop()
{
	task_queue_.clear();
	sspStream::stop();
}

bool sspAudioStream::empty() const
{
	if (!task_queue_.empty()) {
		return false;
	}
	return sspStream::empty();
}

bool sspAudioStream::verify(int & nErrors, int & /*nWarnings*/) const
{
	bool bReturn = true;

	if (!volume_factor_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid volume fader";
	}

	return bReturn;
}

void sspAudioStream::handleMessage(const sspMessage& msg)
{
	sspStream::handleMessage(msg);

	// TODO: A lot of handling missing - need OSC stuff first
	switch (msg.getType())
	{
	case sspMessage::Type::Mute:
		break;
	case sspMessage::Type::Unmute:
		break;
	default:
		break;
	}
}

void sspAudioStream::setMaxTasks(size_t active, size_t waiting)
{
	max_active_ = active;
	max_waiting_ = waiting;
	task_queue_.setMaxTasks(active, waiting);
}

void sspAudioStream::play(std::weak_ptr<sspPlayTask> task)
{
	// TODO: Everything
}
