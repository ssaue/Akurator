/*
  ==============================================================================

    sspLinearMap.cpp
    Created: 7 Jan 2019 3:33:34pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspLinearMap.h"
#include "access/sspLogging.h"

sspLinearMap::sspLinearMap()
	: sspValue(), inp_min_(0.0), inp_max_(1.0), outp_min_(0.0), outp_max_(1.0)
{
	computeLinearFactors();
}

void sspLinearMap::computeLinearFactors()
{
	// Avoid division by zero
	lin_a_ = std::abs(inp_max_ - inp_min_) > std::numeric_limits<double>::epsilon()
		? (outp_max_ - outp_min_) / (inp_max_ - inp_min_) : 1.0f;
	lin_b_ = outp_min_ - lin_a_ * inp_min_;
}

void sspLinearMap::setInputRange(double fMin, double fMax)
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
void sspLinearMap::setOutputRange(double fMin, double fMax)
{ 
	// May be inverted
	outp_min_ = fMin; 
	outp_max_ = fMax; 
	computeLinearFactors();
}

double sspLinearMap::getValue() const
{
	return lin_a_ * val_->getValue() + lin_b_;
}

bool sspLinearMap::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (!val_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid value", getName());
	}
	else if (val_.get() == this) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Value self reference", getName());
	}
	if (inp_min_ > inp_max_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Input range is inverted", getName());
	}
	else if ((inp_max_ - inp_min_) < std::numeric_limits<double>::epsilon()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Input has zero range", getName());
	}
	if (std::abs(outp_max_ - outp_min_) < std::numeric_limits<double>::epsilon()) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn, "{}: Output has zero range", getName());
	}

	return bReturn;
}
