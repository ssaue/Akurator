/*
  ==============================================================================

    sspOscConsole.cpp
    Created: 28 Mar 2019 11:07:16pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "sspOscConsole.h"
#include "sspOscConsoleImpl.h"

std::string sspOscConsole::send_address_s = "127.0.0.1";
int sspOscConsole::send_port_s = 8001;
int sspOscConsole::receive_port_s = 9001;

sspOscConsole::sspOscConsole() : impl_(std::make_unique<sspOscConsoleImpl>())
{
}

sspOscConsole::~sspOscConsole()
{
}

void sspOscConsole::connectAll()
{
	impl_->connectAll();
}

void sspOscConsole::disconnectAll()
{
	impl_->disconnectAll();
}

void sspOscConsole::initializeChannels()
{
	impl_->initializeChannels();
}

bool sspOscConsole::isSendConnected() const { return impl_->isSendConnected(); }
bool sspOscConsole::isReceiveConnected() const { return impl_->isReceiveConnected(); }
bool sspOscConsole::verifyPlaying() { return impl_->verifyPlaying(); }

std::map<unsigned int, std::shared_ptr<sspSendChannel>> sspOscConsole::getBusChannels(unsigned int num)
{
	return std::move(impl_->getBusChannels(num));
}

void sspOscConsole::clearChannels()
{ 
	impl_->clearChannels();
}
