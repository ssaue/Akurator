/*
  ==============================================================================

    sspConditionalMsgList.h
    Created: 24 Jan 2019 5:35:24pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspMessageList.h"
#include <boost/serialization/utility.hpp>

class sspConditionalMsgList
{
	using CondMsg = std::pair<std::shared_ptr<sspConditional>, std::shared_ptr<sspMessageList>>;
	std::list<CondMsg> messages_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(messages_);
	}

public:
	sspConditionalMsgList();
	sspConditionalMsgList(const sspConditionalMsgList& obj) = delete;
	sspConditionalMsgList& operator= (const sspConditionalMsgList& obj) = delete;
	virtual ~sspConditionalMsgList() {}

	bool verify(int& nErrors, int& nWarnings) const;

	void add(std::shared_ptr<sspConditional> cond, std::shared_ptr<sspMessageList> message);
	void remove(std::shared_ptr<sspConditional> cond);
	void removeAll();

	size_t  size() { return messages_.size(); }
	bool	empty() { return messages_.empty(); }

	void send() const;
};

