/*
  ==============================================================================

    sspSimpleString.h
    Created: 14 Jan 2019 2:20:17pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "domain/core/sspDomainPrimitives.h"
#include <boost/serialization/string.hpp>

class sspSimpleString : public sspString
{
private:
	std::string str_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspString);
		ar & BOOST_SERIALIZATION_NVP(str_);
	}

public:
	sspSimpleString() : sspString(), str_("") {}
	sspSimpleString(const sspSimpleString& cond) = delete;
	sspSimpleString& operator= (const sspSimpleString& cond) = delete;
	virtual ~sspSimpleString() {}

	// Virtual methods
	virtual std::string getString() const override { return str_; }
	virtual bool verify(int& /*nErrors*/, int& /*nWarnings*/) const override { return true; }

	// Accessors
	void setString(std::string_view str) { str_ = str; }
};

