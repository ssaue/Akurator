/*
  ==============================================================================

    sspAudioStream.cpp
    Created: 1 Feb 2019 3:37:42pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspAudioStream.h"
#include "sspStreamBus.h"
#include "sspScheduler.h"
#include "sspLogging.h"

sspAudioStream::sspAudioStream()
	: sspStream(), volume_factor_(), task_queue_(), bus_()
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

	switch (msg.getType())
	{
	case sspMessage::Type::Solo:
		if (auto ptr = msg.getTask().lock()) {
			if (ptr->getID() >= 0) {
				bus_->bufferSolo(ptr->getID(), msg.getTime()->getValue());
			}
		}
		break;
	case sspMessage::Type::Unsolo:
		if (auto ptr = msg.getTask().lock()) {
			if (ptr->getID() >= 0) {
				bus_->bufferUnSolo(ptr->getID(), msg.getTime()->getValue());
			}
		}
		break;
	case sspMessage::Type::Mute:
		bus_->masterFadeOut(msg.getTime()->getValue());
		break;
	case sspMessage::Type::Unmute:
		bus_->masterFadeIn(msg.getTime()->getValue());
		break;
	case sspMessage::Type::SetVolume:
		bus_->masterVolume(msg.getValue()->getValue(), msg.getTime()->getValue(), sspStreamBus::Reference::Absolute);
		break;
	case sspMessage::Type::AdjustVolume:
		bus_->masterVolume(msg.getValue()->getValue(), msg.getTime()->getValue(), sspStreamBus::Reference::Relative);
		break;
	default:
		break;
	}
}

void sspAudioStream::setMaxTasks(unsigned int active, unsigned int waiting)
{
	max_active_ = active;
	max_waiting_ = waiting;
	task_queue_.setMaxTasks(active, waiting);
}

void sspAudioStream::setBus(std::unique_ptr<sspStreamBus> mixer)
{
	bus_ = std::move(mixer);
	bus_->setResponder(weak_from_this());
}

void sspAudioStream::play(std::weak_ptr<sspPlayTask> task)
{
	auto ready = task_queue_.loadTask(task);
	if (ready.has_value() && bus_->play(task, ready.value())) {
		sspScheduler::Instance().add(task);
	}
}
