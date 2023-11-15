/*
  ==============================================================================

    sspPlayManager.h
    Created: 31 Mar 2019 7:12:48pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

#include "access/osc/sspOscConsole.h"
#include "domain/sspDomainData.h"
#include "sspTimeUpdater.h"

#include <chrono>

class sspTimeline;
class sspConditionalMsgList;
class sspTriggerMsgList;
class sspTimeTriggerMsgList;

class sspPlayManager
{
public:
	sspPlayManager() = default;
	sspPlayManager(const sspPlayManager&) = delete;
	sspPlayManager& operator=(const sspPlayManager&) = delete;
	~sspPlayManager();

	bool verify(int& nErrors, int& nWarnings) const;

	bool initialize(sspDomainData& data);
	bool start();
	bool update();
	void stop();
	void terminate();

	bool verifyPlaying();

private:
	sspOscConsole osc_console_;
	std::weak_ptr<sspTimeline> root_stream_;
	std::chrono::steady_clock::time_point previous_time_;
	sspTimeUpdater updater_;

	std::shared_ptr<sspConditionalMsgList>	start_messages_;
	std::shared_ptr<sspTriggerMsgList>		trigger_messages_;
	std::shared_ptr<sspTimeTriggerMsgList>	clock_messages_;
};

