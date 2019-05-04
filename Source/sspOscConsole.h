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

#include <vector>
#include <map>

class sspOscConsole : private OSCReceiver, private OSCReceiver::ListenerWithOSCAddress<OSCReceiver::MessageLoopCallback>
{
public:
	static String	send_address_s;
	static int		send_port_s;
	static int		receive_port_s;

	sspOscConsole();
	sspOscConsole(const sspOscConsole& obj) = delete;
	sspOscConsole& operator= (const sspOscConsole& obj) = delete;
	virtual ~sspOscConsole();

	void connectAll();
	void disconnectAll();
	bool isSendConnected() const { return send_ready_; }
	bool isReceiveConnected() const { return receive_ready_; }

	std::map<unsigned int, std::shared_ptr<sspSendChannel>> getBusChannels(unsigned int num);
	void clearChannels() { channels_.clear(); }

private:
	virtual void oscMessageReceived(const OSCMessage& message) override;

	std::vector<std::shared_ptr<sspSendChannel>> channels_;
	bool send_ready_ = false;
	bool receive_ready_ = false;
};
