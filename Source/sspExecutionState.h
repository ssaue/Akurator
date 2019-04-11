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
	static sspExecutionState* s_instance_;
	static bool s_destroyed_;

	bool running_ = false;
	bool playing_ = false;

	std::chrono::steady_clock::time_point start_run_time_;
	std::chrono::steady_clock::time_point start_play_time_;

public:
	static sspExecutionState& Instance();

	void run(bool yes = true);
	void play(bool yes = true);

	bool isRunning() const { return running_; }
	bool isPlaying() const { return playing_; }

	double secondsRunning() const;
	double secondsPlaying() const;

private:
	sspExecutionState();
	sspExecutionState(const sspExecutionState&) = delete;
	sspExecutionState& operator=(const sspExecutionState&) = delete;
	~sspExecutionState();

	static void create();
	static void onDeadReference();
};
