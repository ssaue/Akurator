/*
  ==============================================================================

    sspOscConsoleImpl.cpp
    Created: 02 Sep 2022
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "sspOscConsole.h"
#include "sspOscConsoleImpl.h"
#include "sspOSCSender.h"
#include "sspOscSendChannel.h"

using namespace juce;

sspOscConsoleImpl::sspOscConsoleImpl() : channels_()
{
	addListener(this);
}

sspOscConsoleImpl::~sspOscConsoleImpl()
{
	removeListener(this);
	disconnectAll();
}

void sspOscConsoleImpl::connectAll()
{
	receive_ready_ = OSCReceiver::connect(sspOscConsole::receive_port_s);
	send_ready_ = sspOscSender::connect(sspOscConsole::send_address_s, sspOscConsole::send_port_s);
}

void sspOscConsoleImpl::disconnectAll()
{
	sspOscSender::disconnect();
	OSCReceiver::disconnect();
}

void sspOscConsoleImpl::initializeChannels()
{
	OSCAddressPattern pattern("/init");
	OSCMessage message(pattern);
	message.addInt32(static_cast<int>(channels_.size()));		// Number of channels are sent as parameter
	sspOscSender::send(message);
}

std::map<unsigned int, std::shared_ptr<sspSendChannel>> sspOscConsoleImpl::getBusChannels(unsigned int num)
{
	std::map<unsigned int, std::shared_ptr<sspSendChannel>> bus_channels;

	unsigned int id = static_cast<unsigned int>(channels_.size());
	for (unsigned int i = 0; i < num; ++i) {
		auto channel = std::make_shared<sspOscSendChannel>();
		channel->setBusID(buses_);
		channel->setChannelID(id + i);
		channels_.push_back(channel);
		bus_channels[id + i] = channel;
	}
	buses_++;
	
	return std::move(bus_channels);
}

void sspOscConsoleImpl::clearChannels()
{ 
	channels_.clear();
	buses_ = 0;
}

void sspOscConsoleImpl::oscMessageReceived(const OSCMessage & message)
{
	static float old_amp = 0.0f;
	const OSCAddressPattern& address = message.getAddressPattern();
	if (address == amplitude_) {
		if (message.size() == 1 && message[0].isFloat32()) {
			auto amp = message[0].getFloat32();
			if (amp != old_amp) amp_change_ = true;
			old_amp = amp;
		}
	}
	else if (address == finished_) {
		if (message.size() == 1 && message[0].isInt32()) {
			auto channel = message[0].getInt32();
			if (channel < channels_.size()) {
				channels_[channel]->setFinished();
			}
		}
	}
}
