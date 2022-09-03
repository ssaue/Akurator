/*
  ==============================================================================

    sspOscConsoleImpl.h
    Created: 28 Mar 2019 11:07:16pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

#include <juce_osc/juce_osc.h>

#include "engine/sspSendChannel.h"
#include "domain/core/sspSharedVector.h"
#include "sspOSCSender.h"

#include <vector>
#include <map>
#include <atomic>

class sspOscConsoleImpl : private juce::OSCReceiver, private juce::OSCReceiver::Listener<juce::OSCReceiver::MessageLoopCallback>, private sspOscSender
{
public:
	sspOscConsoleImpl();
	sspOscConsoleImpl(const sspOscConsoleImpl& obj) = delete;
	sspOscConsoleImpl& operator= (const sspOscConsoleImpl& obj) = delete;
	virtual ~sspOscConsoleImpl();

	void connectAll();
	void disconnectAll();
	void initializeChannels();

	bool isSendConnected() const { return send_ready_; }
	bool isReceiveConnected() const { return receive_ready_; }
	bool verifyPlaying() { return amp_change_.exchange(false); }

	std::map<unsigned int, std::shared_ptr<sspSendChannel>> getBusChannels(unsigned int num);
	void clearChannels();

private:
	virtual void oscMessageReceived(const juce::OSCMessage& message) override;

	sspSharedVector<sspSendChannel> channels_;
	int buses_ = 0;
	bool send_ready_ = false;
	bool receive_ready_ = false;
	std::atomic_bool amp_change_ = false;

	// The two address patterns handled by sspOscConsoleImpl
	const juce::OSCAddressPattern finished_ = juce::OSCAddressPattern("/finished");
	const juce::OSCAddressPattern amplitude_ = juce::OSCAddressPattern("/amp");
};
