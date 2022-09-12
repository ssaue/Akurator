/*
  ==============================================================================

    sspInputManager.cpp
    Created: 16 Apr 2019 2:18:22pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "sspInputManager.h"

bool sspInputManager::verify(int& /*nErrors*/, int& /*nWarnings*/) const
{
	return true;
}

bool sspInputManager::initialize(sspDomainPool<sspInput>* inputs)
{
	if (inputs == nullptr)
		return false;

	inputs_ = inputs;
	for (auto input : *inputs_) {
		if (!input->initialize())
			return false;
	}
	return true;
}

bool sspInputManager::update()
{
	if (inputs_ == nullptr)
		return false;

	bool update = false;
	for (auto input : *inputs_) {
		if (input->update())
			update = true;	// At least one input is updated
	}
	return update;
}

void sspInputManager::terminate()
{
	if (inputs_ == nullptr)
		return;

	for (auto input : *inputs_) {
		input->terminate();
	}
}
