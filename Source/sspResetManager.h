/*
  ==============================================================================

    sspResetManager.h
    Created: 15 Apr 2019 2:33:36pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

#include "sspWatchDog.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

class sspResetManager
{
public:
	//Static program settings
	static boost::gregorian::date_duration reset_interval_s;
	static boost::posix_time::time_duration reset_time_s;

	static bool watchdog_enable_s;
	static sspWatchdog::Type watchdog_type_s;
	static double watchdog_timeout_s;

	sspResetManager() = default;
	sspResetManager(const sspResetManager&) = delete;
	sspResetManager& operator=(const sspResetManager&) = delete;
	~sspResetManager() {}

	bool verify(int& nErrors, int& nWarnings) const;

	bool initialize();
	void terminate();

	bool start();
	bool update();
	void stop();

	bool softReboot();

private:
	std::unique_ptr<sspWatchdog> watchdog_;
	boost::gregorian::date next_reset_;
	const int reset_minutes_ = 10;		// Minutes roundoff around the reset time
};
