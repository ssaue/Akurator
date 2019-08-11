/*
  ==============================================================================

    sspOSCSender.h
    Created: 14 Mar 2019 9:17:05pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <mutex>

class sspOscSender
{
protected:
	static bool connect(const String& address, const int port);
	static void disconnect();
	static void send(const OSCMessage& msg);

	sspOscSender() = default;
	sspOscSender(const sspOscSender& obj) = delete;
	sspOscSender& operator= (const sspOscSender& obj) = delete;
	virtual ~sspOscSender() {}

private:
	static std::unique_ptr<OSCSender> sender_;
	static std::mutex send_lock_;
};
