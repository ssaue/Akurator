/*
  ==============================================================================

    sspDateInterval.cpp
    Created: 10 Jan 2019 11:59:30am
    Author:  sigurds

  ==============================================================================
*/

#include "sspDateInterval.h"
#include "sspLogging.h"

using namespace boost::gregorian;

sspDateInterval::sspDateInterval()
	: sspConditional(), date_min_(1, Jan), date_max_(31, Dec)
{
}

bool sspDateInterval::isTrue() const
{
	auto now = day_clock::local_day();
	return ((date_min_(now.year()) < now && date_max_(now.year()) > now) 
		|| (date_max_(now.year()) < now && date_min_(now.year()) > now));
}

bool sspDateInterval::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (date_min_(0) > date_max_(0)) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << ": date range is inverted";
	}
	if (date_min_(0) == date_max_(0)) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << ": date range has zero days";
	}

	return bReturn;
}

void sspDateInterval::setInputRange(const partial_date& min, const partial_date& max)
{
	if (min(0) > max(0)) {
		date_min_ = max;
		date_max_ = min;
	}
	else {
		date_min_ = min;
		date_max_ = max;
	}
}

