/*
  ==============================================================================

    sspOscSendChannel.h
    Created: 8 Mar 2019 5:19:12pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "sspSendChannel.h"
#include "sspOSCSender.h"

class sspOscSendChannel : public sspSendChannel, private sspOscSender
{
public:
	sspOscSendChannel() = default;
	sspOscSendChannel(const sspOscSendChannel& obj) = delete;
	sspOscSendChannel& operator= (const sspOscSendChannel& obj) = delete;
	virtual ~sspOscSendChannel() {}

	virtual void sendMessage(std::string address, std::vector<ArgumentType> arguments = std::vector<ArgumentType>()) override;
};
