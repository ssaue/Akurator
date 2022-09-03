/*
  ==============================================================================

    sspTriggerMsgList.h
    Created: 25 Jan 2019 4:32:38pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspConditionalMsgList.h"
#include "domain/elements/conditionals/sspTrigger.h"

class sspTriggerMsgList
{
	using TrigMsg = std::pair<std::weak_ptr<sspTrigger>, std::shared_ptr<sspConditionalMsgList>>;
	std::list<TrigMsg> messages_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_NVP(messages_);
	}

public:
	sspTriggerMsgList();
	sspTriggerMsgList(const sspTriggerMsgList& obj) = delete;
	sspTriggerMsgList& operator= (const sspTriggerMsgList& obj) = delete;
	virtual ~sspTriggerMsgList() {}

	bool verify(int& nErrors, int& nWarnings) const;

	void add(std::weak_ptr<sspTrigger> cond, std::shared_ptr<sspConditionalMsgList> message);
	void remove(std::weak_ptr<sspTrigger> cond);
	void removeAll();

	void reset();
	void testAndSend() const;
};

