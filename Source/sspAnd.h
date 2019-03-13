/*
  ==============================================================================

    sspAnd.h
    Created: 10 Jan 2019 12:00:41pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspDomainPrimitives.h"
#include "sspDomainVector.h"

class sspAnd : public sspConditional
{
private:
	sspDomainVector<sspConditional> operands_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspConditional);
		ar & BOOST_SERIALIZATION_NVP(operands_);
	}

public:
	sspAnd();
	sspAnd(const sspAnd& cond) = delete;
	sspAnd& operator= (const sspAnd& cond) = delete;
	virtual ~sspAnd() {}

	// Virtual methods
	virtual bool isTrue() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;
	
	// Accessors
	void setOperands(const sspDomainVector<sspConditional>& ops) { operands_ = ops; }
	const sspDomainVector<sspConditional>& getOperands() const { return operands_; }
};
