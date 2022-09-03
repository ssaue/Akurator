/*
  ==============================================================================

    sspTimeMap.cpp
    Created: 7 Jan 2019 3:33:04pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspTimeMap.h"
#include "access/sspLogging.h"

using namespace boost::posix_time;

sspTimeMap::sspTimeMap()
	: sspValue(), clock_min_(0, 0, 0), clock_max_(0, 15, 0), outp_min_(0.0f), outp_max_(1.0f)
{
	computeLinearFactors();
}

void sspTimeMap::computeLinearFactors()
{
	auto inp_min = clock_min_.total_seconds();
	auto inp_max = clock_max_.total_seconds();
	lin_a_ = (inp_min < inp_max) ? (outp_max_ - outp_min_) / static_cast<double>(inp_max - inp_min) : 1.0f;
	lin_b_ = outp_min_ - lin_a_ * static_cast<double>(clock_min_.total_seconds());
}


void sspTimeMap::setInputRange(const time_duration & min, const time_duration & max)
{
	if (min > max) {
		clock_min_ = max;
		clock_max_ = min;
	}
	else {
		clock_min_ = min;
		clock_max_ = max;
	}
	computeLinearFactors();
}

void sspTimeMap::setOutputRange(double fMin, double fMax)
{
	// May be inverted
	outp_min_ = fMin;
	outp_max_ = fMax;
	computeLinearFactors();
}

double sspTimeMap::getValue() const
{
	auto now = second_clock::local_time().time_of_day();
	return lin_a_ * static_cast<double>(now.total_seconds()) + lin_b_;
}

bool sspTimeMap::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (clock_min_ > clock_max_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << ": time range is inverted";
	}
	if (clock_min_ == clock_max_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << ": time range has zero seconds";
	}
	if (std::abs(outp_max_ - outp_min_) < std::numeric_limits<double>::epsilon()) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << ": output has zero range";
	}

	return bReturn;
}
