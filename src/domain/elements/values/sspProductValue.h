/*
  ==============================================================================

    sspProductValue.h
    Created: 7 Jan 2019 3:34:05pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "domain/core/sspDomainPrimitives.h"
#include "domain/core/sspSharedVector.h"

class sspProductValue : public sspValue
{
	sspWeakVector<sspValue> factors_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspValue);
		ar & BOOST_SERIALIZATION_NVP(factors_);
	}

public:
	sspProductValue();
	sspProductValue(const sspProductValue& val) = delete;
	sspProductValue& operator= (const sspProductValue& val) = delete;
	virtual ~sspProductValue() {}

	// Virtual methods
	virtual double getValue() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setFactors(const sspWeakVector<sspValue>& values) { factors_ = values; }
	const sspWeakVector<sspValue>& getFactors() const { return factors_; }
};

