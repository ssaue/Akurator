/*
  ==============================================================================

    sspDayOfWeek.cpp
    Created: 10 Jan 2019 12:00:18pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspDayOfWeek.h"
#include "access/sspLogging.h"

using namespace boost::gregorian;

  sspDayOfWeek::sspDayOfWeek()
	  : sspConditional(), days_()
{
}

  bool sspDayOfWeek::isTrue() const
{
	auto now = day_clock::local_day().day_of_week();
	for (auto&& day : days_) {
		if (day == now) return true;
	}
	return false;
}

bool sspDayOfWeek::verify(int & nErrors, int & /*nWarnings*/) const
{
	bool bReturn = true;

	if (days_.empty()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: No days are selected", getName());
	}

	return bReturn;
}
