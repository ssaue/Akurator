/*
  ==============================================================================

    sspOSCSender.h
    Created: 14 Mar 2019 9:17:05pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

#include <juce_osc/juce_osc.h>
#include <mutex>

class sspOscSender
{
protected:
	static bool connect(const juce::String& address, const int port);
	static void disconnect();
	static void send(const juce::OSCMessage& msg);

	sspOscSender() = default;
	sspOscSender(const sspOscSender& obj) = delete;
	sspOscSender& operator= (const sspOscSender& obj) = delete;
	virtual ~sspOscSender() {}

private:
	static std::unique_ptr<juce::OSCSender> sender_;
	static std::mutex send_lock_;
};
