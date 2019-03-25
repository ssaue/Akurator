/*
  ==============================================================================

    sspAudioStream.cpp
    Created: 1 Feb 2019 3:37:42pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspAudioStream.h"
#include "sspStreamMixer.h"
#include "sspScheduler.h"
#include "sspLogging.h"

sspAudioStream::sspAudioStream()
	: sspStream(), volume_factor_(), task_queue_(), mixer_()
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
				mixer_->bufferSolo(ptr->getID(), msg.getTime()->getValue());
			}
		}
		break;
	case sspMessage::Type::Unsolo:
		if (auto ptr = msg.getTask().lock()) {
			if (ptr->getID() >= 0) {
				mixer_->bufferUnSolo(ptr->getID(), msg.getTime()->getValue());
			}
		}
		break;
	case sspMessage::Type::Mute:
		mixer_->masterFadeOut(msg.getTime()->getValue());
		break;
	case sspMessage::Type::Unmute:
		mixer_->masterFadeIn(msg.getTime()->getValue());
		break;
	case sspMessage::Type::SetVolume:
		mixer_->masterVolume(msg.getValue()->getValue(), msg.getTime()->getValue(), sspStreamMixer::Reference::Absolute);
		break;
	case sspMessage::Type::AdjustVolume:
		mixer_->masterVolume(msg.getValue()->getValue(), msg.getTime()->getValue(), sspStreamMixer::Reference::Relative);
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

void sspAudioStream::setMixer(std::unique_ptr<sspStreamMixer> mixer)
{
	mixer_ = std::move(mixer);
}

void sspAudioStream::play(std::weak_ptr<sspPlayTask> task)
{
	bool ready = false;
	auto fade_task = task_queue_.loadTask(task);
	if (fade_task.has_value()) {
		if (auto fade_ptr = fade_task.value().lock()) {
			if (fade_ptr->getID() >= 0) {
				mixer_->bufferFadeOut(fade_ptr->getID(), 5.0);		// TODO: Establish settings for fade out time!!!!!!
				ready = mixer_->start(task, 5.0);					// TODO: Settings for fade in time
			}
			else {
				ready = mixer_->start(task);
			}
		}
	}
	if (ready) sspScheduler::Instance().add(task);
}
