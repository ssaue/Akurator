/*
  ==============================================================================

    sspTimeTriggerMsgList.h
    Created: 25 Jan 2019 4:32:59pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspConditionalMsgList.h"

#include <map>
#include <boost/serialization/map.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>

class sspTimeTriggerMsgList
{
	using TimeMap = std::map<boost::posix_time::time_duration, std::shared_ptr<sspConditionalMsgList>>;

	TimeMap messages_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_NVP(messages_);
	}

public:
	sspTimeTriggerMsgList();
	sspTimeTriggerMsgList(const sspTimeTriggerMsgList& obj) = delete;
	sspTimeTriggerMsgList& operator= (const sspTimeTriggerMsgList& obj) = delete;
	virtual ~sspTimeTriggerMsgList() {}

	bool verify(int& nErrors, int& nWarnings) const;

	void add(const boost::posix_time::time_duration& clock, std::shared_ptr<sspConditionalMsgList> message);
	void remove(const boost::posix_time::time_duration& clock);
	void removeAll();

	void reset();
	void testAndSend() const;

private:
	mutable TimeMap::const_iterator pos_ = messages_.cend();
};

