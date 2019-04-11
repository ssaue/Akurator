/*
  ==============================================================================

    sspExecutiveManager.cpp
    Created: 31 Mar 2019 7:13:02pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "sspExecutiveManager.h"
#include "sspPlayManager.h"
#include "sspExecutionState.h"
#include "sspLogging.h"

// Define the static constants
sspExecutiveManager::Startup sspExecutiveManager::startup_proc_s = sspExecutiveManager::Startup::DoNothing;
sspExecutiveManager::Shutdown sspExecutiveManager::shutdown_proc_s = sspExecutiveManager::Shutdown::Stop;

bool sspExecutiveManager::use_play_interval_s = true;
boost::posix_time::time_duration sspExecutiveManager::start_time_s{ 8, 0, 0 };
boost::posix_time::time_duration sspExecutiveManager::end_time_s{ 20, 0, 0 };

double sspExecutiveManager::update_interval_s = 1.0;

/*****************************************************/

sspExecutiveManager::sspExecutiveManager()
	: Timer(), play_manager_(std::make_unique<sspPlayManager>())
{
}

sspExecutiveManager::~sspExecutiveManager()
{
	stop();
}

bool sspExecutiveManager::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;


	if (use_play_interval_s && start_time_s.is_not_a_date_time()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << "sspExecutiveManager: Invalid start time of interval";
	}
	if (use_play_interval_s && end_time_s.is_not_a_date_time()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << "sspExecutiveManager: Invalid end time of interval";
	}
	if (!play_manager_->verify(nErrors, nWarnings))
		bReturn = false;

	return bReturn;
}

void sspExecutiveManager::start()
{
	srand((unsigned) time(NULL));	// Seed a random generator with the start time
	int msecs = static_cast<int>(update_interval_s * 1000);
	startTimer(msecs);
	if (isTimerRunning()) {
		if (isPlayInterval()) {
			play_manager_->start();
		}
		// TODO: Reset manager
		sspExecutionState::Instance().run();
	}
}

void sspExecutiveManager::stop()
{
	stopTimer();
	play_manager_->stop();
	sspExecutionState::Instance().run(false);
	// TODO: reset manager??
}

void sspExecutiveManager::timerCallback()
{
	// TODO: Check if everything is OK with play manager and reset manager

	isPlayInterval() ? play_manager_->start() : play_manager_->stop();
	if (!play_manager_->update() && shutdown_proc_s != Shutdown::KeepRunning) {
		stop();
	}
}

bool sspExecutiveManager::isPlayInterval() const
{
	if (use_play_interval_s) {
		auto now = boost::posix_time::second_clock::local_time().time_of_day();
		return ((start_time_s < now && end_time_s > now) || (end_time_s < now && start_time_s > now));
	}
	return true;
}
