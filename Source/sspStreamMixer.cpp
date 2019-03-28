/*
  ==============================================================================

    sspStreamMixer.cpp
    Created: 25 Feb 2019 11:25:21pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspStreamMixer.h"
#include "sspSendChannel.h"
#include "sspPlayTask.h"

sspStreamMixer::sspStreamMixer(const std::vector<std::shared_ptr<sspSendChannel>>& channels, std::weak_ptr<sspFinishedResponder> responder)
	: channels_(channels), responder_(responder), lock_()
{
}

sspStreamMixer::~sspStreamMixer() 
{
}

bool sspStreamMixer::start(std::weak_ptr<sspPlayTask> task, double time)
{
	if (auto ptr = task.lock()) {
		std::scoped_lock<std::mutex> lck{ lock_ };
		for (auto& chan : channels_) {
			if (!chan->busy()) {
				double vol = ptr->getVolumeFactor()->getValue();
				if (time > 0.0f) {		// Fade in
					bufferVolume(chan->getID(), vol);
				}
				bufferVolume(chan->getID(), vol, time);
				return (ptr->start(chan, responder_));
			}
		}
	}
	return false;
}

void sspStreamMixer::stop()
{
	std::scoped_lock<std::mutex> lck{ lock_ };
	for (auto& chan : channels_) {
		if (chan->busy()) {
			chan->sendMessage("buffer/stop", std::vector<sspSendChannel::ArgumentType>());
		}
	}
}

bool sspStreamMixer::masterVolume(double vol, double time, Reference ref)
{
	return bufferVolume(0, vol, time, ref);
}

bool sspStreamMixer::masterFadeIn(double time)
{
	return bufferFadeIn(0, time);
}

bool sspStreamMixer::masterFadeOut(double time)
{
	return bufferFadeOut(0, time);
}

bool sspStreamMixer::bufferVolume(int channel_id, double vol, double time, Reference ref)
{
	channel_id %= 10;
	if (channel_id > channels_.size() || !channels_[channel_id])
		return false;

	std::string chan_addr = (channel_id == 0 ? "master" : "buffer");
	std::vector<sspSendChannel::ArgumentType> args;
	args.push_back(vol);
	args.push_back(time);

	if (ref == Reference::Absolute) {
		channels_[channel_id]->sendMessage(chan_addr + "/vol/abs", args);
	}
	else {
		channels_[channel_id]->sendMessage(chan_addr + "/vol/rel", args);
	}
	return true;
}

bool sspStreamMixer::bufferFadeIn(int channel_id, double time)
{
	channel_id %= 10;
	if (channel_id > channels_.size() || !channels_[channel_id])
		return false;

	std::string chan_addr = (channel_id == 0 ? "master" : "buffer");
	std::vector<sspSendChannel::ArgumentType> args;
	args.push_back(time);
	channels_[channel_id]->sendMessage(chan_addr + "/fade/in", args);
	return true;
}

bool sspStreamMixer::bufferFadeOut(int channel_id, double time)
{
	channel_id %= 10;
	if (channel_id > channels_.size() || !channels_[channel_id])
		return false;

	std::string chan_addr = (channel_id == 0 ? "master" : "buffer");
	std::vector<sspSendChannel::ArgumentType> args;
	args.push_back(time);
	channels_[channel_id]->sendMessage(chan_addr + "/fade/out", args);
	return true;
}

void sspStreamMixer::bufferSolo(int channel_id, double time)
{
	channel_id %= 10;

	// Iterate over all buffers except the master (0)
	for (int i = 1; i < channels_.size(); ++i) {
		if (i == channel_id) {
			bufferFadeIn(i, time);
		}
		else {
			bufferFadeOut(i, time);
		}
	}
}

void sspStreamMixer::bufferUnSolo(int channel_id, double time)
{
	channel_id %= 10;

	// Iterate over all buffers except the master (0)
	for (int i = 1; i < channels_.size(); ++i) {
		if (i != channel_id) {
			bufferFadeIn(i, time);
		}
	}
}

