/*
  ==============================================================================

    sspTaskChannel.h
    Created: 25 Feb 2019 11:25:06pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspFinishedResponder.h"

#include <variant>
#include <string>
#include <vector>

class sspTaskChannel
{
public:
	using ArgumentType = std::variant<int, float, std::string>;

	sspTaskChannel() = default;
	sspTaskChannel(const sspTaskChannel& obj) = delete;
	sspTaskChannel& operator= (const sspTaskChannel& obj) = delete;
	virtual ~sspTaskChannel() {}

	virtual void sendMessage(std::string address, std::vector<ArgumentType> arguments = std::vector<ArgumentType>()) = 0;
	void setResponder(std::weak_ptr<sspFinishedResponder> responder) { responder_ = responder; }

	void setID(int value) { id_ = value; }
	int  getID() const { return id_; }

private:
	int id_;
	std::weak_ptr<sspFinishedResponder> responder_;
};