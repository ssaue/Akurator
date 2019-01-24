/*
  ==============================================================================

    sspConditionalMsgList.cpp
    Created: 24 Jan 2019 5:35:24pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspConditionalMsgList.h"
#include "sspLogging.h"

bool sspConditionalMsgList::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	for (auto&& msg : messages_) {
		if (!msg.first) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << "Message list has an invalid conditional";
		}
		if (!msg.second->verify(nErrors, nWarnings)) {
			bReturn = false;
		}
	}

	if (!bReturn) {
		BOOST_LOG_TRIVIAL(info) << "Error found in conditional message list";
	}

	return bReturn;
}

void sspConditionalMsgList::add(std::shared_ptr<sspConditional> cond, std::shared_ptr<sspMessageList> message)
{
	messages_.push_back(std::make_pair(cond, message));
}

void sspConditionalMsgList::remove(std::shared_ptr<sspConditional> cond)
{
	messages_.remove_if([=](CondMsg msg) { return (msg.first == cond); });
}

void sspConditionalMsgList::removeAll()
{
	messages_.clear();
}

void sspConditionalMsgList::send() const
{
	for (auto&& elem : messages_) {
		if (elem.first->isTrue()) {
			elem.second->send();
		}
	}
}
