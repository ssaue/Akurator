/*
  ==============================================================================

    sspAddValue.h
    Created: 7 Jan 2019 3:33:53pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspDomainPrimitives.h"
#include "sspDomainVector.h"

class sspAddValue : public sspValue
{
	sspDomainVector<sspValue> addends_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspValue);
		ar & BOOST_SERIALIZATION_NVP(addends_);
	}

public:
	sspAddValue();
	sspAddValue(const sspAddValue& val) = delete;
	sspAddValue& operator= (const sspAddValue& val) = delete;
	virtual ~sspAddValue() {}

	// Virtual methods
	virtual double getValue() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setAddends(const sspDomainVector<sspValue>& values) { addends_ = values; }
	const sspDomainVector<sspValue>& getAddends() const { return addends_; }
};

