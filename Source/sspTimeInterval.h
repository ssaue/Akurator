/*
  ==============================================================================

    sspTimeInterval.h
    Created: 10 Jan 2019 11:58:26am
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspDomainPrimitives.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>

class sspTimeInterval : public sspConditional
{
	boost::posix_time::time_duration clock_min_;
	boost::posix_time::time_duration clock_max_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspConditional);
		ar & BOOST_SERIALIZATION_NVP(clock_min_);
		ar & BOOST_SERIALIZATION_NVP(clock_max_);
	}

public:
	sspTimeInterval();
	sspTimeInterval(const sspTimeInterval& cond) = delete;
	sspTimeInterval& operator= (const sspTimeInterval& cond) = delete;
	virtual ~sspTimeInterval() {}

	// Virtual methods
	virtual bool isTrue() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setInputRange(const boost::posix_time::time_duration& min,
		const boost::posix_time::time_duration& max);	// This range may NOT be inverted

	const boost::posix_time::time_duration& getClockMin() const { return clock_min_; }
	const boost::posix_time::time_duration& getClockMax() const { return clock_max_; }
};
