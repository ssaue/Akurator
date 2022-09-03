/*
  ==============================================================================

    sspNot.h
    Created: 10 Jan 2019 12:00:54pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "domain/core/sspDomainPrimitives.h"
#include <boost/serialization/weak_ptr.hpp>

class sspNot : public sspConditional
{
private:
	std::weak_ptr<sspConditional> operand_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspConditional);
		ar & BOOST_SERIALIZATION_NVP(operand_);
	}

public:
	sspNot();
	sspNot(const sspNot& cond) = delete;
	sspNot& operator= (const sspNot& cond) = delete;
	virtual ~sspNot() {}

	// Virtual methods
	virtual bool isTrue() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setOperand(std::weak_ptr<sspConditional> op) { operand_ = std::move(op); }
	std::weak_ptr<sspConditional> getOperand() const { return operand_; }
};
