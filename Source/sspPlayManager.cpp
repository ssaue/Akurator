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
