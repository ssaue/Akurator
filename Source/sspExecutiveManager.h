/*
  ==============================================================================

    sspExecutiveManager.h
    Created: 31 Mar 2019 7:13:02pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include <boost/date_time/posix_time/posix_time.hpp>

class sspPlayManager;

// Class sspExecutiveManager inherits a Juce::Timer and is the main message loop
class sspExecutiveManager : public Timer
{
public:
	enum Startup : int { DoNothing, Initialize, Play };
	enum class Shutdown : int { KeepRunning, Stop, Exit };

	// Static functions (program settings)
	static Startup startup_proc_s;
	static Shutdown shutdown_proc_s;

	static bool use_play_interval_s;
	static boost::posix_time::time_duration start_time_s;
	static boost::posix_time::time_duration end_time_s;

	static double update_interval_s;	// Update interval (in seconds)

	sspExecutiveManager();
	sspExecutiveManager(const sspExecutiveManager&) = delete;
	sspExecutiveManager& operator=(const sspExecutiveManager&) = delete;
	~sspExecutiveManager();

	bool verify(int& nErrors, int& nWarnings) const;

	void start();
	void stop();

private:
	virtual void timerCallback() override;
	bool isPlayInterval() const;

	std::unique_ptr<sspPlayManager> play_manager_;
};
