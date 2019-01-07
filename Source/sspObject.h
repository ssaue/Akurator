/*
  ==============================================================================

    sspObject.h
    Created: 3 Jan 2019 12:28:24pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include <string_view>

#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/assume_abstract.hpp>

class sspObject
{
protected:
	std::string name_ { "" };

public:
	sspObject() = default;
	sspObject(const sspObject& obj) = delete;
	sspObject& operator= (const sspObject& obj) = delete;
	virtual ~sspObject() {}

	std::string_view getName() const { return name_; }
	void setName(std::string_view name) { name_ = name; }

	// Verify correctness (returns false if there are errors or warnings)
	// Details on errors and warnings should be logged to file (Boost.Log)
	virtual bool verify(int& nErrors, int& nWarnings) const = 0;

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_NVP(name_);
	}
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(sspObject)
