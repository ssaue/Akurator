/*
  ==============================================================================

    sspSelectString.h
    Created: 14 Jan 2019 2:20:50pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "domain/core/sspDomainPrimitives.h"
#include "domain/core/sspSharedVector.h"

class sspSelectString : public sspString
{
	sspWeakVector<sspString> strings_;
	std::weak_ptr<sspValue> value_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspString);
		ar & BOOST_SERIALIZATION_NVP(strings_);
		ar & BOOST_SERIALIZATION_NVP(value_);
	}

public:
	sspSelectString();
	sspSelectString(const sspSelectString& cond) = delete;
	sspSelectString& operator= (const sspSelectString& cond) = delete;
	virtual ~sspSelectString() {}

	// Virtual methods
	virtual std::string getString() const override;
	virtual bool verify(int& /*nErrors*/, int& /*nWarnings*/) const override;

	// Accessors
	void setStrings(const sspWeakVector<sspString>& strings) { strings_ = strings; }
	void setValue(std::weak_ptr<sspValue> value) { value_ = std::move(value); }

	const sspWeakVector<sspString>& getStrings() const { return strings_; }
	std::weak_ptr<sspValue> getValue() const { return value_; }
};

