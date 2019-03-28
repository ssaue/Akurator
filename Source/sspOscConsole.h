/*
  ==============================================================================

    sspOscConsole.h
    Created: 28 Mar 2019 11:07:16pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "sspSendChannel.h"

#include <map>

class sspOscConsole : private OSCReceiver, private OSCReceiver::ListenerWithOSCAddress<OSCReceiver::MessageLoopCallback>
{
public:
	static String send_address_s;
	static int send_port_s;
	static int receive_port_s;

	sspOscConsole();
	sspOscConsole(const sspOscConsole& obj) = delete;
	sspOscConsole& operator= (const sspOscConsole& obj) = delete;
	virtual ~sspOscConsole() {}

	bool isSendConnected() const { return send_ready_; }
	bool isReceiveConnected() const { return receive_ready_; }

private:
	void oscMessageReceived(const OSCMessage& message) override;

	std::map<int, std::shared_ptr<sspSendChannel>> channels_;
	bool send_ready_;
	bool receive_ready_;
};
