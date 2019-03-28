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
	void setResponder(std::weak_ptr<sspFinishedResponder> responder) { responder_ = responder; }
	void setFinished() { if (auto ptr = responder_.lock()) { ptr->onFinished(); } }

	bool busy() { return !responder_.expired(); }

	void setID(int value) { id_ = value; }
	int  getID() const { return id_; }

private:
	int id_;
	std::weak_ptr<sspFinishedResponder> responder_;
};