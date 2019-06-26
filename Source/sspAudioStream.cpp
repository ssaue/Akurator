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
	: sspStream(), volume_factor_(), task_queue_(), bus_(), updater_(sspStreamBus::volume_time_s)
{
	updater_.initialize(false);
}

sspAudioStream::~sspAudioStream()
{
	task_queue_.clear();
}

void sspAudioStream::start()
{
	updater_.initialize(false);
	if (auto ptr = volume_factor_.lock()) {
		master_volume_ = ptr->getValue();
		bus_->busVolume(master_volume_, sspStreamBus::volume_time_s);
	}
	task_queue_.clear();
	task_queue_.setMaxTasks(max_active_, max_waiting_);
	sspStream::start();
}

void sspAudioStream::update(double seconds)
{
	if (updater_.update()) {
		if (auto ptr = volume_factor_.lock()) {
			double volume = ptr->getValue();
			if (abs(volume - master_volume_) > 0.001) {
				master_volume_ = volume;
				bus_->busVolume(master_volume_, sspStreamBus::volume_time_s);
			}
		}
	}
	sspStream::update(seconds);
}

void sspAudioStream::stop()
{
	task_queue_.clear();
	sspStream::stop();
}

void sspAudioStream::terminate()
{
	bus_.reset();
	sspStream::terminate();
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

	if (volume_factor_.expired()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid volume fader";
	}

	return bReturn;
}

void sspAudioStream::handleMessage(const sspMessage& msg)
{
	sspStream::handleMessage(msg);

	auto t_ptr = msg.getTime().lock();
	auto v_ptr = msg.getValue().lock();

	switch (msg.getType())
	{
	case sspMessage::Type::Solo:
		is_solostream_ = true;
		if (auto ptr = msg.getTask().lock()) {
			if (ptr->getChannelID() >= 0 && t_ptr) {
				bus_->channelSolo(ptr->getChannelID(), t_ptr->getValue());
			}
		}
		break;
	case sspMessage::Type::Unsolo:
		is_solostream_ = false;
		if (auto ptr = msg.getTask().lock()) {
			if (ptr->getChannelID() >= 0 && t_ptr) {
				bus_->channelUnSolo(ptr->getChannelID(), t_ptr->getValue());
			}
		}
		break;
	case sspMessage::Type::Mute:
		if (t_ptr) bus_->busFadeOut(t_ptr->getValue());
		break;
	case sspMessage::Type::MuteOnSolo:
		if (!is_solostream_ && t_ptr) bus_->busFadeOut(t_ptr->getValue());
		break;
	case sspMessage::Type::Unmute:
		if (t_ptr) bus_->busFadeIn(t_ptr->getValue());
		break;
	case sspMessage::Type::UnmuteOnSolo:
		if (!is_solostream_ && t_ptr) bus_->busFadeIn(t_ptr->getValue());
		break;
	case sspMessage::Type::SetVolume:
		if (t_ptr && v_ptr) {
			bus_->busVolume(v_ptr->getValue(), t_ptr->getValue(), sspStreamBus::Reference::Absolute);
		}
		break;
	case sspMessage::Type::AdjustVolume:
		if (t_ptr && v_ptr) {
			bus_->busVolume(v_ptr->getValue(), t_ptr->getValue(), sspStreamBus::Reference::Relative);
		}
		break;
	default:
		break;
	}
}

void sspAudioStream::onFinished()
{
	sspStream::onFinished();
	task_queue_.removeInactive();

	if (running_) {
		auto task = task_queue_.getWaitingTask();
		while (auto ptr = task.lock()) {
			if (bus_->play(task, std::weak_ptr<sspPlayTask>())) {
				sspScheduler::Instance().add(task);
			}
			task = task_queue_.getWaitingTask();
		}
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
	auto[is_play_ready, is_exit_ready, old_task]  = task_queue_.loadTask(task);
	if (is_play_ready && bus_->play(task, old_task)) {
		sspScheduler::Instance().add(task);
	}
	else if (is_exit_ready) {
		if (auto ptr = task.lock()) {
			ptr->execute(false);
		}
	}
}
