/*
  ==============================================================================

    sspAkuratorApplication.cpp
    Created: 22 Apr 2019 11:10:46pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "sspAkuratorApplication.h"

sspAkuratorApplication::sspAkuratorApplication()
{
}

sspAkuratorApplication& sspAkuratorApplication::getApp()
{
	sspAkuratorApplication* const app = dynamic_cast<sspAkuratorApplication*> (JUCEApplication::getInstance());
	jassert(app != nullptr);
	return *app;
}

ApplicationCommandManager& sspAkuratorApplication::getCommandManager()
{
	auto* cm = sspAkuratorApplication::getApp().command_manager_.get();
	jassert(cm != nullptr);
	return *cm;
}

RecentlyOpenedFilesList & sspAkuratorApplication::getRecentlyOpenedFiles()
{
	auto* files = sspAkuratorApplication::getApp().recent_files_.get();
	jassert(files != nullptr);
	return *files;
}


void sspAkuratorApplication::initialise(const String& commandLine)
{
	// This method is where you should put your application's initialisation code..

	// Get the optional commandLine argument
	StringArray arguments = StringArray::fromTokens(commandLine, true);
	String path = arguments.isEmpty() ? String() : arguments[0];

	recent_files_.reset(new RecentlyOpenedFilesList());

	command_manager_.reset(new ApplicationCommandManager());
	command_manager_->registerAllCommandsForTarget(this);

	main_window_.reset(new MainWindow(getApplicationName(), path));
}

void sspAkuratorApplication::shutdown()
{
	// Add your application's shutdown code here..

	main_window_ = nullptr; // (deletes our window)
}

void sspAkuratorApplication::systemRequestedQuit()
{
	// This is called when the app is being asked to quit: you can ignore this
	// request and let the app carry on running, or call quit() to allow the app to close.
	quit();
}

void sspAkuratorApplication::anotherInstanceStarted(const String& /*commandLine*/)
{
	// When another instance of the app is launched while this one is running,
	// this method is invoked, and the commandLine parameter tells you what
	// the other instance's command-line arguments were.
}
