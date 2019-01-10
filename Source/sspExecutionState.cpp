/*
  ==============================================================================

    sspExecutionTime.cpp
    Created: 10 Jan 2019 10:12:47am
    Author:  sigurds

  ==============================================================================
*/

#include "sspExecutionState.h"

#include <stdexcept>

using namespace std::chrono;

sspExecutionState* sspExecutionState::s_instance_ = nullptr;
bool sspExecutionState::s_destroyed_ = false;

sspExecutionState::sspExecutionState(void)
	: running_(false)
{
}

sspExecutionState::~sspExecutionState(void)
{
	s_instance_ = NULL;
	s_destroyed_ = true;
}

void sspExecutionState::run()
{
	start_time_ = steady_clock::now();
	running_ = true;
}

double sspExecutionState::secondsRunning() const
{
	if (running_) {
		auto diff = duration_cast<seconds>(steady_clock::now() - start_time_);
		return static_cast<double>(diff.count());
	}
	else {
		return 0.0;
	}
}

/*
** Singleton stuff
*/

sspExecutionState& sspExecutionState::Instance()
{
	if (!s_instance_) {
		if (s_destroyed_) {
			onDeadReference();
		}
		else {
			create();
		}
	}
	return *s_instance_;
}

void sspExecutionState::create()
{
	static sspExecutionState theInstance;
	s_instance_ = &theInstance;
}

void sspExecutionState::onDeadReference()
{
	throw std::runtime_error("Dead reference to sspExecutionState detected");
}
