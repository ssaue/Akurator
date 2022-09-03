/*
  ==============================================================================

    sspICPanalogInput.h
    Created: 5 May 2019 2:50:45pm
    Author:  Admin

  ==============================================================================
*/

#pragma once

#include "sspICPinput.h"
#include "domain/core/sspDomainPrimitives.h"

#include <boost/serialization/weak_ptr.hpp>

class sspBasicValue;

class sspICPanalogInput : public sspICPinput
{
	std::weak_ptr<sspValue> value_;

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

	void setValue(std::weak_ptr<sspValue> value);
	std::weak_ptr<sspValue> getValue() const { return value_; }

private:
	std::weak_ptr<sspBasicValue> set_value_;
};

