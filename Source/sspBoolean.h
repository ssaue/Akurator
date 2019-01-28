/*
  ==============================================================================

    sspBoolean.h
    Created: 10 Jan 2019 11:56:16am
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPrimitives.h"

class sspBoolean : public sspConditional
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
	sspBoolean() : sspConditional(), value_(true) {}
	sspBoolean(const sspBoolean& cond) = delete;
	sspBoolean& operator= (const sspBoolean& cond) = delete;
	virtual ~sspBoolean() {}

	// Virtual methods
	virtual bool isTrue() const override { return value_; }
	virtual bool verify(int& /*nErrors*/, int& /*nWarnings*/) const override { return true; }

	// Accessors
	void setValue(bool bVal) { value_ = bVal; }
};

