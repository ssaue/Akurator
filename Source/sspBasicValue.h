/*
  ==============================================================================

    sspBasicValue.h
    Created: 7 Jan 2019 3:32:21pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspDomainPrimitives.h"

class sspBasicValue : public sspValue
{
	double val_ = 0.0;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspValue);
		ar & BOOST_SERIALIZATION_NVP(val_);
	}

public:
	sspBasicValue() : sspValue() {}
	sspBasicValue(const sspBasicValue& val) = delete;
	sspBasicValue& operator= (const sspBasicValue& val) = delete;
	virtual ~sspBasicValue() {}

	// Virtual methods
	virtual double getValue() const override { return val_; }
	virtual bool verify(int& /*nErrors*/, int& /*nWarnings*/) const override { return true; }

	// Accessors
	void setValue(double value) { val_ = value; }
};

