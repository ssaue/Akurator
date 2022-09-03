/*
  ==============================================================================

    sspOscSender.cpp
    Created: 14 Mar 2019 10:14:59pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "sspOscSender.h"

using namespace juce;

std::unique_ptr<OSCSender> sspOscSender::sender_;
std::mutex sspOscSender::send_lock_;

bool sspOscSender::connect(const String & address, const int port)
{
	std::scoped_lock<std::mutex> lck{ send_lock_ };
	if (!sender_) {
		sender_ = std::make_unique<OSCSender>();
	}
	return sender_->connect(address, port);
}

void sspOscSender::disconnect()
{
	std::scoped_lock<std::mutex> lck{ send_lock_ };
	if (sender_) {
		sender_->disconnect();
		sender_.reset();
	}
}

void sspOscSender::send(const OSCMessage & msg)
{
	std::scoped_lock<std::mutex> lck{ send_lock_ };
	sender_->send(msg);
}
