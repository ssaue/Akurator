/*
  ==============================================================================

    sspDomainPool.h
    Created: 4 Jan 2019 11:08:42am
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspDomainVector.h"

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

template <typename T>
class sspDomainPool : public sspDomainVector<T>
{
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspDomainVector);
	}

public:
	sspDomainPool();
	sspDomainPool(const sspDomainPool& obj) = delete;
	sspDomainPool& operator= (const sspDomainPool& obj) = delete;
	virtual ~sspDomainPool() {}

	bool verify(int& nErrors, int& nWarnings) const;
};
