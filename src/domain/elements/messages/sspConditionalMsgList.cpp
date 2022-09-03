/*
  ==============================================================================

    sspConditionalMsgList.cpp
    Created: 24 Jan 2019 5:35:24pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspConditionalMsgList.h"
#include "access/sspLogging.h"

sspConditionalMsgList::sspConditionalMsgList()
	: messages_()
{
}

bool sspConditionalMsgList::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	for (auto&& msg : messages_) {
		if (msg.first.expired()) {
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

void sspConditionalMsgList::add(std::weak_ptr<sspConditional> cond, std::shared_ptr<sspMessageList> message)
{
	messages_.push_back(std::make_pair(cond, std::move(message)));
}

void sspConditionalMsgList::remove(std::weak_ptr<sspConditional> cond)
{
	auto test_ptr = cond.lock();
	messages_.remove_if([=](CondMsg msg) { auto ptr = msg.first.lock(); return (ptr == test_ptr); });
}

void sspConditionalMsgList::removeAll()
{
	messages_.clear();
}

void sspConditionalMsgList::send() const
{
	for (auto&& elem : messages_) {
		auto ptr = elem.first.lock();
		if (ptr && ptr->isTrue()) {
			elem.second->send();
		}
	}
}
