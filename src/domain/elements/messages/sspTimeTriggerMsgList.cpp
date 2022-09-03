/*
  ==============================================================================

    sspTimeTriggerMsgList.cpp
    Created: 25 Jan 2019 4:32:59pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspTimeTriggerMsgList.h"
#include "access/sspLogging.h"

sspTimeTriggerMsgList::sspTimeTriggerMsgList()
	: messages_()
{
}

  bool sspTimeTriggerMsgList::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	for (auto&& msg : messages_) {
		if (!msg.second->verify(nErrors, nWarnings)) {
			bReturn = false;
		}
	}

	if (!bReturn) {
		BOOST_LOG_TRIVIAL(info) << "Error found in time trigger message list";
	}

	return bReturn;
}

void sspTimeTriggerMsgList::add(const boost::posix_time::time_duration & clock, std::shared_ptr<sspConditionalMsgList> message)
{
	remove(clock);
	messages_[clock] = message;
}

void sspTimeTriggerMsgList::remove(const boost::posix_time::time_duration & clock)
{
	auto iter = messages_.find(clock);
	if (iter != messages_.end()) {
		if (iter == pos_) pos_ = messages_.cend();
		messages_.erase(iter);
	}
}

void sspTimeTriggerMsgList::removeAll()
{
	messages_.clear();
	pos_ = messages_.cend();
}

void sspTimeTriggerMsgList::reset()
{
	auto now = boost::posix_time::second_clock::local_time().time_of_day();
	for (pos_ = messages_.cbegin(); pos_ != messages_.cend(); ++pos_) {
		if (pos_->first > now) break;
	}
}

void sspTimeTriggerMsgList::testAndSend() const
{
	auto now = boost::posix_time::second_clock::local_time().time_of_day();
	if (!messages_.empty() && pos_ == messages_.cend() && now < messages_.cbegin()->first) {
		pos_ = messages_.cbegin();
	}
	for (; pos_ != messages_.cend(); ++pos_) {
		if (pos_->first < now) {
			pos_->second->send();
		}
		else {
			break;
		}
	}
}
