/*
  ==============================================================================

    sspMessageList.cpp
    Created: 24 Jan 2019 5:14:40pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspMessageList.h"

sspMessageList::sspMessageList()
	: messages_()
{
}

  bool sspMessageList::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	for (auto&& msg : messages_) {
		if (!msg->verify(nErrors, nWarnings)) {
			bReturn = false;
		}
	}

	return bReturn;
}

void sspMessageList::add(std::shared_ptr<sspMessageWithReceiver> message)
{
	messages_.push_back(message);
}

void sspMessageList::remove(std::shared_ptr<sspMessageWithReceiver> message)
{
	messages_.remove(message);
}

void sspMessageList::removeAll()
{
	messages_.clear();
}

void sspMessageList::send() const
{
	for (auto&& msg : messages_) {
		msg->send();
	}
}
