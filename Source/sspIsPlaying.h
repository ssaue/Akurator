/*
  ==============================================================================

    sspIsPlaying.h
    Created: 10 Jan 2019 12:00:30pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspDomainPrimitives.h"
#include "sspDomainVector.h"

class sspIsPlaying : public sspConditional
{
private:
	sspDomainVector<sspPlayObject> players_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspConditional);
		ar & BOOST_SERIALIZATION_NVP(players_);
	}

public:
	sspIsPlaying();
	sspIsPlaying(const sspIsPlaying& cond) = delete;
	sspIsPlaying& operator= (const sspIsPlaying& cond) = delete;
	virtual ~sspIsPlaying() {}

	// Virtual methods
	virtual bool isTrue() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setPLayers(const sspDomainVector<sspPlayObject>& ops) { players_ = ops; }
	const sspDomainVector<sspPlayObject>& getPlayers() const { return players_; }
};
