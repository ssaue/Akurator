/*
  ==============================================================================

    sspInputManager.h
    Created: 16 Apr 2019 2:18:22pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

#include "sspInput.h"
#include "sspDomainPool.h"

class sspInputManager
{
	sspDomainPool<sspInput> inputs_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_NVP(inputs_);
	}

public:
	sspInputManager() 
		: inputs_() {}
	sspInputManager(const sspInputManager&) = delete;
	sspInputManager& operator=(const sspInputManager&) = delete;
	virtual ~sspInputManager() {}

	bool verify(int& nErrors, int& nWarnings) const;

	bool initialize();
	bool update();
	void terminate();

	void clearContents();

	sspDomainPool<sspInput>&	getInputs() { return inputs_; }
};
