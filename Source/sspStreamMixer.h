/*
  ==============================================================================

    sspStreamMixer.h
    Created: 25 Feb 2019 11:25:21pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include <memory>
#include <vector>
#include <mutex>

class sspPlayTask;
class sspFinishedResponder;
class sspSendChannel;

class sspStreamMixer
{
protected:
	sspStreamMixer(const std::vector<std::shared_ptr<sspSendChannel>>& channels, std::weak_ptr<sspFinishedResponder> responder);

public:
	virtual ~sspStreamMixer() = 0;	// Ensure abstract class

	bool start(std::weak_ptr<sspPlayTask> task, double time = 0.0f);	// Allowing fade in
	void stop();

	enum class Reference : unsigned int { Relative, Absolute };

	bool masterVolume(double vol, double time = 0.0, Reference ref = Reference::Absolute);
	bool masterFadeIn(double time);
	bool masterFadeOut(double time);
	
	// Figure out how to address the correct buffer later
	bool bufferVolume(int channel_id, double vol, double time = 0.0, Reference ref = Reference::Absolute);
	bool bufferFadeIn(int channel_id, double time);
	bool bufferFadeOut(int channel_id, double time);
	void bufferSolo(int channel_id, double time);
	void bufferUnSolo(int channel_id, double time);

private:
	std::vector<std::shared_ptr<sspSendChannel>> channels_;	// channel 0 is the master channel
	std::weak_ptr<sspFinishedResponder> responder_;
	std::mutex lock_;
};

