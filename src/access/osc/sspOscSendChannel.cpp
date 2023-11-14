/*
  ==============================================================================

    sspOscSendChannel.cpp
    Created: 8 Mar 2019 5:19:12pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "sspOscSendChannel.h"

using namespace juce;

namespace {
	// Overload trick for visitors
	template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
	template<class... Ts> overloaded(Ts...)->overloaded<Ts...>;
}

void sspOscSendChannel::sendMessage(std::string address, std::vector<ArgumentType> arguments)
{
	OSCAddressPattern pattern(address);
	OSCMessage message(pattern);
	message.addInt32(getBusID());	// Always add the bus ID when sending messages
	message.addInt32(getChannelID());	// Always add the channel ID when sending messages
	for (auto&& arg : arguments) {
		std::visit(overloaded {
			[&message](int i) { message.addInt32(i); },
			[&message](double f) { message.addFloat32(static_cast<float>(f)); },
			[&message](const std::string& str) { message.addString(String(str)); },
		}, arg);
	}

	sspOscSender::send(message);
}

void sspOscSendChannel::stop()
{
	sendMessage("/stop");
}
