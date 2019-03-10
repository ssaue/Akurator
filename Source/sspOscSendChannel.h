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

class sspOscSendChannel : public sspSendChannel
{
public:
	sspOscSendChannel() = default;
	sspOscSendChannel(const sspOscSendChannel& obj) = delete;
	sspOscSendChannel& operator= (const sspOscSendChannel& obj) = delete;
	virtual ~sspOscSendChannel() {}

	virtual void initialize(std::weak_ptr<OSCSender> sender, int id);
	virtual void sendMessage(std::string address, std::vector<ArgumentType> arguments = std::vector<ArgumentType>()) override;

private:
	std::weak_ptr<OSCSender> sender_;
};
