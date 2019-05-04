/*
  ==============================================================================

    sspTabbedComponent.h
    Created: 28 Apr 2019 5:48:09pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class sspDomainData;

class sspTabbedComponent : public TabbedComponent
{
public:
	sspTabbedComponent(sspDomainData* domain);

private:
	sspDomainData* domain_;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(sspTabbedComponent)
};
