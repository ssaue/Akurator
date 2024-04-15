/*
  ==============================================================================

    sspPlayManager.cpp
    Created: 31 Mar 2019 7:12:48pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "sspPlayManager.h"
#include "domain/elements/streams/sspAudioStream.h"
#include "sspStreamBus.h"
#include "sspExecutionState.h"
#include "scheduling/sspScheduler.h"
#include "sspResetManager.h"

#include "domain/elements/messages/sspConditionalMsgList.h"
#include "domain/elements/messages/sspTriggerMsgList.h"
#include "domain/elements/messages/sspTimeTriggerMsgList.h"

using namespace std::chrono;

sspPlayManager::~sspPlayManager()
{
}

bool sspPlayManager::verify(int & , int & ) const
{
	bool bReturn = true;
	return bReturn;
}

bool sspPlayManager::initialize(sspDomainData& data)
{
	auto timelines = data.getTimelines();
	if (timelines.empty())
		return false;

	start_messages_ = data.getStartList();
	trigger_messages_ = data.getTriggerList();
	clock_messages_ = data.getClockList();

	updater_.setInterval(sspResetManager::watchdog_timeout_s);

	osc_console_.connectAll();
	osc_console_.clearChannels();

	if (not midi_console_.openDevices())
		return false;

	root_stream_ = timelines[0];
	for (auto& timeline : timelines) {
		if (auto audio = std::dynamic_pointer_cast<sspAudioStream>(timeline)) {
			unsigned int num_channels = audio->getMaxActive() + 1;	// Add an extra channel for transitions
			auto bus = std::make_unique<sspStreamBus>(std::move(osc_console_.getBusChannels(num_channels)));
			audio->setBus(std::move(bus));
		}
		else if (auto stream = std::dynamic_pointer_cast<sspStream>(timeline)) {
			stream->setSendChannel(midi_console_.getSendChannel());
		}
	}

	return true;
}

bool sspPlayManager::start()
{
	if (!sspExecutionState::Instance().isPlaying()) {
		// TODO: Input manager
		sspExecutionState::Instance().playing();
		sspScheduler::Instance().enableTasks();
		osc_console_.initializeChannels();
		previous_time_ = steady_clock::now();
		if (auto ptr = root_stream_.lock()) ptr->start();
		trigger_messages_->reset();
		clock_messages_->reset();
		start_messages_->send();
		updater_.initialize();
	}
	return sspExecutionState::Instance().isPlaying();
}

bool sspPlayManager::update()
{
	if (sspExecutionState::Instance().isPlaying()) {
		clock_messages_->testAndSend();
		trigger_messages_->testAndSend();

		auto now = steady_clock::now();
		std::chrono::duration<double> diff = steady_clock::now() - previous_time_;
		previous_time_ = now;
		auto ptr = root_stream_.lock();
		if (ptr) ptr->update(diff.count());
		return ((ptr && !ptr->empty()) || !sspScheduler::Instance().empty());
	}
	else 
		return false;
}

void sspPlayManager::stop()
{
	if (sspExecutionState::Instance().isPlaying()) {
		if (auto ptr = root_stream_.lock()) ptr->stop();
		sspScheduler::Instance().disableTasks();

		sspExecutionState::Instance().playing(false);
	}
}

void sspPlayManager::terminate()
{
	stop();
	midi_console_.closeDevices();

	if (auto ptr = root_stream_.lock()) ptr->terminate();
	osc_console_.disconnectAll();
}

bool sspPlayManager::verifyPlaying()
{
	return (sspExecutionState::Instance().isPlaying() && updater_.update()) ? osc_console_.verifyPlaying() : true;
}
