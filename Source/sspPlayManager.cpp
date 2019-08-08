/*
  ==============================================================================

    sspPlayManager.cpp
    Created: 31 Mar 2019 7:12:48pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "sspPlayManager.h"
#include "sspAudioStream.h"
#include "sspStreamBus.h"
#include "sspExecutionState.h"
#include "sspScheduler.h"
#include "sspResetManager.h"

using namespace std::chrono;

sspPlayManager::~sspPlayManager()
{
	clearContents();
}

bool sspPlayManager::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;
	if (!start_messages_.verify(nErrors, nWarnings))
		bReturn = false;
	if (!trigger_messages_.verify(nErrors, nWarnings))
		bReturn = false;
	if (!clock_messages_.verify(nErrors, nWarnings))
		bReturn = false;
	return bReturn;
}

bool sspPlayManager::initialize(sspDomainPool<sspTimeline>& timelines)
{
	// Initialize the root timeline and add OSC-channels to the audio streams
	if (timelines.empty())
		return false;

	updater_.setInterval(sspResetManager::watchdog_timeout_s);

	osc_console_.connectAll();
	osc_console_.clearChannels();

	root_stream_ = timelines[0];
	for (auto& stream : timelines) {
		auto audio = std::dynamic_pointer_cast<sspAudioStream>(stream);
		if (audio) {
			unsigned int num_channels = audio->getMaxActive() + 1;	// Add an extra channel for transitions
			auto bus = std::make_unique<sspStreamBus>(std::move(osc_console_.getBusChannels(num_channels)));
			audio->setBus(std::move(bus));
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
		osc_console_.initializeMixer();
		previous_time_ = steady_clock::now();
		if (auto ptr = root_stream_.lock()) ptr->start();
		trigger_messages_.reset();
		clock_messages_.reset();
		start_messages_.send();
		updater_.initialize();
	}
	return sspExecutionState::Instance().isPlaying();
}

bool sspPlayManager::update()
{
	if (sspExecutionState::Instance().isPlaying()) {
		clock_messages_.testAndSend();
		trigger_messages_.testAndSend();

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
	if (auto ptr = root_stream_.lock()) ptr->terminate();
	osc_console_.disconnectAll();
}

void sspPlayManager::clearContents()
{
	terminate();
	start_messages_.removeAll();
	trigger_messages_.removeAll();
	clock_messages_.removeAll();
}

bool sspPlayManager::verifyPlaying()
{
	return (sspExecutionState::Instance().isPlaying() && updater_.update()) ? osc_console_.verifyPlaying() : true;
}
