/*
  ==============================================================================

    sspSendChannel.h
    Created: 25 Feb 2019 11:25:06pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspFinishedResponder.h"

#include <variant>
#include <string>
#include <vector>

class sspSendChannel
{
public:
	using ArgumentType = std::variant<int, double, std::string>;

	sspSendChannel() = default;
	sspSendChannel(const sspSendChannel& obj) = delete;
	sspSendChannel& operator= (const sspSendChannel& obj) = delete;
	virtual ~sspSendChannel() {}

	virtual void sendMessage(std::string address, std::vector<ArgumentType> arguments = std::vector<ArgumentType>()) = 0;
	virtual bool play(const std::string& file_path, double tempo_fac) = 0;
	virtual void stop() = 0;

	void setResponder(std::weak_ptr<sspFinishedResponder> responder) { responder_ = responder; }
	void clearResponder() { responder_.reset(); }
	void setFinished() { if (auto ptr = responder_.lock()) { ptr->onFinished(); } }

	bool assigned() const { return assigned_; }
	bool busy() const { return !responder_.expired(); }

	void setChannelID(int value) { channel_id_ = value; }
	int  getChannelID() const { return channel_id_; }

	void setBusID(int value) { bus_id_ = value; }
	int  getBusID() const { return bus_id_; }

	void setAssigned(bool yes) { assigned_ = yes; }

private:
	int channel_id_ = 0;
	int bus_id_ = 0;
	bool assigned_ = false;
	std::weak_ptr<sspFinishedResponder> responder_;
};