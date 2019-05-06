/*
  ==============================================================================

    sspICPanalogInput.h
    Created: 5 May 2019 2:50:45pm
    Author:  Admin

  ==============================================================================
*/

#pragma once

#include "sspICPinput.h"
#include "sspDomainPrimitives.h"

#include <boost/serialization/shared_ptr.hpp>

class sspBasicValue;

class sspICPanalogInput : public sspICPinput
{
	std::shared_ptr<sspValue> value_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspICPinput);
		ar & BOOST_SERIALIZATION_NVP(value_);
	}

public:
	sspICPanalogInput();
	sspICPanalogInput(const sspICPanalogInput& inp) = delete;
	sspICPanalogInput& operator= (const sspICPanalogInput& inp) = delete;
	virtual ~sspICPanalogInput();

	virtual bool update() override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	void setValue(std::shared_ptr<sspValue> value);
	std::shared_ptr<sspValue> getValue() const { return value_; }

private:
	// Hack for boost serialization
	std::shared_ptr<sspBasicValue> set_value_;
};

