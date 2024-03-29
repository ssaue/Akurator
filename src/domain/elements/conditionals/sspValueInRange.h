/*
  ==============================================================================

    sspValueInRange.h
    Created: 10 Jan 2019 11:58:05am
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "domain/core/sspDomainPrimitives.h"
#include <boost/serialization/weak_ptr.hpp>

class sspValueInRange : public sspConditional
{
	std::weak_ptr<sspValue> min_;
	std::weak_ptr<sspValue> max_;
	std::weak_ptr<sspValue> test_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspConditional);
		ar & BOOST_SERIALIZATION_NVP(min_);
		ar & BOOST_SERIALIZATION_NVP(max_);
		ar & BOOST_SERIALIZATION_NVP(test_);
	}

public:
	sspValueInRange();
	sspValueInRange(const sspValueInRange& cond) = delete;
	sspValueInRange& operator= (const sspValueInRange& cond) = delete;
	virtual ~sspValueInRange() {}

	// Virtual methods
	virtual bool isTrue() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setTest(std::weak_ptr<sspValue> value) { test_ = std::move(value); }
	void setRange(std::weak_ptr<sspValue> min, std::weak_ptr<sspValue> max)
		{ min_ = std::move(min); max_ = std::move(max);	}

	std::weak_ptr<sspValue> getTest() const { return test_; }
	std::weak_ptr<sspValue> getMin() const { return min_; }
	std::weak_ptr<sspValue> getMax() const { return max_; }
};
