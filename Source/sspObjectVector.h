/*
  ==============================================================================

    sspObjectVector.h
    Created: 7 Jan 2019 4:20:33pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

/*
  ==============================================================================

	sspObjectVector.h
	Created: 4 Jan 2019 11:08:42am
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
	std::shared_ptr<const T> getAt(size_t const index) const
	{
		assert(index < size());
		return elements_[index];
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

	bool operator!= (sspObjectVector_iterator_type const & other) const
	{
		return index != other.index;
	}

	std::shared_ptr<const T> operator* () const
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
