/*
  ==============================================================================

    sspOr.h
    Created: 10 Jan 2019 12:00:46pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPrimitives.h"
#include "sspObjectVector.h"

class sspOr : public sspConditional
{
private:
	sspObjectVector<sspConditional> operands_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspConditional);
		ar & BOOST_SERIALIZATION_NVP(operands_);
	}

public:
	sspOr() = default;
	sspOr(const sspOr& cond) = delete;
	sspOr& operator= (const sspOr& cond) = delete;
	virtual ~sspOr() {}

	// Virtual methods
	virtual bool isTrue() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setOperands(const sspObjectVector<sspConditional>& ops) { operands_ = ops; }
	const sspObjectVector<sspConditional>& getOperands() const { return operands_; }
};