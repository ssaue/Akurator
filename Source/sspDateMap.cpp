/*
  ==============================================================================

    sspDateMap.cpp
    Created: 7 Jan 2019 3:33:22pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspDateMap.h"
#include "sspLogging.h"

using namespace boost::gregorian;

sspDateMap::sspDateMap()
	: date_min_(1, 1), date_max_(31, 12), outp_min_(0.0), outp_max_(1.0)
{
	computeLinearFactors();
}

void sspDateMap::computeLinearFactors()
{
	auto duration = date_max_(0) - date_min_(0);
	lin_a_ = (duration.days() > 0) ? (outp_max_ - outp_min_) / static_cast<double>(duration.days()) : 1.0f;
}


void sspDateMap::setInputRange(const partial_date& min, const partial_date& max)
{
	if (min(0) > max(0)) {
		date_min_ = max;
		date_max_ = min;
	}
	else {
		date_min_ = min;
		date_max_ = max;
	}
	computeLinearFactors();
}

void sspDateMap::setOutputRange(double fMin, double fMax)
{
	// May be inverted
	outp_min_ = fMin;
	outp_max_ = fMax;
	computeLinearFactors();
}

double sspDateMap::getValue() const
{
	auto now = day_clock::local_day();
	auto diff = now - date_min_(now.year());
	auto val = outp_min_ + lin_a_ * static_cast<double>(diff.days());

	if (outp_max_ > outp_min_) {
		return val > outp_max_ ? outp_max_ : (val < outp_min_ ? outp_min_ : val);
	}
	else {
		return val > outp_min_ ? outp_min_ : (val < outp_max_ ? outp_max_ : val);
	}
}

bool sspDateMap::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (date_min_(0) > date_max_(0)) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << ": date range is inverted";
	}
	if (date_min_(0) == date_max_(0)) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << ": date range has zero days";
	}
	if (std::abs(outp_max_ - outp_min_) < std::numeric_limits<double>::epsilon()) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << ": output has zero range";
	}

	return bReturn;
}
