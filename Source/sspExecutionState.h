/*
  ==============================================================================

    sspExecutionState.h
    Created: 10 Jan 2019 10:06:59am
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include <chrono>

// Class sspExecutionState is implemented as a Singleton pattern

class sspExecutionState
{
	bool running_;
	std::chrono::steady_clock::time_point start_time_;

	static sspExecutionState* s_instance_;
	static bool s_destroyed_;

public:
	static sspExecutionState& Instance();

	void run();
	double secondsRunning() const;

private:
	sspExecutionState();
	sspExecutionState(const sspExecutionState&) = delete;
	sspExecutionState& operator=(const sspExecutionState&) = delete;
	~sspExecutionState();

	static void create();
	static void onDeadReference();
};
