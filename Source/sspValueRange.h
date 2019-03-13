/*
  ==============================================================================

    sspValueRange.h
    Created: 7 Jan 2019 3:32:49pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspDomainPrimitives.h"

class sspValueRange : public sspValue
{
	double val_;
	double min_, max_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspValue);
		ar & BOOST_SERIALIZATION_NVP(val_);
		ar & BOOST_SERIALIZATION_NVP(min_);
		ar & BOOST_SERIALIZATION_NVP(max_);
	}

public:
	sspValueRange();
	sspValueRange(const sspValueRange& val) = delete;
	sspValueRange& operator= (const sspValueRange& val) = delete;
	virtual ~sspValueRange() {}

	// Virtual methods
	virtual double getValue() const override { return val_; }
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setValue(double value);
	void setValueRange(double fmin, double fMax);
	void setNormalized(double fVal);

	double getNormalized() const;
	double getMin() const { return min_; }
	double getMax() const { return max_; }
};

