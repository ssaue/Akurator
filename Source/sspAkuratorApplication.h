/*
  ==============================================================================

    sspAkuratorApplication.h
    Created: 22 Apr 2019 11:10:46pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainWindow.h"

//==============================================================================
class sspAkuratorApplication : public JUCEApplication
{
public:
	//==============================================================================
	sspAkuratorApplication();

	static sspAkuratorApplication& getApp();
	static ApplicationCommandManager& getCommandManager();

	const String getApplicationName() override { return ProjectInfo::projectName; }
	const String getApplicationVersion() override { return ProjectInfo::versionString; }
	bool moreThanOneInstanceAllowed() override { return false; }

	//==============================================================================

	void initialise(const String& commandLine) override;
	void shutdown() override;

	//==============================================================================

	void systemRequestedQuit() override;
	void anotherInstanceStarted(const String& commandLine) override;

	std::unique_ptr<ApplicationCommandManager> command_manager_;

private:
	std::unique_ptr<MainWindow> main_window_;
};
