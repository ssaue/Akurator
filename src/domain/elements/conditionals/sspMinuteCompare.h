/*
  ==============================================================================

    sspMinuteCompare.h
    Created: 10 Jan 2019 11:59:12am
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "domain/core/sspDomainPrimitives.h"

class sspMinuteCompare : public sspConditional
{
public:
	enum class Relation : unsigned int { Before, After, Equal };

private:
	int minutes_ = 0;
	Relation relation_ = Relation::After;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspConditional);
		ar & BOOST_SERIALIZATION_NVP(minutes_);
		ar & BOOST_SERIALIZATION_NVP(relation_);
	}

public:
	sspMinuteCompare() : sspConditional() {}
	sspMinuteCompare(const sspMinuteCompare& cond) = delete;
	sspMinuteCompare& operator= (const sspMinuteCompare& cond) = delete;
	virtual ~sspMinuteCompare() {}

	// Virtual methods
	virtual bool isTrue() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setMinutes(int minutes) { minutes_ = minutes; }
	void setRelationship(Relation value) { relation_ = value; }

	int getMinutes() const { return minutes_; }
	Relation getRelationship() const { return relation_; }
};
