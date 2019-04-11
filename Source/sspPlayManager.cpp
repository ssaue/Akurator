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

	osc_console_.clearChannels();

	root_stream_ = timelines.getAt(0);
	for (auto& stream : timelines) {
		auto audio = std::dynamic_pointer_cast<sspAudioStream>(stream);
		if (audio) {
			unsigned int num_channels = audio->getMaxActive();
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
		sspExecutionState::Instance().play();
		previous_time_ = steady_clock::now();
		root_stream_->start();
		trigger_messages_.reset();
		clock_messages_.reset();
		start_messages_.send();
	}
	return sspExecutionState::Instance().isPlaying();
}

bool sspPlayManager::update()
{
	if (sspExecutionState::Instance().isPlaying()) {
		clock_messages_.testAndSend();
		trigger_messages_.testAndSend();

		// TODO: Handling the stream volumes

		auto now = steady_clock::now();
		std::chrono::duration<double> diff = steady_clock::now() - previous_time_;
		root_stream_->update(diff.count());
		previous_time_ = now;
		return (!root_stream_->empty() || !sspScheduler::Instance().empty());
	}
	else 
		return false;
}

void sspPlayManager::stop()
{
	if (sspExecutionState::Instance().isPlaying()) {
		root_stream_->stop();
		// TODO: Stop scheduler
		// TODO: Input manager!
		sspExecutionState::Instance().play(false);
	}
}

void sspPlayManager::terminate()
{
	stop();
	// TODO: Need to terminate streams and stop all running instruments (OSC handling)
	// TODO: Terminate scheduler as well?
}

void sspPlayManager::clearContents()
{
	terminate();
	start_messages_.removeAll();
	trigger_messages_.removeAll();
	clock_messages_.removeAll();
}
