/*
  ==============================================================================

    sspOscConsole.cpp
    Created: 28 Mar 2019 11:07:16pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "sspOscConsole.h"
#include "sspOSCSender.h"
#include "sspOscSendChannel.h"

String sspOscConsole::send_address_s = "127.0.0.1";
int sspOscConsole::send_port_s = 8001;
int sspOscConsole::receive_port_s = 9001;

sspOscConsole::sspOscConsole() : channels_()
{
	addListener(this);
}

sspOscConsole::~sspOscConsole()
{
	removeListener(this);
	disconnectAll();
}

void sspOscConsole::connectAll()
{
	receive_ready_ = connect(receive_port_s);
	send_ready_ = sspOscSender::connect(send_address_s, send_port_s);
}

void sspOscConsole::disconnectAll()
{
	sspOscSender::disconnect();
	disconnect();
}

std::map<unsigned int, std::shared_ptr<sspSendChannel>> sspOscConsole::getBusChannels(unsigned int num)
{
	std::map<unsigned int, std::shared_ptr<sspSendChannel>> bus_channels;

	unsigned int id = static_cast<unsigned int>(channels_.size());
	for (unsigned int i = 0; i < num; ++i) {
		channels_.push_back(std::make_shared<sspOscSendChannel>());
		channels_.back()->setID(id+i);
		bus_channels[id + i] = channels_.back();
	}
	
	return std::move(bus_channels);
}

void sspOscConsole::oscMessageReceived(const OSCMessage & message)
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
