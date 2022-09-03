/*
  ==============================================================================

    sspConditionalValue.h
    Created: 7 Jan 2019 3:34:18pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "domain/core/sspDomainPrimitives.h"
#include "domain/core/sspSharedVector.h"

class sspConditionalValue : public sspValue
{
	sspWeakVector<sspConditional> conditionals_;
	sspWeakVector<sspValue> values_;
	std::weak_ptr<sspValue> default_value_;
	
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspValue);
		ar & BOOST_SERIALIZATION_NVP(conditionals_);
		ar & BOOST_SERIALIZATION_NVP(values_);
		ar & BOOST_SERIALIZATION_NVP(default_value_);
	}

public:
	sspConditionalValue();
	sspConditionalValue(const sspConditionalValue& val) = delete;
	sspConditionalValue& operator= (const sspConditionalValue& val) = delete;
	virtual ~sspConditionalValue() {}

	// Virtual methods
	virtual double getValue() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setConditionals(const sspWeakVector<sspConditional>& conds) { conditionals_ = conds; }
	void setValues(const sspWeakVector<sspValue>& values) { values_ = values; }
	void setDefaultValue(std::weak_ptr<sspValue> value) { default_value_ = std::move(value); }

	const sspWeakVector<sspValue>& getValues() const { return values_; }
	const sspWeakVector<sspConditional>& getConditionals() const { return conditionals_; }
	std::weak_ptr<sspValue> getDefaultValue() const { return default_value_; }
};

