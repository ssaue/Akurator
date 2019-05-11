/*
  ==============================================================================

    sspValueCompare.cpp
    Created: 10 Jan 2019 11:56:37am
    Author:  sigurds

  ==============================================================================
*/

#include "sspValueCompare.h"
#include "sspLogging.h"

#include <limits>

sspValueCompare::sspValueCompare()
	: sspConditional(), test_(), threshold_()
{
}

bool sspValueCompare::isTrue() const
{
	double test = 0.0, threshold = 0.0;

	if (auto ptr = test_.lock()) test = ptr->getValue();
	if (auto ptr = threshold_.lock()) threshold = ptr->getValue();

	switch (relation_) {
	case Relation::Equal: 
		return abs(test - threshold) <= std::numeric_limits<double>::epsilon();
		break;
	case Relation::Unequal:
		return abs(test - threshold) > std::numeric_limits<double>::epsilon();
		break;
	case Relation::Smaller:
		return test < threshold;
		break;
	case Relation::Larger:
		return test > threshold;
		break;
	case Relation::SmallEq:
		return test <= threshold;
		break;
	case Relation::LargeEq:
		return test >= threshold;
		break;
	default:
		return false;
		break;
	}
}

bool sspValueCompare::verify(int & nErrors, int & /*nWarnings*/) const
{
	bool bReturn = true;

	if (test_.expired()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid test value";
	}
	if (threshold_.expired()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid threshold value";
	}

	return bReturn;
}
