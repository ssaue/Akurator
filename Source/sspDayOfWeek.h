/*
  ==============================================================================

    sspDayOfWeek.h
    Created: 10 Jan 2019 12:00:18pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPrimitives.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/date_time/gregorian/greg_serialize.hpp>

class sspDayOfWeek : public sspConditional
{
private:
	std::vector<boost::date_time::weekdays> days_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspConditional);
		ar & BOOST_SERIALIZATION_NVP(days_);
	}

public:
	sspDayOfWeek();
	sspDayOfWeek(const sspDayOfWeek& cond) = delete;
	sspDayOfWeek& operator= (const sspDayOfWeek& cond) = delete;
	virtual ~sspDayOfWeek() {}

	// Virtual methods
	virtual bool isTrue() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setDays(const std::vector<boost::date_time::weekdays>& days) { days_ = days; }
	const std::vector<boost::date_time::weekdays>& getDays() const { return days_; }
};
