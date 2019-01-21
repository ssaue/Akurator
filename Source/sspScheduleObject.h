/*
  ==============================================================================

    sspScheduleObject.h
    Created: 21 Jan 2019 2:52:26pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

class sspScheduleObject
{
protected:
	long	next_time_;
	bool	is_playing_;

public:
	sspScheduleObject() = default;
	sspScheduleObject(const sspScheduleObject& obj) = delete;
	sspScheduleObject& operator= (const sspScheduleObject& obj) = delete;
	virtual ~sspScheduleObject() {}

	virtual	bool start() = 0;
	virtual bool update() = 0;
	virtual void finish() = 0;

	long	getNextTime() const { return next_time_; }
	long&	getNextTime() { return next_time_; }

	bool isPlaying() const { return is_playing_; }
};
