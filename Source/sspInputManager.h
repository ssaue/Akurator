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
public:
	sspInputManager() : inputs_() {}
	sspInputManager(const sspInputManager&) = delete;
	sspInputManager& operator=(const sspInputManager&) = delete;
	virtual ~sspInputManager() {}

	bool verify(int& nErrors, int& nWarnings) const;

	bool initialize(sspDomainPool<sspInput>* inputs);
	bool update();
	void terminate();

private:
	sspDomainPool<sspInput>* inputs_;
};
