/*
  ==============================================================================

    sspTimeInterval.cpp
    Created: 10 Jan 2019 11:58:26am
    Author:  sigurds

  ==============================================================================
*/

#include "sspTimeInterval.h"
#include "access/sspLogging.h"

using namespace boost::posix_time;

void sspTimeInterval::setInputRange(const time_duration& min, const time_duration& max)
{
	if (min > max) {
		clock_min_ = max;
		clock_max_ = min;
	}
	else {
		clock_min_ = min;
		clock_max_ = max;
	}
}

sspTimeInterval::sspTimeInterval()
	: sspConditional(), clock_min_(), clock_max_()
{
}

bool sspTimeInterval::isTrue() const
{
	auto now = second_clock::local_time().time_of_day();
	return ((clock_min_ < now && clock_max_ > now) || (clock_max_ < now && clock_min_ > now));
}

bool sspTimeInterval::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (clock_min_ > clock_max_) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn, "{}: Date range is inverted", getName());
	}
	if (clock_min_ == clock_max_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Date range has zero days", getName());
	}

	return bReturn;
}
