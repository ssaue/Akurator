/*
  ==============================================================================

    sspAddValue.h
    Created: 7 Jan 2019 3:33:53pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPrimitives.h"
#include "sspObjectVector.h"

#include <vector>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

class SSpAddValue : public sspValue
{
	sspObjectVector<sspValue> addends_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspValue);
		ar & BOOST_SERIALIZATION_NVP(addends_);
	}

public:
	SSpAddValue() = default;
	SSpAddValue(const SSpAddValue& val) = delete;
	SSpAddValue& operator= (const SSpAddValue& val) = delete;
	virtual ~SSpAddValue() {}

	// Virtual methods
	virtual float getValue() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setAddends(const sspObjectVector<sspValue>& values) { addends_ = values; }
	const sspObjectVector<sspValue>& getAddends() const { return addends_; }
};

