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
	: channels_(channels), responder_()
{
}

sspStreamBus::~sspStreamBus() 
{
}

bool sspStreamBus::play(std::weak_ptr<sspPlayTask> task, std::weak_ptr<sspPlayTask> old_task)
{
	if (auto ptr = task.lock()) {
		for (auto& chan : channels_) {
			if (!chan.second->busy()) {
				if (auto old_ptr = old_task.lock()) {	// Need to fade out old buffer first
					bufferFadeOut(old_ptr->getID(), fadeout_time_s);
					bufferVolume(chan.first, 0.0);
				}
				bufferVolume(chan.first, ptr->getVolumeFactor()->getValue(), fadein_time_s);
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
			chan.second->sendMessage("buffer/stop", std::vector<sspSendChannel::ArgumentType>());
		}
	}
}

void sspStreamBus::masterVolume(double vol, double time, Reference ref)
{
	std::string chan_addr = "master/vol/";
	chan_addr += (ref == Reference::Absolute ? "abs" : "rel");
	std::vector<sspSendChannel::ArgumentType> args;
	args.push_back(vol);
	args.push_back(time);

	for (auto& chan : channels_) {
		chan.second->sendMessage(chan_addr, args);
	}
}

void sspStreamBus::masterFadeIn(double time)
{
	std::string chan_addr = "master/fadein/";
	std::vector<sspSendChannel::ArgumentType> args;
	args.push_back(time);

	for (auto& chan : channels_) {
		chan.second->sendMessage(chan_addr, args);
	}
}

void sspStreamBus::masterFadeOut(double time)
{
	std::string chan_addr = "master/fadeout/";
	std::vector<sspSendChannel::ArgumentType> args;
	args.push_back(time);

	for (auto& chan : channels_) {
		chan.second->sendMessage(chan_addr, args);
	}
}

bool sspStreamBus::bufferVolume(unsigned int channel_id, double vol, double time, Reference ref)
{
	auto channel = channels_.find(channel_id);
	if (channel != channels_.end()) {
		std::string chan_addr = "buffer/vol/";
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

bool sspStreamBus::bufferFadeIn(unsigned int channel_id, double time)
{
	auto channel = channels_.find(channel_id);
	if (channel != channels_.end()) {
		std::string chan_addr = "buffer/fadein/";
		std::vector<sspSendChannel::ArgumentType> args;
		args.push_back(time);
		channel->second->sendMessage(chan_addr, args);
		return true;
	}
	else {
		return false;
	}
}

bool sspStreamBus::bufferFadeOut(unsigned int channel_id, double time)
{
	auto channel = channels_.find(channel_id);
	if (channel != channels_.end()) {
		std::string chan_addr = "buffer/fadeout/";
		std::vector<sspSendChannel::ArgumentType> args;
		args.push_back(time);
		channel->second->sendMessage(chan_addr, args);
		return true;
	}
	else {
		return false;
	}
}

void sspStreamBus::bufferSolo(unsigned int channel_id, double time)
{
	for (auto& chan : channels_) {
		if (chan.first == channel_id) {
			bufferFadeIn(chan.first, time);
		}
		else {
			bufferFadeOut(chan.first, time);
		}
	}
}

void sspStreamBus::bufferUnSolo(unsigned int channel_id, double time)
{
	for (auto& chan : channels_) {
		if (chan.first != channel_id) {
			bufferFadeIn(chan.first, time);
		}
	}
}

