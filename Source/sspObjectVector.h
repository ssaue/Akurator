/*
  ==============================================================================

    sspObjectVector.h
    Created: 7 Jan 2019 4:20:33pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include <vector>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

template <typename T>
class sspObjectVector
{
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_NVP(elements_);
	}

protected:
	std::vector<std::shared_ptr<T>> elements_;

public:
	sspObjectVector() = default;
	sspObjectVector(const sspObjectVector& other) 
	{ 
		elements_ = other.elements_; 
	}
	sspObjectVector& operator= (const sspObjectVector& other)
	{
		if (this != &other) {
			elements_.clear();
			elements_ = other.elements_;
		}
		return *this;
	}
	sspObjectVector(sspObjectVector&& other)				// Move constructor
	{
		elements_ = std::move(other.elements_);
	}
	sspObjectVector& operator= (sspObjectVector&& other)	// Move assignment
	{
		if (this != &other) {
			elements_.clear();
			elements_ = std::move(other.elements_);
		}
		return *this;
	}
	virtual ~sspObjectVector() {}

	void add(std::shared_ptr<T> element) { elements_.push_back(element); }
	const std::shared_ptr<T> getAt(size_t const index) const
	{
		assert(index < size());
		return elements_[index];
	}
	const std::shared_ptr<T> getLast() const
	{
		return elements_[size() - 1];
	}
	void clear() { elements_.clear(); }

	size_t size() const { return elements_.size(); }
	bool empty() const { return elements_.empty(); }
};

// sspObjectVector iterators

template <typename T, typename C>
class sspObjectVector_iterator_type
{
	size_t   index;
	C&       collection;

public:
	sspObjectVector_iterator_type(C& collection, size_t const index) :
		index(index), collection(collection)
	{
	}

	sspObjectVector_iterator_type(const sspObjectVector_iterator_type& other) :
		index(other.index), collection(other.collection)
	{
	}

	sspObjectVector_iterator_type& operator=(const sspObjectVector_iterator_type& other)
	{
		if (this == &other)
			return *this;
		index = other.index;
		collection = other.collection;
		return *this;
	}

	bool operator!= (sspObjectVector_iterator_type const & other) const
	{
		return index != other.index;
	}

	const std::shared_ptr<T> operator* () const
	{
		return collection.getAt(index);
	}

	sspObjectVector_iterator_type const & operator++ ()
	{
		++index;
		return *this;
	}
};

template <typename T>
using sspObjectVector_iterator = sspObjectVector_iterator_type<T, sspObjectVector<T>>;

template <typename T>
using sspObjectVector_const_iterator = sspObjectVector_iterator_type<T, sspObjectVector<T> const>;

template <typename T>
inline sspObjectVector_iterator<T> begin(sspObjectVector<T>& collection)
{
	return sspObjectVector_iterator<T>(collection, 0);
}

template <typename T>
inline sspObjectVector_iterator<T> end(sspObjectVector<T>& collection)
{
	return sspObjectVector_iterator<T>(collection, collection.size());
}

template <typename T>
inline sspObjectVector_const_iterator<T> begin(sspObjectVector<T> const & collection)
{
	return sspObjectVector_const_iterator<T>(collection, 0);
}

template <typename T>
inline sspObjectVector_const_iterator<T> end(sspObjectVector<T> const & collection)
{
	return sspObjectVector_const_iterator<T>(collection, collection.size());
}
