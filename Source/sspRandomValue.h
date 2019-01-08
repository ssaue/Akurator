/*
  ==============================================================================

    sspRandomValue.h
    Created: 7 Jan 2019 3:34:27pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPrimitives.h"
#include <boost/serialization/shared_ptr.hpp>

class sspRandomValue : public sspValue
{
	std::shared_ptr<sspValue> low_;
	std::shared_ptr<sspValue> high_;
	
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspValue);
		ar & BOOST_SERIALIZATION_NVP(low_);
		ar & BOOST_SERIALIZATION_NVP(high_);
	}

public:
	sspRandomValue() = default;
	sspRandomValue(const sspRandomValue& val) = delete;
	sspRandomValue& operator= (const sspRandomValue& val) = delete;
	virtual ~sspRandomValue() {}

	// Virtual methods
	virtual float getValue() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setLow(std::shared_ptr<sspValue> value) { low_ = std::move(value); }
	void setHigh(std::shared_ptr<sspValue> value) { high_ = std::move(value); }

	std::shared_ptr<sspValue> getLow() const { return low_; }
	std::shared_ptr<sspValue> getHIgh() const { return high_; }
};

