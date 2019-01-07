/*
  ==============================================================================

    sspPool.cpp
    Created: 4 Jan 2019 11:08:42am
    Author:  sigurds

  ==============================================================================
*/

#include "sspPool.h"
#include "sspPrimitives.h"
#include <boost/log/trivial.hpp>

template <typename T>
sspPool<T>::~sspPool()
{
	elements_.clear();
}

template <typename T>
void sspPool<T>::add(std::shared_ptr<T> element)
{
	elements_.push_back(element);
}

template <typename T>
std::shared_ptr<T> sspPool<T>::getAt(size_t const index) const
{
	assert(index < size());
	return elements_[index];
}

template <typename T>
void sspPool<T>::clear()
{
	elements_.clear();
}

template <typename T>
bool sspPool<T>::verify(int& nErrors, int& nWarnings) const
{
	bool bReturn = true;
	if (elements_.empty()) {
		nWarnings++;
		BOOST_LOG_TRIVIAL(warning) << getName() << " is empty";
	}
	for (auto&& element : elements_) {
		if (!element->verify(nErrors, nWarnings)) {
			bReturn = false;
		}
	}

	return bReturn;
}

// Instantiate sspPool templates
template class sspPool<sspValue>;
template class sspPool<sspConditional>;
template class sspPool<sspString>;
