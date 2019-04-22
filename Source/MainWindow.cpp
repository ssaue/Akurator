/*
  ==============================================================================

    MainWindow.cpp
    Created: 22 Apr 2019 11:15:40pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "MainWindow.h"

MainWindow::MainWindow(String name, String path) 
	: DocumentWindow(name, Desktop::getInstance().getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId), 	DocumentWindow::allButtons)
{
	setUsingNativeTitleBar(false);
	setContentOwned(new MainComponent(path), true);

#if JUCE_IOS || JUCE_ANDROID
	setFullScreen(true);
#else
	setResizable(true, true);
	centreWithSize(getWidth(), getHeight());
#endif

	setVisible(true);
}

void MainWindow::closeButtonPressed()
{
	// This is called when the user tries to close this window. Here, we'll just
	// ask the app to quit when this happens, but you can change this to do
	// whatever you need.
	JUCEApplication::getInstance()->systemRequestedQuit();
}
