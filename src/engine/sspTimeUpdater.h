/*
  ==============================================================================

    sspTimeUpdater.h
    Created: 3 Apr 2019 10:21:55pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

#include <chrono>

class sspTimeUpdater
{
private:
	std::chrono::steady_clock::time_point next_time_;
	std::chrono::milliseconds interval_;

public:
	sspTimeUpdater() 
		: interval_(0) {}
	sspTimeUpdater(double seconds)
		: interval_(std::chrono::milliseconds(static_cast<int>(seconds * 1000))) {}

	void setInterval(double seconds)
	{ 
		interval_ = std::chrono::milliseconds(static_cast<int>(seconds * 1000));
	}

	void initialize(bool bIncrement = true)
	{
		next_time_ = std::chrono::steady_clock::now();
		if (bIncrement) next_time_ += interval_;
	}

	bool update()
	{
		bool bUpdate = (std::chrono::steady_clock::now() > next_time_);
		if (bUpdate) next_time_ += interval_;
		return bUpdate;
	}
};

