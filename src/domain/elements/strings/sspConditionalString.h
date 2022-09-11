/*
  ==============================================================================

    sspConditionalString.h
    Created: 14 Jan 2019 2:20:50pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "domain/core/sspDomainPrimitives.h"
#include "domain/core/sspSharedVector.h"

class sspConditionalString : public sspString
{
	sspWeakVector<sspConditional> conditionals_;
	sspWeakVector<sspString> strings_;
	std::weak_ptr<sspString> default_string_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspString);
		ar & BOOST_SERIALIZATION_NVP(conditionals_);
		ar & BOOST_SERIALIZATION_NVP(strings_);
		ar & BOOST_SERIALIZATION_NVP(default_string_);
	}

public:
	sspConditionalString();
	sspConditionalString(const sspConditionalString& cond) = delete;
	sspConditionalString& operator= (const sspConditionalString& cond) = delete;
	virtual ~sspConditionalString() {}

	// Virtual methods
	virtual std::string getString() const override;
	virtual bool verify(int& /*nErrors*/, int& /*nWarnings*/) const override;

	// Accessors
	void setConditionals(const sspWeakVector<sspConditional>& conds) { conditionals_ = conds; }
	void setStrings(const sspWeakVector<sspString>& strings) { strings_ = strings; }
	void setDefaultString(std::weak_ptr<sspString> str) { default_string_ = std::move(str); }

	const sspWeakVector<sspConditional>& getConditionals() const { return conditionals_; }
	const sspWeakVector<sspString>& getStrings() const { return strings_; }
	std::weak_ptr<sspString> getDefaultString() const { return default_string_; }
};

