/*
  ==============================================================================

    sspICPdigitalInput.h
    Created: 5 May 2019 2:50:45pm
    Author:  Admin

  ==============================================================================
*/

#pragma once

#include "sspICPinput.h"
#include "domain/core/sspDomainPrimitives.h"

#include <boost/serialization/weak_ptr.hpp>

class sspBoolean;

class sspICPdigitalInput : public sspICPinput
{
	std::weak_ptr<sspConditional> conditional_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspICPinput);
		ar & BOOST_SERIALIZATION_NVP(conditional_);
	}

public:
	sspICPdigitalInput();
	sspICPdigitalInput(const sspICPdigitalInput& inp) = delete;
	sspICPdigitalInput& operator= (const sspICPdigitalInput& inp) = delete;
	virtual ~sspICPdigitalInput();

	virtual bool initialize() override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	void setConditional(std::weak_ptr<sspConditional> value);
	std::weak_ptr<sspConditional> getConditional() const { return conditional_; }

private:
	std::weak_ptr<sspBoolean> set_conditional_;
	void received(const std::string& response);
};

