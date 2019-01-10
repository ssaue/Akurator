/*
  ==============================================================================

    sspSecondsRun.h
    Created: 7 Jan 2019 3:34:39pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPrimitives.h"

class sspSecondsRun : public sspValue
{
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspValue);
	}

public:
	sspSecondsRun() = default;
	sspSecondsRun(const sspSecondsRun& val) = delete;
	sspSecondsRun& operator= (const sspSecondsRun& val) = delete;
	virtual ~sspSecondsRun() {}

	// Virtual methods
	virtual double getValue() const override;
	virtual bool verify(int& /*nErrors*/, int& /*nWarnings*/) const override { return true; }
};

