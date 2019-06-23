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
#include "sspSharedVector.h"

#include <vector>
#include <map>
#include <atomic>

class sspOscConsole : private OSCReceiver, private OSCReceiver::Listener<OSCReceiver::MessageLoopCallback>
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
	bool verifyPlaying() { return amp_change_.exchange(false); }

	std::map<unsigned int, std::shared_ptr<sspSendChannel>> getBusChannels(unsigned int num);
	void clearChannels() { channels_.clear(); }

private:
	virtual void oscMessageReceived(const OSCMessage& message) override;

	sspSharedVector<sspSendChannel> channels_;
	bool send_ready_ = false;
	bool receive_ready_ = false;
	std::atomic_bool amp_change_ = false;

	// The two address patterns handled by sspOscConsole
	const OSCAddressPattern finished_ = OSCAddressPattern("/finished");
	const OSCAddressPattern amplitude_ = OSCAddressPattern("/amp");
};
