/*
  ==============================================================================

    OscChannelComponent.cpp
    Created: 8 Mar 2019 5:19:12pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "OscChannelComponent.h"

namespace {
	// Overload trick for visitors
	template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
	template<class... Ts> overloaded(Ts...)->overloaded<Ts...>;
}

void OscChannelComponent::initialize(std::weak_ptr<OSCSender> sender, int id)
{
	sender = sender;
	setID(id);
}


void OscChannelComponent::sendMessage(std::string address, std::vector<ArgumentType> arguments)
{
	OSCAddressPattern pattern(address);
	OSCMessage message(pattern);
	message.addInt32(getID());	// Always add the channel ID when sending messages
	for (auto&& arg : arguments) {
		std::visit(overloaded {
			[&message](int i) { message.addInt32(i); },
			[&message](float f) { message.addFloat32(f); },
			[&message](const std::string& str) { message.addString(String(str)); },
		}, arg);
	}
	if (auto sender = sender_.lock())
		sender->send(message);
}
