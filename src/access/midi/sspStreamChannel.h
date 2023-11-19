/*
  ==============================================================================

    sspStreamChannel.h
    Created: 8 Mar 2019 5:19:12pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

#include "engine/sspSendChannel.h"

class sspStreamChannel : public sspSendChannel
{
public:
	sspStreamChannel() = default;
	sspStreamChannel(const sspStreamChannel& obj) = delete;
	sspStreamChannel& operator= (const sspStreamChannel& obj) = delete;
	virtual ~sspStreamChannel() {}

	void sendMessage(std::string address, std::vector<ArgumentType> arguments = std::vector<ArgumentType>()) override {}
	bool play(const std::string&, double) final;
	void stop() override;
};
