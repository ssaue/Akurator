/*
  ==============================================================================

    sspDomainVector.h
    Created: 7 Jan 2019 4:20:33pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include <vector>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

template <typename T>
class sspDomainVector
{
	std::vector<std::shared_ptr<T>> elements_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_NVP(elements_);
	}

public:
	sspDomainVector() : elements_() {}
	sspDomainVector(const sspDomainVector& other) 
	{ 
		elements_ = other.elements_; 
	}
	sspDomainVector& operator= (const sspDomainVector& other)
	{
		if (this != &other) {
			elements_.clear();
			elements_ = other.elements_;
		}
		return *this;
	}
	sspDomainVector(sspDomainVector&& other)				// Move constructor
	{
		elements_ = std::move(other.elements_);
	}
	sspDomainVector& operator= (sspDomainVector&& other)	// Move assignment
	{
		if (this != &other) {
			elements_.clear();
			elements_ = std::move(other.elements_);
		}
		return *this;
	}
	virtual ~sspDomainVector() {}

	void add(std::shared_ptr<T> element) 
	{ 
		elements_.push_back(element); 
	}
	
	void removeAt(size_t const index)
	{
		assert(index < size());
		auto elem = elements_.begin() + index;
		elements_.erase(elem);
	}

	const std::shared_ptr<T> getAt(size_t const index) const
	{
		assert(index < size());
		return elements_[index];
	}

	const std::shared_ptr<T> getLast() const
	{
		return elements_[size() - 1];
	}

	void clear() 
	{ 
		elements_.clear(); 
	}

	size_t size() const
	{ 
		return elements_.size(); 
	}

	bool empty() const 
	{ 
		return elements_.empty(); 
	}
};

// sspDomainVector iterators

template <typename T, typename C>
class sspDomainVector_iterator_type
{
	size_t   index;
	C&       collection;

public:
	sspDomainVector_iterator_type(C& collection, size_t const index) :
		index(index), collection(collection)
	{
	}

	sspDomainVector_iterator_type(const sspDomainVector_iterator_type& other) :
		index(other.index), collection(other.collection)
	{
	}

	sspDomainVector_iterator_type& operator=(const sspDomainVector_iterator_type& other)
	{
		if (this == &other)
			return *this;
		index = other.index;
		collection = other.collection;
		return *this;
	}

	bool operator!= (sspDomainVector_iterator_type const & other) const
	{
		return index != other.index;
	}

	const std::shared_ptr<T> operator* () const
	{
		return collection.getAt(index);
	}

	sspDomainVector_iterator_type const & operator++ ()
	{
		++index;
		return *this;
	}
};

template <typename T>
using sspDomainVector_iterator = sspDomainVector_iterator_type<T, sspDomainVector<T>>;

template <typename T>
using sspDomainVector_const_iterator = sspDomainVector_iterator_type<T, sspDomainVector<T> const>;

template <typename T>
inline sspDomainVector_iterator<T> begin(sspDomainVector<T>& collection)
{
	return sspDomainVector_iterator<T>(collection, 0);
}

template <typename T>
inline sspDomainVector_iterator<T> end(sspDomainVector<T>& collection)
{
	return sspDomainVector_iterator<T>(collection, collection.size());
}

template <typename T>
inline sspDomainVector_const_iterator<T> begin(sspDomainVector<T> const & collection)
{
	return sspDomainVector_const_iterator<T>(collection, 0);
}

template <typename T>
inline sspDomainVector_const_iterator<T> end(sspDomainVector<T> const & collection)
{
	return sspDomainVector_const_iterator<T>(collection, collection.size());
}
