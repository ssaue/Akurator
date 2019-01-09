/*
  ==============================================================================

    sspLinearMap.h
    Created: 7 Jan 2019 3:33:34pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPrimitives.h"
#include <boost/serialization/shared_ptr.hpp>

class sspLinearMap : public sspValue
{
	std::shared_ptr<sspValue> val_;

	float inp_min_, inp_max_;
	float outp_min_, outp_max_;

	// Utility variables to save computation time
	float lin_a_, lin_b_;
	void computeLinearFactors();

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspValue);
		ar & BOOST_SERIALIZATION_NVP(val_);
		ar & BOOST_SERIALIZATION_NVP(inp_min_);
		ar & BOOST_SERIALIZATION_NVP(inp_max_);
		ar & BOOST_SERIALIZATION_NVP(outp_min_);
		ar & BOOST_SERIALIZATION_NVP(outp_max_);
		computeLinearFactors();	// Only necessary when loading, but it doesn't hurt
	}

public:
	sspLinearMap();
	sspLinearMap(const sspLinearMap& val) = delete;
	sspLinearMap& operator= (const sspLinearMap& val) = delete;
	virtual ~sspLinearMap() {}

	// Virtual methods
	virtual float getValue() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setValue(std::shared_ptr<sspValue> value) { val_ = std::move(value); }
	
	void setInputRange(float fMin, float fMax);		// This range may NOT be inverted
	void setOutputRange(float fMin, float fMax);	// This range may be inverted

	std::shared_ptr<sspValue> getInputValue() const { return val_; }

	float getInputMin() const { return inp_min_; }
	float getInputMax() const { return inp_max_; }
	float getOutputMin() const { return outp_min_; }
	float getOutputMax() const { return outp_max_; }
};

