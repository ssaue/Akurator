/*
  ==============================================================================

    sspResetManager.cpp
    Created: 15 Apr 2019 2:33:36pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "sspResetManager.h"
#include "sspLogging.h"

using namespace boost::posix_time;

boost::gregorian::date_duration sspResetManager::reset_interval_s{ 1 };
time_duration sspResetManager::reset_time_s{ 4, 0, 0 };

sspWatchdog::Type sspResetManager::watchdog_type_s = sspWatchdog::Type::None;
double sspResetManager::watchdog_timeout_s = 5.0;

bool sspResetManager::verify(int & nErrors, int & /*nWarnings*/) const
{
	bool bReturn = true;

	if ((watchdog_type_s != sspWatchdog::Type::None) && watchdog_timeout_s <= 1.0) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << "sspResetManager: Watchdog timeout is too small";
	}

	return bReturn;
}

bool sspResetManager::initialize()
{
	if (watchdog_type_s == sspWatchdog::Type::None)
		return true;    // No watchdog selected - nothing more to initialize

	watchdog_ = std::unique_ptr<sspWatchdog>(sspWatchdog::create(watchdog_type_s));
	watchdog_enabled_ = watchdog_ ? watchdog_->initialize(watchdog_timeout_s) : false;
	return watchdog_enabled_;
}

void sspResetManager::terminate()
{
	if (watchdog_enabled_ && watchdog_) watchdog_->terminate();
}

bool sspResetManager::start()
{
	if (reset_interval_s.days() > 0) {
		next_reset_ = boost::gregorian::day_clock::universal_day() + reset_interval_s;
	}
	return (!watchdog_enabled_ || watchdog_->enable());
}

bool sspResetManager::update()
{
	bool reset = false;
	if (reset_interval_s.days() > 0) {
		auto today = boost::gregorian::day_clock::universal_day();
		if (today == next_reset_) {
			auto diff = second_clock::local_time().time_of_day() - reset_time_s;
			reset = abs(diff.minutes()) < reset_minutes_;
		}
	}

	if (reset) {
		if (softReboot()) {
			stop();
		}
		else if (watchdog_enabled_) {
			watchdog_enabled_ = false;	// Forces hard reboot
		}
		return false;
	}
	if (watchdog_enabled_) {
		watchdog_->refresh();
	}
	return true;
}

void sspResetManager::stop()
{
	if (watchdog_enabled_ && watchdog_) watchdog_->disable();
}

bool sspResetManager::softReboot()
{
#ifdef WIN32
	int ret = std::system("shutdown /r /t 5 /c \"Planned Akurator restart\" /f /d p:4:1");
	return (ret == 0);
#elif // WIN32
	return false;	// Only implemented on Windows
#endif
}
