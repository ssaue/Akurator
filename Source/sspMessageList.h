/*
  ==============================================================================

    sspMessageList.h
    Created: 24 Jan 2019 5:14:40pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspMessageWithReceiver.h"

#include <list>
#include <boost/serialization/list.hpp>
#include <boost/serialization/unique_ptr.hpp>

class sspMessageList
{
	std::list<std::unique_ptr<sspMessageWithReceiver>> messages_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_NVP(messages_);
	}

public:
	sspMessageList();
	sspMessageList(const sspMessageList& obj) = delete;
	sspMessageList& operator= (const sspMessageList& obj) = delete;
	virtual ~sspMessageList() {}

	bool verify(int& nErrors, int& nWarnings) const;

	void add(std::unique_ptr<sspMessageWithReceiver> message);
	void remove(std::unique_ptr<sspMessageWithReceiver> message);
	void removeAll();

	void send() const;
};

