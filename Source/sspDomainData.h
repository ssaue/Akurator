/*
  ==============================================================================

    sspDomainData.h
    Created: 4 Jan 2019 1:27:47pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPrimitives.h"
#include "sspPlayer.h"
#include "sspPlayTask.h"

#include "sspPool.h"

class sspDomainData : public sspObject
{
	sspPool<sspValue>		values_;
	sspPool<sspConditional>	conditionals_;
	sspPool<sspString>		strings_;
	sspPool<sspPlayer>		players_;
	sspPool<sspPlayTask>	tasks_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspObject);
		ar & BOOST_SERIALIZATION_NVP(values_);
		ar & BOOST_SERIALIZATION_NVP(conditionals_);
		ar & BOOST_SERIALIZATION_NVP(strings_);
		ar & BOOST_SERIALIZATION_NVP(players_);
	}

public:
	sspDomainData();
	sspDomainData(const sspDomainData&) = delete;
	sspDomainData& operator=(const sspDomainData&) = delete;
	~sspDomainData() {}
	
	virtual bool verify(int& nErrors, int& nWarnings) const override;
};
