/*
  ==============================================================================

    MainWindow.h
    Created: 22 Apr 2019 11:15:40pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"

//==============================================================================
/*
	This class implements the desktop window that contains an instance of
	our MainComponent class.
*/

class MainWindow : public DocumentWindow
{
public:
	MainWindow(String name, String path);

	void closeButtonPressed() override;

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
};
