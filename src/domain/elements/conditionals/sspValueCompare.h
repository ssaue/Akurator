/*
  ==============================================================================

    sspValueCompare.h
    Created: 10 Jan 2019 11:56:36am
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "domain/core/sspDomainPrimitives.h"
#include <boost/serialization/weak_ptr.hpp>

class sspValueCompare : public sspConditional
{
public:
	enum class Relation : unsigned int { Equal, Unequal, Smaller, Larger, SmallEq, LargeEq };

private:
	std::weak_ptr<sspValue> test_;
	std::weak_ptr<sspValue> threshold_;
	Relation relation_ = Relation::Equal;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspConditional);
		ar & BOOST_SERIALIZATION_NVP(test_);
		ar & BOOST_SERIALIZATION_NVP(threshold_);
		ar & BOOST_SERIALIZATION_NVP(relation_);
	}

public:
	sspValueCompare();
	sspValueCompare(const sspValueCompare& cond) = delete;
	sspValueCompare& operator= (const sspValueCompare& cond) = delete;
	virtual ~sspValueCompare() {}

	// Virtual methods
	virtual bool isTrue() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setTest(std::weak_ptr<sspValue> value) { test_ = std::move(value); }
	void setThreshold(std::weak_ptr<sspValue> value) { threshold_ = std::move(value); }
	void setRelationship(Relation value) { relation_ = value; }
	
	std::weak_ptr<sspValue> getTest() const { return test_; }
	std::weak_ptr<sspValue> getThreshold() const { return threshold_; }
	Relation getRelationship() const { return relation_; }
};
