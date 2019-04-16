/*
  ==============================================================================

    sspInputManager.cpp
    Created: 16 Apr 2019 2:18:22pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "sspInputManager.h"

bool sspInputManager::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;
	if (!inputs_.verify(nErrors, nWarnings))
		bReturn = false;
	return bReturn;
}

bool sspInputManager::initialize()
{
	for (auto input : inputs_) {
		if (!input->initialize())
			return false;
	}
	return true;
}

bool sspInputManager::update()
{
	bool update = false;
	for (auto input : inputs_) {
		if (!input->update())
			update = true;	// At least one input is updated
	}
	return update;
}

void sspInputManager::terminate()
{
	for (auto input : inputs_) {
		input->terminate();
	}
}

void sspInputManager::clearContents()
{
	terminate();
	inputs_.clear();
}
