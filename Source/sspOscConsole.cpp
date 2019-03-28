/*
  ==============================================================================

    sspOscConsole.cpp
    Created: 28 Mar 2019 11:07:16pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "sspOscConsole.h"
#include "sspOSCSender.h"

String sspOscConsole::send_address_s = "127.0.0.1";
int sspOscConsole::send_port_s = 8001;
int sspOscConsole::receive_port_s = 9001;

sspOscConsole::sspOscConsole() : channels_()
{
	receive_ready_= connect(receive_port_s);
	send_ready_ = sspOscSender::connect(send_address_s, send_port_s);
	addListener(this, "/finished");
}

void sspOscConsole::oscMessageReceived(const OSCMessage & message)
{
	if (message.size() == 1 && message[0].isInt32()) {
		auto channel = channels_.find(message[0].getInt32());
		if (channel != channels_.end()) {
			channel->second->setFinished();
		}
	}
}
