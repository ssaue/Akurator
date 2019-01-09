/*
  ==============================================================================

    sspConditionalValue.h
    Created: 7 Jan 2019 3:34:18pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPrimitives.h"
#include "sspObjectVector.h"

class sspConditionalValue : public sspValue
{
	sspObjectVector<sspConditional> conditionals_;
	sspObjectVector<sspValue> values_;
	std::shared_ptr<sspValue> defaultValue_;
	
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspValue);
		ar & BOOST_SERIALIZATION_NVP(conditionals_);
		ar & BOOST_SERIALIZATION_NVP(values_);
		ar & BOOST_SERIALIZATION_NVP(defaultValue_);
	}

public:
	sspConditionalValue() = default;
	sspConditionalValue(const sspConditionalValue& val) = delete;
	sspConditionalValue& operator= (const sspConditionalValue& val) = delete;
	virtual ~sspConditionalValue() {}

	// Virtual methods
	virtual double getValue() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setConditionals(const sspObjectVector<sspConditional>& conds) { conditionals_ = conds; }
	void setValues(const sspObjectVector<sspValue>& values) { values_ = values; }
	void setDefaultValue(std::shared_ptr<sspValue> value) { defaultValue_ = std::move(value); }

	const sspObjectVector<sspValue>& getValues() const { return values_; }
	const sspObjectVector<sspConditional>& getConditionals() const { return conditionals_; }
	std::shared_ptr<sspValue> getDefaultValue() const { return defaultValue_; }
};

