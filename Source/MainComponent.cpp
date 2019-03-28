/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

#include "sspDomainData.h"
#include "sspAudioStream.h"
#include "sspOscConsole.h"

#include <fstream>
#include <boost/archive/xml_oarchive.hpp> 
#include <boost/archive/xml_iarchive.hpp> 

//==============================================================================
MainComponent::MainComponent()
{
	menuBar_.reset(new MenuBarComponent(this));
	addAndMakeVisible(menuBar_.get());
	setApplicationCommandManagerToWatch(&commandManager_);
	commandManager_.registerAllCommandsForTarget(this);
	addKeyListener(commandManager_.getKeyMappings());

    setSize (600, 400);

	PropertiesFile::Options options;
	options.applicationName = ProjectInfo::projectName;
	options.folderName = File::getSpecialLocation(File::SpecialLocationType::userApplicationDataDirectory).getChildFile(ProjectInfo::projectName).getFullPathName();
	options.filenameSuffix = ".settings";
	options.osxLibrarySubFolder = "Application Support";
	options.storageFormat = PropertiesFile::storeAsXML;
	app_properties_.setStorageParameters(options);

	loadProperties();
}

MainComponent::~MainComponent()
{
	saveProperties();
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainComponent::resized()
{
	auto b = getLocalBounds();
	menuBar_->setBounds(b.removeFromTop(LookAndFeel::getDefaultLookAndFeel().getDefaultMenuBarHeight()));
}

//==============================================================================
StringArray MainComponent::getMenuBarNames()
{
	return { "File", "Edit" };
}

PopupMenu MainComponent::getMenuForIndex(int menuIndex, const String& /*menuName*/)
{
	PopupMenu menu;
	
		if (menuIndex == 0)
		{
			menu.addCommandItem(&commandManager_, CommandIDs::fileNew);
			menu.addCommandItem(&commandManager_, CommandIDs::fileOpen);
			menu.addCommandItem(&commandManager_, CommandIDs::fileSave);
			menu.addCommandItem(&commandManager_, CommandIDs::fileSaveAs);
		}
		//else if (menuIndex == 1)
		//{
		//	menu.addCommandItem(&commandManager, CommandIDs::outerColourRed);
		//	menu.addCommandItem(&commandManager, CommandIDs::outerColourGreen);
		//	menu.addCommandItem(&commandManager, CommandIDs::outerColourBlue);
		//}

	return menu;
}

void MainComponent::menuItemSelected(int /*menuItemID*/, int /*topLevelMenuIndex*/)
{
}

//==============================================================================
ApplicationCommandTarget* MainComponent::getNextCommandTarget()
{
	return NULL;
}

void MainComponent::getAllCommands(Array<CommandID>& c)
{
	Array<CommandID> commands{ CommandIDs::fileNew,
		CommandIDs::fileOpen,
		CommandIDs::fileSave,
		CommandIDs::fileSaveAs };

	c.addArray(commands);
}

void MainComponent::getCommandInfo(CommandID commandID, ApplicationCommandInfo& result)
{
	switch (commandID)
	{
	case CommandIDs::fileNew:
		result.setInfo("New...", "Create a new Akurator project", "Menu", 0);
		result.addDefaultKeypress('n', ModifierKeys::commandModifier);
		break;
	case CommandIDs::fileOpen:
		result.setInfo("Open...", "Open an Akurator project file", "Menu", 0);
		result.addDefaultKeypress('o', ModifierKeys::commandModifier);
		break;
	case CommandIDs::fileSave:
		result.setInfo("Save...", "Save Akurator project to file", "Menu", 0);
		result.addDefaultKeypress('s', ModifierKeys::commandModifier);
		break;
	case CommandIDs::fileSaveAs:
		result.setInfo("Save as...", "Save Akurator project to a different file", "Menu", 0);
		result.addDefaultKeypress('a', ModifierKeys::commandModifier);
		break;
	default:
		break;
	}
}

bool MainComponent::perform(const InvocationInfo& info)
{
	switch (info.commandID)
	{
	case CommandIDs::fileNew:
		break;
	case CommandIDs::fileOpen:
	{
		sspDomainData test;
		std::ifstream is("polymorphism_test.xml");
		boost::archive::xml_iarchive ia(is);
		ia >> BOOST_SERIALIZATION_NVP(test);
	}
		break;
	case CommandIDs::fileSave:
	{
		sspDomainData test;
		std::ofstream os("polymorphism_test.xml");
		boost::archive::xml_oarchive oa(os);			   		 
		oa << BOOST_SERIALIZATION_NVP(test);
	}
		break;
	case CommandIDs::fileSaveAs:
		break;
	default:
		return false;
	}

	return true;
}

void MainComponent::loadProperties()
{
	PropertiesFile* props = app_properties_.getUserSettings();

	sspOscConsole::send_address_s = props->getValue("send_address", "127.0.0.1");
	sspOscConsole::send_port_s = props->getIntValue("send_port", 8001);
	sspOscConsole::receive_port_s = props->getIntValue("receive_port", 9001);

	sspAudioStream::fadein_time_s = props->getDoubleValue("fadein", 2.0);
	sspAudioStream::fadeout_time_s = props->getDoubleValue("fadeout", 5.0);
}

void MainComponent::saveProperties()
{
	PropertiesFile* props = app_properties_.getUserSettings();

	props->setValue("send_address", sspOscConsole::send_address_s);
	props->setValue("send_port", sspOscConsole::send_port_s);
	props->setValue("receive_port", sspOscConsole::receive_port_s);

	props->setValue("fadein", sspAudioStream::fadein_time_s);
	props->setValue("fadeout", sspAudioStream::fadeout_time_s);
}
