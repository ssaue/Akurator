/*
  ==============================================================================

    sspTimeCompare.h
    Created: 10 Jan 2019 11:58:52am
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "domain/core/sspDomainPrimitives.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>

class sspTimeCompare : public sspConditional
{
public:
	enum class Relation : unsigned int { Before, After };

private:
	boost::posix_time::time_duration clock_;
	Relation relation_ = Relation::After;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspConditional);
		ar & BOOST_SERIALIZATION_NVP(clock_);
		ar & BOOST_SERIALIZATION_NVP(relation_);
	}

public:
	sspTimeCompare();
	sspTimeCompare(const sspTimeCompare& cond) = delete;
	sspTimeCompare& operator= (const sspTimeCompare& cond) = delete;
	virtual ~sspTimeCompare() {}

	// Virtual methods
	virtual bool isTrue() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setClock(const boost::posix_time::time_duration& clock) { clock_ = clock; }
	void setRelationship(Relation value) { relation_ = value; }

	const boost::posix_time::time_duration& getClock() const { return clock_; }
	Relation getRelationship() const { return relation_; }
};
