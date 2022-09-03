/*
  ==============================================================================

    sspPlayManager.h
    Created: 31 Mar 2019 7:12:48pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

#include "domain/elements/messages/sspConditionalMsgList.h"
#include "domain/elements/messages/sspTriggerMsgList.h"
#include "domain/elements/messages/sspTimeTriggerMsgList.h"

#include "access/osc/sspOscConsole.h"
#include "domain/sspDomainData.h"
#include "sspTimeUpdater.h"

#include <chrono>

class sspTimeline;

class sspPlayManager
{
	sspConditionalMsgList	start_messages_;
	sspTriggerMsgList		trigger_messages_;
	sspTimeTriggerMsgList	clock_messages_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_NVP(start_messages_);
		ar & BOOST_SERIALIZATION_NVP(trigger_messages_);
		ar & BOOST_SERIALIZATION_NVP(clock_messages_);
	}

public:
	sspPlayManager() = default;
	sspPlayManager(const sspPlayManager&) = delete;
	sspPlayManager& operator=(const sspPlayManager&) = delete;
	~sspPlayManager();

	bool verify(int& nErrors, int& nWarnings) const;

	bool initialize(sspDomainPool<sspTimeline>& timelines);
	bool start();
	bool update();
	void stop();
	void terminate();
	void clearContents();

	bool verifyPlaying();

	sspConditionalMsgList&	getStartList() { return start_messages_; }
	sspTriggerMsgList&		getTriggerList() { return trigger_messages_; }
	sspTimeTriggerMsgList&  getClockList() { return clock_messages_; }

private:
	sspOscConsole osc_console_;
	std::weak_ptr<sspTimeline> root_stream_;
	std::chrono::steady_clock::time_point previous_time_;
	sspTimeUpdater updater_;
};

