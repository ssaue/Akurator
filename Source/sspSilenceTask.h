/*
  ==============================================================================

    sspSilenceTask.h
    Created: 21 Jan 2019 2:52:40pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspScheduleTask.h"
#include "sspFinishedResponder.h"


class sspSilenceTask : public sspScheduleTask
{
	std::weak_ptr<sspFinishedResponder> responder_;

public:
	sspSilenceTask() = default;
	sspSilenceTask(const sspSilenceTask& obj) = delete;
	sspSilenceTask& operator= (const sspSilenceTask& obj) = delete;
	virtual ~sspSilenceTask() {}

	virtual	bool run() override;

	void setDuration(double time);
	void setResponder(std::weak_ptr<sspFinishedResponder> responder) { responder_= responder; }
};
