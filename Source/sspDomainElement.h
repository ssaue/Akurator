/*
  ==============================================================================

    sspDomainElement.h
    Created: 3 Jan 2019 12:28:24pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include <string_view>

#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/assume_abstract.hpp>

class sspDomainElement
{
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_NVP(name_);
	}

protected:
	std::string name_{ "" };

public:
	sspDomainElement() : name_("") {}
	sspDomainElement(const sspDomainElement& obj) = delete;
	sspDomainElement& operator= (const sspDomainElement& obj) = delete;
	virtual ~sspDomainElement() {}

	std::string_view getName() const { return name_; }
	void setName(std::string_view name) { name_ = name; }

	// Verify correctness (returns false if there are errors or warnings)
	// Details on errors and warnings should be logged to file (Boost.Log)
	virtual bool verify(int& nErrors, int& nWarnings) const = 0;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(sspDomainElement)
