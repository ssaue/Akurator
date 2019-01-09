/*
  ==============================================================================

    sspTimeMap.h
    Created: 7 Jan 2019 3:33:04pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPrimitives.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>

class sspTimeMap : public sspValue
{
	float outp_min_, outp_max_;
	boost::posix_time::time_duration clock_min_;
	boost::posix_time::time_duration clock_max_;

	// Utility variables to save computation time
	float lin_a_, lin_b_;
	void computeLinearFactors();

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspValue);
		ar & BOOST_SERIALIZATION_NVP(clock_min_);
		ar & BOOST_SERIALIZATION_NVP(clock_max_);
		ar & BOOST_SERIALIZATION_NVP(outp_min_);
		ar & BOOST_SERIALIZATION_NVP(outp_max_);
		computeLinearFactors();	// Only necessary when loading, but it doesn't hurt
	}

public:
	sspTimeMap();
	sspTimeMap(const sspTimeMap& val) = delete;
	sspTimeMap& operator= (const sspTimeMap& val) = delete;
	virtual ~sspTimeMap() {}

	// Virtual methods
	virtual float getValue() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setInputRange(const boost::posix_time::time_duration& min, 
		const boost::posix_time::time_duration& max);	// This range may NOT be inverted
	void setOutputRange(float fMin, float fMax);		// This range may be inverted

	const boost::posix_time::time_duration& getClockMin() const { return clock_min_; }
	const boost::posix_time::time_duration& getClockMax() const { return clock_max_; }
	float getOutputMin() const { return outp_min_; }
	float getOutputMax() const { return outp_max_; }
};

