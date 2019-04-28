/*
  ==============================================================================

    sspTabbedComponent.cpp
    Created: 28 Apr 2019 5:48:09pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "sspTabbedComponent.h"
#include "sspSettingsPage.h"


sspTabbedComponent::sspTabbedComponent()
	: TabbedComponent(TabbedButtonBar::TabsAtTop)
{
	auto colour = findColour(ResizableWindow::backgroundColourId);

	addTab("Settings", colour, new sspSettingsPage(), true);
	//addTab("Sliders", colour, new SlidersPage(), true);
	//addTab("Toolbars", colour, new ToolbarDemoComp(), true);
	//addTab("Misc", colour, new MiscPage(), true);
	//addTab("Tables", colour, new TableDemoComponent(), true);
	//addTab("Drag & Drop", colour, new DragAndDropDemo(), true);
}
