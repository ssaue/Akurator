/*
  ==============================================================================

    OscChannelComponent.h
    Created: 8 Mar 2019 5:19:12pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "sspTaskChannel.h"

class OscChannelComponent : public sspTaskChannel
{
public:
	OscChannelComponent() = default;
	OscChannelComponent(const OscChannelComponent& obj) = delete;
	OscChannelComponent& operator= (const OscChannelComponent& obj) = delete;
	virtual ~OscChannelComponent() {}

	virtual void initialize(std::weak_ptr<OSCSender> sender, int id);
	virtual void sendMessage(std::string address, std::vector<ArgumentType> arguments = std::vector<ArgumentType>()) override;

private:
	std::weak_ptr<OSCSender> sender_;
};
