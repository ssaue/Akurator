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

class sspPlayTask;
class sspFinishedResponder;
class sspSendChannel;

class sspStreamBus
{
public:
	static double fadein_time_s, fadeout_time_s;

	sspStreamBus(const std::map<unsigned int, std::shared_ptr<sspSendChannel>>& channels);
	virtual ~sspStreamBus();	// Ensure abstract class

	void setResponder(std::weak_ptr<sspFinishedResponder> responder) { responder_ = responder; }
	bool play(std::weak_ptr<sspPlayTask> task, std::weak_ptr<sspPlayTask> old_task);
	void stop();

	enum class Reference : unsigned int { Relative, Absolute };

	void masterVolume(double vol, double time = 0.0, Reference ref = Reference::Absolute);
	void masterFadeIn(double time);
	void masterFadeOut(double time);
	
	// Figure out how to address the correct buffer later
	bool bufferVolume(unsigned int channel_id, double vol, double time = 0.0, Reference ref = Reference::Absolute);
	bool bufferFadeIn(unsigned int channel_id, double time);
	bool bufferFadeOut(unsigned int channel_id, double time);
	void bufferSolo(unsigned int channel_id, double time);
	void bufferUnSolo(unsigned int channel_id, double time);

private:
	std::map<unsigned int, std::shared_ptr<sspSendChannel>> channels_;
	std::weak_ptr<sspFinishedResponder> responder_;
};

