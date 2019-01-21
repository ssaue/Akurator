/*
  ==============================================================================

    sspSilenceObject.h
    Created: 21 Jan 2019 2:52:40pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspScheduleObject.h"
#include "sspFinishedResponder.h"


class sspSilenceObject : public sspScheduleObject
{
	double duration_;
	std::weak_ptr<sspFinishedResponder> responder_;

public:
	sspSilenceObject() = default;
	sspSilenceObject(const sspSilenceObject& obj) = delete;
	sspSilenceObject& operator= (const sspSilenceObject& obj) = delete;
	virtual ~sspSilenceObject() {}

	virtual	bool start() override;
	virtual bool update() override;
	virtual void finish() override;

	void setDuration(double value) { duration_ = value; }
	void setResponder(std::weak_ptr<sspFinishedResponder> responder) { responder_= responder; }
};
