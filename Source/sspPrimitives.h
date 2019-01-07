/*
  ==============================================================================

    sspPrimitives.h
    Created: 3 Jan 2019 11:00:02pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspObject.h"
#include <boost/serialization/base_object.hpp>

class sspValue : public sspObject
{
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspObject);
	}

public:
	sspValue() = default;
	sspValue(const sspValue& obj) = delete;
	sspValue& operator= (const sspValue& obj) = delete;
	virtual ~sspValue() {}

	virtual float getValue() const = 0;
	explicit operator float() const { return getValue(); }

};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(sspValue)

class sspConditional : public sspObject
{
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspObject);
	}

public:
	sspConditional() = default;
	sspConditional(const sspConditional& obj) = delete;
	sspConditional& operator= (const sspConditional& obj) = delete;
	virtual ~sspConditional() {}

	virtual bool isTrue() const = 0;
	explicit operator bool() const { return isTrue(); }
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(sspConditional)

class sspString : public sspObject
{
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspObject);
	}

public:
	sspString() = default;
	sspString(const sspString& obj) = delete;
	sspString& operator= (const sspString& obj) = delete;
	virtual ~sspString() {}

	virtual std::string_view getString() const = 0;
	explicit operator std::string_view() const { return getString(); }
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(sspString)

class sspDummy : public sspValue
{
public:
	sspDummy() = default;
	sspDummy(const sspDummy& obj) = delete;
	sspDummy& operator= (const sspDummy& obj) = delete;
	virtual ~sspDummy() {}

	virtual float getValue() const override { return 1.0f; }
	virtual bool verify(int& , int& ) const override { return true; }

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspValue);
	}
};
