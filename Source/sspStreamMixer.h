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
	sspStreamMixer(std::weak_ptr<sspFinishedResponder> responder);

public:
	virtual ~sspStreamMixer() = 0;	// Ensure abstract class

	bool start(std::weak_ptr<sspPlayTask> task, float time = 0.0f);	// Allowing fade in
	void stop();

	enum class Reference : unsigned int { Relative, Absolute };

	bool masterVolume(float vol, float time = 0.0, Reference ref = Reference::Absolute);
	bool masterFadeIn(float time);
	bool masterFadeOut(float time);
	
	// Figure out how to address the correct buffer later
	bool bufferVolume(int channel_id, float vol, float time = 0.0f, Reference ref = Reference::Absolute);
	bool bufferFadeIn(int channel_id, float time);
	bool bufferFadeOut(int channel_id, float time);
	void bufferSolo(int channel_id, float time);
	void bufferUnSolo(int channel_id, float time);

protected:
	std::vector<std::shared_ptr<sspSendChannel>> channels_;	// channel 0 is the master channel

private:
	std::mutex lock_;
	std::weak_ptr<sspFinishedResponder> responder_;
};

