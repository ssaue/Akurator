/*
  ==============================================================================

    sspConcatString.h
    Created: 14 Jan 2019 2:21:05pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPrimitives.h"
#include "sspObjectVector.h"

class sspConcatString : public sspString
{
	sspObjectVector<sspString> strings_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspString);
		ar & BOOST_SERIALIZATION_NVP(strings_);
	}

public:
	sspConcatString() = default;
	sspConcatString(const sspConcatString& cond) = delete;
	sspConcatString& operator= (const sspConcatString& cond) = delete;
	virtual ~sspConcatString() {}

	// Virtual methods
	virtual std::string_view getString() const override;
	virtual bool verify(int& /*nErrors*/, int& /*nWarnings*/) const override;

	// Accessors
	void setStrings(const sspObjectVector<sspString>& strings) { strings_ = strings; }
	const sspObjectVector<sspString>& getStrings() const { return strings_; }
};

