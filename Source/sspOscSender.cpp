/*
  ==============================================================================

    sspOscSender.cpp
    Created: 14 Mar 2019 10:14:59pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "sspOscSender.h"

std::unique_ptr<OSCSender> sspOscSender::sender_ = std::make_unique<OSCSender>();
std::mutex sspOscSender::send_lock_;

void sspOscSender::connect(const String & address, const int port)
{
	std::scoped_lock<std::mutex> lck{ send_lock_ };
	if (!sender_) {
		sender_ = std::make_unique<OSCSender>();
	}
	sender_->connect(address, port);
}

void sspOscSender::send(const OSCMessage & msg)
{
	std::scoped_lock<std::mutex> lck{ send_lock_ };
	sender_->send(msg);
}
