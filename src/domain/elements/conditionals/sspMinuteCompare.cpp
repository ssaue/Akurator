/*
  ==============================================================================

    sspMinuteCompare.cpp
    Created: 10 Jan 2019 11:59:12am
    Author:  sigurds

  ==============================================================================
*/

#include "sspMinuteCompare.h"
#include "access/sspLogging.h"
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::posix_time;

bool sspMinuteCompare::isTrue() const
{
	auto now = second_clock::local_time().time_of_day().minutes();

	switch (relation_) {
	case Relation::Before:
		return now < minutes_;
	case Relation::After:
		return now > minutes_;
	case Relation::Equal:
		return now == minutes_;
	default:
		return false;
	}
}

bool sspMinuteCompare::verify(int & nErrors, int & /*nWarnings*/) const
{
	bool bReturn = true;

	if (minutes_ < 0 || minutes_ > 60) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << ": minutes are not valid";
	}

	return bReturn;
}
