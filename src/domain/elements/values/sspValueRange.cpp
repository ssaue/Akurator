/*
  ==============================================================================

    sspValueRange.cpp
    Created: 7 Jan 2019 3:32:49pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspValueRange.h"
#include "access/sspLogging.h"

#include <limits>

sspValueRange::sspValueRange() 
	: sspValue(), min_(0.0), max_(1.0)
{
	val_ = (min_ + max_) * 0.5;
}

bool sspValueRange::verify(int& nErrors, int& nWarnings) const
{
	bool bReturn = true;

	if (min_ > max_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Min is larger than max", getName());
	}
	else {
		if ((max_ - min_) < std::numeric_limits<double>::epsilon() ) {
			SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn, "{}: Min and max are equal", getName());
		}
		if (val_ < min_ || val_ > max_) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Value is outside range", getName());
		}
	}

	return bReturn;
}

void sspValueRange::setValue(double value) {
	if (value < min_) 
		val_ = min_;
	else if (value > max_)
		val_ = max_;
	else
		val_ = value;
}

void sspValueRange::setValueRange(double fMin, double fMax)
{
	if (min_ < max_) {
		min_ = fMin;
		max_ = fMax;
	}
	else {
		min_ = fMax;
		max_ = fMin;
	}
	setValue(val_); // Ensure value in range
}

void sspValueRange::setNormalized(double fVal)
{
	if (fVal <= 0.0)
		val_ = min_;
	else if (fVal >= 1.0)
		val_ = max_;
	else
		val_ = min_ + (max_ - min_) * fVal;
}

double sspValueRange::getNormalized() const
{
	assert((max_ - min_) > std::numeric_limits<double>::epsilon());
	return (val_ - min_) / (max_ - min_);
}
