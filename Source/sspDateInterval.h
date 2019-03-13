/*
  ==============================================================================

    sspDateInterval.h
    Created: 10 Jan 2019 11:59:30am
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspDomainPrimitives.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/greg_serialize.hpp>

class sspDateInterval : public sspConditional
{
	boost::gregorian::partial_date date_min_;
	boost::gregorian::partial_date date_max_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspConditional);
		ar & BOOST_SERIALIZATION_NVP(date_min_);
		ar & BOOST_SERIALIZATION_NVP(date_max_);
	}

public:
	sspDateInterval();
	sspDateInterval(const sspDateInterval& cond) = delete;
	sspDateInterval& operator= (const sspDateInterval& cond) = delete;
	virtual ~sspDateInterval() {}

	// Virtual methods
	virtual bool isTrue() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setInputRange(const boost::gregorian::partial_date& min,
		const boost::gregorian::partial_date& max);	// This range may NOT be inverted

	const boost::gregorian::partial_date& getDateMin() const { return date_min_; }
	const boost::gregorian::partial_date& getDateMax() const { return date_max_; }
};
