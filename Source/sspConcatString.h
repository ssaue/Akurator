/*
  ==============================================================================

    sspConcatString.h
    Created: 14 Jan 2019 2:21:05pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspDomainPrimitives.h"
#include "sspSharedVector.h"

class sspConcatString : public sspString
{
	sspWeakVector<sspString> strings_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspString);
		ar & BOOST_SERIALIZATION_NVP(strings_);
	}

public:
	sspConcatString();
	sspConcatString(const sspConcatString& cond) = delete;
	sspConcatString& operator= (const sspConcatString& cond) = delete;
	virtual ~sspConcatString() {}

	// Virtual methods
	virtual std::string getString() const override;
	virtual bool verify(int& /*nErrors*/, int& /*nWarnings*/) const override;

	// Accessors
	void setStrings(const sspWeakVector<sspString>& strings) { strings_ = strings; }
	const sspWeakVector<sspString>& getStrings() const { return strings_; }
};

