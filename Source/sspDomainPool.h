/*
  ==============================================================================

    sspDomainPool.h
    Created: 4 Jan 2019 11:08:42am
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspDomainElement.h"
#include "sspDomainVector.h"

#include <vector>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

template <typename T>
class sspDomainPool : public sspDomainElement, public sspDomainVector<T>
{
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspDomainElement);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspDomainVector);
	}

public:
	sspDomainPool();
	sspDomainPool(const sspDomainPool& obj) = delete;
	sspDomainPool& operator= (const sspDomainPool& obj) = delete;
	virtual ~sspDomainPool() {}

	virtual bool verify(int& nErrors, int& nWarnings) const override;
};

// sspDomainPool iterators

template <typename T, typename C>
class sspDomainPool_iterator_type
{
	size_t   index;
	C&       collection;

public:
	sspDomainPool_iterator_type(C& collection, size_t const index) :
		index(index), collection(collection)
	{
	}

	bool operator!= (sspDomainPool_iterator_type const & other) const
	{
		return index != other.index;
	}

	std::shared_ptr<T> const & operator* () const
	{
		return collection.getAt(index);
	}

	sspDomainPool_iterator_type const & operator++ ()
	{
		++index;
		return *this;
	}
};

template <typename T>
using sspDomainPool_iterator = sspDomainPool_iterator_type<T, sspDomainPool<T>>;

template <typename T>
using sspDomainPool_const_iterator = sspDomainPool_iterator_type<T, sspDomainPool<T> const>;

template <typename T>
inline sspDomainPool_iterator<T> begin(sspDomainPool<T>& collection)
{
	return sspDomainPool_iterator<T>(collection, 0);
}

template <typename T>
inline sspDomainPool_iterator<T> end(sspDomainPool<T>& collection)
{
	return sspDomainPool_iterator<T>(collection, collection.size());
}

template <typename T>
inline sspDomainPool_const_iterator<T> begin(sspDomainPool<T> const & collection)
{
	return sspDomainPool_const_iterator<T>(collection, 0);
}

template <typename T>
inline sspDomainPool_const_iterator<T> end(sspDomainPool<T> const & collection)
{
	return sspDomainPool_const_iterator<T>(collection, collection.size());
}
