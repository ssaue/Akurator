/*
  ==============================================================================

    sspRandomValue.cpp
    Created: 7 Jan 2019 3:34:27pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspRandomValue.h"
#include "access/sspLogging.h"

#include <random>

namespace {
	// Establish a random-number engine
	std::random_device rd;
	std::mt19937 random_generator(rd());
}

sspRandomValue::sspRandomValue()
	: sspValue(), low_(), high_()
{
}

double sspRandomValue::getValue() const
{
	auto low = low_->getValue();
	auto high = high_->getValue();
	if (low < high) {
		std::uniform_real_distribution<double> dist(low, high);
		return dist(random_generator);
	}
	else {
		std::uniform_real_distribution<double> dist(high, low);
		return dist(random_generator);
	}
}

bool sspRandomValue::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (!low_ || !high_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid value";
	}
	else {
		if (low_.get() == this || high_.get() == this) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
		}
		if (low_.get() == high_.get()) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << ": low and high are equal values";
		}

		auto low = low_->getValue();
		auto high = high_->getValue();
		if (low > high) {
			SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << ": low is larger than high";
		}
		else if ((high - low) < std::numeric_limits<double>::epsilon()) {
			SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << ": high and low are equal";
		}
	}
	return bReturn;
}
