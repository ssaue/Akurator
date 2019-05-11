/*
  ==============================================================================

    sspWeakVector.h
    Created: 10 May 2019 10:55:46pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

#include <memory>
#include <vector>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/weak_ptr.hpp>
#include <boost/serialization/shared_ptr.hpp>

template <typename T>
class sspSharedVector : public std::vector<std::shared_ptr<T>>
{
	typedef std::vector<std::shared_ptr<T>> sharedBase;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sharedBase);
	}

public:
	sspSharedVector() : std::vector<std::shared_ptr<T>>() {}
	virtual ~sspSharedVector() {}
};

template <typename T>
class sspWeakVector : public std::vector<std::weak_ptr<T>>
{
	typedef std::vector<std::weak_ptr<T>> weakBase;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(weakBase);
	}

public:
	sspWeakVector() : std::vector<std::weak_ptr<T>>() {}
	virtual ~sspWeakVector() {}
};

