/*
  ==============================================================================

    sspScheduler.cpp
    Created: 21 Jan 2019 4:26:05pm
    Author:  sigurds
	Adapted from: seccpur

  ==============================================================================
*/

#include "sspScheduler.h"

#include <stdexcept>

sspScheduler* sspScheduler::s_instance_ = nullptr;
bool sspScheduler::s_destroyed_ = false;

sspScheduler::sspScheduler(void)
	: running_(false)
{
}

sspScheduler::~sspScheduler(void)
{
	s_instance_ = NULL;
	s_destroyed_ = true;
}

void sspScheduler::run()
{
}

/*
** Singleton stuff
*/

sspScheduler& sspScheduler::Instance()
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

void sspScheduler::create()
{
	static sspScheduler theInstance;
	s_instance_ = &theInstance;
}

void sspScheduler::onDeadReference()
{
	throw std::runtime_error("Dead reference to sspScheduler detected");
}
