/*
  ==============================================================================

    sspTriggerMsgList.cpp
    Created: 25 Jan 2019 4:32:38pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspTriggerMsgList.h"
#include "sspTrigger.h"
#include "sspLogging.h"

sspTriggerMsgList::sspTriggerMsgList()
	: messages_()
{
}

bool sspTriggerMsgList::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	for (auto&& msg : messages_) {
		if (!msg.first) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << "Message list has an invalid trigger";
		}
		if (!msg.second->verify(nErrors, nWarnings)) {
			bReturn = false;
		}
	}

	if (!bReturn) {
		BOOST_LOG_TRIVIAL(info) << "Error found in trigger message list";
	}
	
	return bReturn;
}

void sspTriggerMsgList::add(std::shared_ptr<sspTrigger> cond, std::shared_ptr<sspConditionalMsgList> message)
{
	messages_.push_back(std::make_pair(cond, message));
}

void sspTriggerMsgList::remove(std::shared_ptr<sspTrigger> cond)
{
	messages_.remove_if([=](TrigMsg msg) { return (msg.first == cond); });
}

void sspTriggerMsgList::removeAll()
{
	messages_.clear();
}

void sspTriggerMsgList::reset()
{
	for (auto&& msg : messages_) {
		msg.first->reset();
	}
}

void sspTriggerMsgList::testAndSend() const
{
	for (auto& msg : messages_) {
		if (msg.first->isTrue()) msg.second->send();
	}
}
