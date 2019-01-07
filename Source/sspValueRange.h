/*
  ==============================================================================

    sspValueRange.h
    Created: 7 Jan 2019 3:32:49pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPrimitives.h"

class sspValueRange : public sspValue
{
	float val_;
	float min_, max_;

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
	virtual float getValue() const override { return val_; }
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setValue(float value);
	void setValueRange(float fmin, float fMax);
	void setNormalized(float fVal);
	float getNormalized() const;

	float getMin() const { return min_; }
	float getMax() const { return max_; }

};

