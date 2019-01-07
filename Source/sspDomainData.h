/*
  ==============================================================================

    sspDomainData.h
    Created: 4 Jan 2019 1:27:47pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspObject.h"
#include "sspPrimitives.h"
#include "sspPool.h"

class sspDomainData : public sspObject
{
private:
	sspPool<sspValue>		values_;
	sspPool<sspConditional>	conditionals_;
	sspPool<sspString>		strings_;

public:
	sspDomainData() = default;
	sspDomainData(const sspDomainData&) = delete;
	sspDomainData& operator=(const sspDomainData&) = delete;
	~sspDomainData() {}
	
	virtual bool verify(int& nErrors, int& nWarnings) const override;

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspObject);
		ar & BOOST_SERIALIZATION_NVP(values_);
		ar & BOOST_SERIALIZATION_NVP(conditionals_);
		ar & BOOST_SERIALIZATION_NVP(strings_);
	}
};
