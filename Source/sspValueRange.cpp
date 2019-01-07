/*
  ==============================================================================

    sspValueRange.cpp
    Created: 7 Jan 2019 3:32:49pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspValueRange.h"
#include "sspLogging.h"

#include <limits>

sspValueRange::sspValueRange() 
	: min_(0.0f), max_(1.0f)
{
	val_ = (min_ + max_) * 0.5f;
}

bool sspValueRange::verify(int& nErrors, int& nWarnings) const
{
	bool bReturn = true;

	if (min_ > max_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << ": min is larger than max";
	}
	else {
		if ((max_ - min_) < std::numeric_limits<float>::epsilon() ) {
			SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << ": min and max are equal";
		}
		if (val_ < min_ || val_ > max_) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << ": val is outside range";
		}
	}

	return bReturn;
}

void sspValueRange::setValue(float value) {
	if (value < min_) 
		val_ = min_;
	else if (value > max_)
		val_ = max_;
	else
		val_ = value;
}

void sspValueRange::setValueRange(float fMin, float fMax)
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

void sspValueRange::setNormalized(float fVal)
{
	if (fVal <= 0.0f)
		val_ = min_;
	else if (fVal >= 1.0f)
		val_ = max_;
	else
		val_ = min_ + (max_ - min_) * fVal;
}

float sspValueRange::getNormalized() const
{
	assert((max_ - min_) > std::numeric_limits<float>::epsilon());
	return (val_ - min_) / (max_ - min_);
}
