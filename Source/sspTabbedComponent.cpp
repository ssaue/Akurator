/*
  ==============================================================================

    sspTabbedComponent.cpp
    Created: 28 Apr 2019 5:48:09pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "sspTabbedComponent.h"
#include "sspDomainData.h"
#include "sspSettingsPage.h"
#include "sspDomainPage.h"


sspTabbedComponent::sspTabbedComponent(sspDomainData* domain)
	: TabbedComponent(TabbedButtonBar::TabsAtTop)
{
	auto colour = findColour(ResizableWindow::backgroundColourId);

	addTab("Domain", colour, new sspDomainPage(domain), true);
	addTab("Settings", colour, new sspSettingsPage(), true);
}
