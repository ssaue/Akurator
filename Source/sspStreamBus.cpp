/*
  ==============================================================================

    sspStreamBus.cpp
    Created: 25 Feb 2019 11:25:21pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspStreamBus.h"
#include "sspSendChannel.h"
#include "sspPlayTask.h"

double sspStreamBus::fadein_time_s = 2.0;
double sspStreamBus::fadeout_time_s = 5.0;
double sspStreamBus::volume_time_s = 1.0;

sspStreamBus::sspStreamBus(const std::map<unsigned int, std::shared_ptr<sspSendChannel>>& channels)
	: channels_(channels), responder_(), lock_()
{
}

sspStreamBus::~sspStreamBus() 
{
}

bool sspStreamBus::play(std::weak_ptr<sspPlayTask> task, std::weak_ptr<sspPlayTask> old_task)
{
	std::scoped_lock<std::mutex> lck{ lock_ };

	if (auto ptr = task.lock()) {
		for (auto& chan : channels_) {
			if (!chan.second->assigned()) {
				if (auto old_ptr = old_task.lock()) {	// Need to fade out old buffer first
					channelFadeOut(old_ptr->getChannelID(), fadeout_time_s);
					channelVolume(chan.first, 0.0);
				}
				if (auto v_ptr = ptr->getVolumeFactor().lock()) {
					channelFadeIn(chan.first, fadein_time_s);	// To compensate for previous fadeout
					channelVolume(chan.first, v_ptr->getValue(), fadein_time_s);
				}
				return (ptr->start(chan.second, responder_));
			}
		}
	}
	return false;
}

void sspStreamBus::stop()
{
	for (auto& chan : channels_) {
		if (chan.second->busy()) {
			chan.second->sendMessage("/stop", std::vector<sspSendChannel::ArgumentType>());
		}
	}
}

void sspStreamBus::busVolume(double vol, double time, Reference ref)
{
	std::string chan_addr = "/bus/vol/";
	chan_addr += (ref == Reference::Absolute ? "abs" : "rel");
	std::vector<sspSendChannel::ArgumentType> args;
	args.push_back(vol);
	args.push_back(time);

	// Use the first channel to send the message
	channels_.cbegin()->second->sendMessage(chan_addr, args);
}

void sspStreamBus::busFadeIn(double time)
{
	std::string chan_addr = "/bus/fadein/";
	std::vector<sspSendChannel::ArgumentType> args;
	args.push_back(time);

	// Use the first channel to send the message
	channels_.cbegin()->second->sendMessage(chan_addr, args);
}

void sspStreamBus::busFadeOut(double time)
{
	std::string chan_addr = "/bus/fadeout/";
	std::vector<sspSendChannel::ArgumentType> args;
	args.push_back(time);

	// Use the first channel to send the message
	channels_.cbegin()->second->sendMessage(chan_addr, args);
}

bool sspStreamBus::channelVolume(unsigned int channel_id, double vol, double time, Reference ref)
{
	auto channel = channels_.find(channel_id);
	if (channel != channels_.end()) {
		std::string chan_addr = "/channel/vol/";
		chan_addr += (ref == Reference::Absolute ? "abs" : "rel");
		std::vector<sspSendChannel::ArgumentType> args;
		args.push_back(vol);
		args.push_back(time);
		channel->second->sendMessage(chan_addr, args);
		return true;
	}
	else {
		return false;
	}
}

bool sspStreamBus::channelFadeIn(unsigned int channel_id, double time)
{
	auto channel = channels_.find(channel_id);
	if (channel != channels_.end()) {
		std::string chan_addr = "/channel/fadein/";
		std::vector<sspSendChannel::ArgumentType> args;
		args.push_back(time);
		channel->second->sendMessage(chan_addr, args);
		return true;
	}
	else {
		return false;
	}
}

bool sspStreamBus::channelFadeOut(unsigned int channel_id, double time)
{
	auto channel = channels_.find(channel_id);
	if (channel != channels_.end()) {
		std::string chan_addr = "/channel/fadeout/";
		std::vector<sspSendChannel::ArgumentType> args;
		args.push_back(time);
		channel->second->sendMessage(chan_addr, args);
		return true;
	}
	else {
		return false;
	}
}

void sspStreamBus::channelSolo(unsigned int channel_id, double time)
{
	for (auto& chan : channels_) {
		if (chan.first == channel_id) {
			channelFadeIn(chan.first, time);
		}
		else {
			channelFadeOut(chan.first, time);
		}
	}
}

void sspStreamBus::channelUnSolo(unsigned int channel_id, double time)
{
	for (auto& chan : channels_) {
		if (chan.first != channel_id) {
			channelFadeIn(chan.first, time);
		}
	}
}

