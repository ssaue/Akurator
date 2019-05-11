/*
  ==============================================================================

    sspDomainPool.h
    Created: 4 Jan 2019 11:08:42am
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspSharedVector.h"

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

template <typename T>
class sspDomainPool : public sspSharedVector<T>
{
	typedef  sspSharedVector<T> sharedVectorBase;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sharedVectorBase);
	}

public:
	sspDomainPool();
	virtual ~sspDomainPool() {}

	bool verify(int& nErrors, int& nWarnings) const;
};
