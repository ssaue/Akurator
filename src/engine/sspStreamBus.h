/*
  ==============================================================================

    sspStreamBus.h
    Created: 25 Feb 2019 11:25:21pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include <memory>
#include <map>
#include <mutex>

class sspPlayTask;
class sspFinishedResponder;
class sspSendChannel;

class sspStreamBus
{
public:
	static double fadein_time_s;
	static double fadeout_time_s;
	static double volume_time_s;

	sspStreamBus(const std::map<unsigned int, std::shared_ptr<sspSendChannel>>& channels);
	virtual ~sspStreamBus();

	void setResponder(std::weak_ptr<sspFinishedResponder> responder) { responder_ = responder; }
	bool play(std::weak_ptr<sspPlayTask> task, std::weak_ptr<sspPlayTask> old_task);
	void stop();

	enum class Reference : unsigned int { Relative, Absolute };

	void busVolume(double vol, double time, Reference ref = Reference::Absolute);
	void busFadeIn(double time);
	void busFadeOut(double time);
	
	// Figure out how to address the correct buffer later
	bool channelVolume(unsigned int channel_id, double vol, double time = 0.0, Reference ref = Reference::Absolute);
	bool channelFadeIn(unsigned int channel_id, double time);
	bool channelFadeOut(unsigned int channel_id, double time);
	void channelSolo(unsigned int channel_id, double time);
	void channelUnSolo(unsigned int channel_id, double time);

private:
	mutable std::mutex lock_;
	std::map<unsigned int, std::shared_ptr<sspSendChannel>> channels_;
	std::weak_ptr<sspFinishedResponder> responder_;
};

