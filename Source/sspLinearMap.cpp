/*
  ==============================================================================

    sspLinearMap.cpp
    Created: 7 Jan 2019 3:33:34pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspLinearMap.h"
#include "sspLogging.h"

sspLinearMap::sspLinearMap()
	: inp_min_(0.0f), inp_max_(1.0f), outp_min_(0.0f), outp_max_(1.0f)
{
	computeLinearFactors();
}

void sspLinearMap::computeLinearFactors()
{
	// Avoid division by zero
	lin_a_ = std::abs(inp_max_ - inp_min_) > std::numeric_limits<float>::epsilon() 
		? (outp_max_ - outp_min_) / (inp_max_ - inp_min_) : 1.0f;
	lin_b_ = outp_min_ - lin_a_ * inp_min_;
}

void sspLinearMap::setInputRange(float fMin, float fMax) 
{ 
	// Should not be inverted
	if (fMin > fMax) {
		inp_min_ = fMax;
		inp_max_ = fMin;
	}
	else {
		inp_min_ = fMin;
		inp_max_ = fMax;
	}
	computeLinearFactors();
}
void sspLinearMap::setOutputRange(float fMin, float fMax)
{ 
	// May be inverted
	outp_min_ = fMin; 
	outp_max_ = fMax; 
	computeLinearFactors();
}

float sspLinearMap::getValue() const
{
	return lin_a_ * val_->getValue() + lin_b_;
}

bool sspLinearMap::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (!val_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid value";
	}
	else if (val_.get() == this) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
	}
	if (inp_min_ > inp_max_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << ": input range is inverted";
	}
	else if ((inp_max_ - inp_min_) < std::numeric_limits<float>::epsilon()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << ": input has zero range";
	}
	if (std::abs(outp_max_ - outp_min_) < std::numeric_limits<float>::epsilon()) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << ": output has zero range";
	}

	return bReturn;
}
