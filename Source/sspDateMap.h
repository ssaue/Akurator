/*
  ==============================================================================

    sspDateMap.h
    Created: 7 Jan 2019 3:33:22pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPrimitives.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/greg_serialize.hpp>

class sspDateMap : public sspValue
{
	float outp_min_, outp_max_;
	boost::gregorian::partial_date date_min_;
	boost::gregorian::partial_date date_max_;

	// Utility variables to save computation time
	float lin_a_;
	void computeLinearFactors();

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspValue);
		ar & BOOST_SERIALIZATION_NVP(date_min_);
		ar & BOOST_SERIALIZATION_NVP(date_max_);
		ar & BOOST_SERIALIZATION_NVP(outp_min_);
		ar & BOOST_SERIALIZATION_NVP(outp_max_);
		computeLinearFactors();	// Only necessary when loading, but it doesn't hurt
	}

public:
	sspDateMap();
	sspDateMap(const sspDateMap& val) = delete;
	sspDateMap& operator= (const sspDateMap& val) = delete;
	virtual ~sspDateMap() {}

	// Virtual methods
	virtual float getValue() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setInputRange(const boost::gregorian::partial_date& min,
		const boost::gregorian::partial_date& max);	// This range may NOT be inverted
	void setOutputRange(float fMin, float fMax);			// This range may be inverted

	const boost::gregorian::partial_date& getDateMin() const { return date_min_; }
	const boost::gregorian::partial_date& getDateMax() const { return date_max_; }
	float getOutputMin() const { return outp_min_; }
	float getOutputMax() const { return outp_max_; }
};

