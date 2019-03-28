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
public:
	static bool connect(const String& address, const int port);

protected:
	sspOscSender() = default;
	sspOscSender(const sspOscSender& obj) = delete;
	sspOscSender& operator= (const sspOscSender& obj) = delete;
	virtual ~sspOscSender() {}

	static void send(const OSCMessage& msg);

private:
	static std::unique_ptr<OSCSender> sender_;
	static std::mutex send_lock_;
};
