/*
  ==============================================================================

    sspTimeline.cpp
    Created: 31 Jan 2019 3:30:06pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspTimeline.h"
#include "sspLogging.h"

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/export.hpp>

sspTimeline::sspTimeline()
	: sspMessageHandler(), sspFinishedResponder(), children_(), time_factor_()
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

void sspTimeline::terminate()
{
	stop();
	for (auto child : children_) {
		child->terminate();
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

#include "sspStream.h"
#include "sspAudioStream.h"

BOOST_CLASS_EXPORT(sspTimeline);
BOOST_CLASS_EXPORT(sspStream);
BOOST_CLASS_EXPORT(sspAudioStream);
