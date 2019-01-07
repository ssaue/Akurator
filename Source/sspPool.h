/*
  ==============================================================================

    sspPool.h
    Created: 4 Jan 2019 11:08:42am
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspObject.h"

#include <vector>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

template <typename T>
class sspPool : public sspObject 
{
	std::vector<std::shared_ptr<T>> elements_;

public:
	sspPool() = default;
	virtual ~sspPool();

	void add(std::shared_ptr<T> element);
	std::shared_ptr<T> getAt(size_t const index) const;
	void clear();

	size_t size() const { return elements_.size(); }
	bool empty() const { return elements_.empty(); }
	
	virtual bool verify(int& nErrors, int& nWarnings) const override;

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspObject);
		ar & BOOST_SERIALIZATION_NVP(elements_);
	}
};

// sspPool iterators

template <typename T, typename C>
class sspPool_iterator_type
{
public:
	sspPool_iterator_type(C& collection, size_t const index) :
		index(index), collection(collection)
	{
	}

	bool operator!= (sspPool_iterator_type const & other) const
	{
		return index != other.index;
	}

	std::shared_ptr<T> const & operator* () const
	{
		return collection.getAt(index);
	}

	sspPool_iterator_type const & operator++ ()
	{
		++index;
		return *this;
	}

private:
	size_t   index;
	C&       collection;
};

template <typename T>
using sspPool_iterator = sspPool_iterator_type<T, sspPool<T>>;

template <typename T>
using sspPool_const_iterator = sspPool_iterator_type<T, sspPool<T> const>;

template <typename T>
inline sspPool_iterator<T> begin(sspPool<T>& collection)
{
	return sspPool_iterator<T>(collection, 0);
}

template <typename T>
inline sspPool_iterator<T> end(sspPool<T>& collection)
{
	return sspPool_iterator<T>(collection, collection.size());
}

template <typename T>
inline sspPool_const_iterator<T> begin(sspPool<T> const & collection)
{
	return sspPool_const_iterator<T>(collection, 0);
}

template <typename T>
inline sspPool_const_iterator<T> end(sspPool<T> const & collection)
{
	return sspPool_const_iterator<T>(collection, collection.size());
}
