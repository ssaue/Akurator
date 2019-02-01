/*
  ==============================================================================

    sspTimeline.cpp
    Created: 31 Jan 2019 3:30:06pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspTimeline.h"
#include "sspLogging.h"

sspTimeline::sspTimeline()
	: sspMessageHandler(), children_(), time_factor_()
{
}

void sspTimeline::start()
{
	running_ = true;
	for (auto child : children_) {
		child->start();
	}
}

void sspTimeline::update(double seconds)
{
	for (auto child : children_) {
		child->update(getTimeStep(seconds));
	}
}

void sspTimeline::stop()
{
	running_ = false;
	for (auto child : children_) {
		child->stop();
	}
}

bool sspTimeline::empty() const
{
	for (auto child : children_) {
		if (!child->empty()) {
			return false;
		}
	}
	return true;
}

bool sspTimeline::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	for (auto&& child : children_) {
		if (!child) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid child";
		}
		else if (child.get() == this) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
		}
	}
	if (!time_factor_) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << " has no time factor";
	}

	return bReturn;
}

inline double sspTimeline::getTimeStep(double seconds)
{
	return time_factor_ ? seconds * time_factor_->getValue() : seconds;
}
