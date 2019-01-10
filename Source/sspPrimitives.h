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

	virtual double getValue() const = 0;
	explicit operator double() const { return getValue(); }

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

class sspPlayObject : public sspObject
{
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspObject);
	}

public:
	sspPlayObject() = default;
	sspPlayObject(const sspPlayObject& obj) = delete;
	sspPlayObject& operator= (const sspPlayObject& obj) = delete;
	virtual ~sspPlayObject() {}

	virtual bool isPlaying() const = 0;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(sspPlayObject)
