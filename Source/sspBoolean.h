/*
  ==============================================================================

    sspBoolean.h
    Created: 10 Jan 2019 11:56:16am
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPrimitives.h"

class SSpBoolean : public sspConditional
{
private:
	bool value_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspConditional);
		ar & BOOST_SERIALIZATION_NVP(value_);
	}

public:
	SSpBoolean() = default;
	SSpBoolean(const SSpBoolean& cond) = delete;
	SSpBoolean& operator= (const SSpBoolean& cond) = delete;
	virtual ~SSpBoolean() {}

	// Virtual methods
	virtual bool isTrue() const override { return value_; }
	virtual bool verify(int& /*nErrors*/, int& /*nWarnings*/) const override { return true; }

	// Accessors
	void setValue(bool bVal) { value_ = bVal; }
};

