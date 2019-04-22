/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "sspAkuratorApplication.h"

#include "sspDomainData.h"
#include "sspStreamBus.h"
#include "sspOscConsole.h"
#include "sspExecutiveManager.h"
#include "sspResetManager.h"
#include "sspCommandIDs.h"

#include <fstream>
#include <boost/archive/xml_oarchive.hpp> 
#include <boost/archive/xml_iarchive.hpp> 

//==============================================================================
MainComponent::MainComponent(String file_path)
	: domain_(std::make_unique<sspDomainData>())
	, manager_(std::make_unique<sspExecutiveManager>())
{
	domain_->createInitialContent();
	manager_->initialize(*domain_.get());

	//File current_path;
	//if (file_path.isNotEmpty() && File::isAbsolutePath(file_path)) {
	//	File path = file_path;
	//	if (path.existsAsFile()) {
	//		current_path = file_path;
	//	}
	//}

	//file_component_.reset(new FilenameComponent("fileComp",
	//	current_path,             // current file
	//	false,                    // can edit file name,
	//	false,                    // is directory,
	//	false,                    // is for saving,
	//	"*.sspx",				  // browser wildcard suffix,
	//	{},                       // enforced suffix,
	//	"Select file to open"));  // text when nothing selected

	//addAndMakeVisible(file_component_.get());
	//file_component_->addListener(this);

	ApplicationCommandManager& cmd_manager = sspAkuratorApplication::getCommandManager();
	cmd_manager.registerAllCommandsForTarget(this);
	addKeyListener(cmd_manager.getKeyMappings());

	addAndMakeVisible(toolbar_);
	toolbar_.addDefaultItems(toolbar_factory_);

    setSize (800, 600);

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

    //g.setFont (Font (16.0f));
    //g.setColour (Colours::white);
    //g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainComponent::resized()
{
	auto b = getLocalBounds();
//	menuBar_->setBounds(b.removeFromTop(LookAndFeel::getDefaultLookAndFeel().getDefaultMenuBarHeight()));
//	file_component_->setBounds(b.removeFromTop(20));
	toolbar_.setBounds(b.removeFromTop(40));
}

//==============================================================================
ApplicationCommandTarget* MainComponent::getNextCommandTarget()
{
	return NULL;
}

void MainComponent::getAllCommands(Array<CommandID>& c)
{
	Array<CommandID> commands{ 
		sspCommandIDs::DocNew,
		sspCommandIDs::DocOpen,
		sspCommandIDs::DocSave,
		sspCommandIDs::DocSaveAs };

	c.addArray(commands);
}

void MainComponent::getCommandInfo(CommandID commandID, ApplicationCommandInfo& result)
{
	switch (commandID)
	{
	case sspCommandIDs::DocNew:
		result.setInfo("New...", "Create a new Akurator project", "Menu", 0);
		result.addDefaultKeypress('n', ModifierKeys::commandModifier);
		break;
	case sspCommandIDs::DocOpen:
		result.setInfo("Open...", "Open an Akurator project file", "Menu", 0);
		result.addDefaultKeypress('o', ModifierKeys::commandModifier);
		break;
	case sspCommandIDs::DocSave:
		result.setInfo("Save...", "Save Akurator project to file", "Menu", 0);
		result.addDefaultKeypress('s', ModifierKeys::commandModifier);
		break;
	case sspCommandIDs::DocSaveAs:
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
	case sspCommandIDs::DocNew:
		domain_->clearContents();
		domain_->createInitialContent();
		manager_->clearContents();
		manager_->initialize(*domain_.get());
		break;
	case sspCommandIDs::DocOpen:
	{
		std::ifstream is("polymorphism_test.xml");
		boost::archive::xml_iarchive ia(is);
		domain_->clearContents();
		manager_->clearContents();
		ia >> boost::serialization::make_nvp("sspDomainData", *domain_.get()) >> boost::serialization::make_nvp("sspExecutiveManager", *manager_.get());
	}
		break;
	case sspCommandIDs::DocSave:
	{
		std::ofstream os("polymorphism_test.xml");
		boost::archive::xml_oarchive oa(os);			   		 
		oa << boost::serialization::make_nvp("sspDomainData", *domain_.get()) << boost::serialization::make_nvp("sspExecutiveManager", *manager_.get());
	}
		break;
	case sspCommandIDs::DocSaveAs:
		break;
	default:
		return false;
	}

	return true;
}

void MainComponent::filenameComponentChanged(FilenameComponent* fileComponentThatHasChanged)
{
	//if (fileComponentThatHasChanged == file_component_.get()) {
	//	// Do something
	//}
}


void MainComponent::loadProperties()
{
	PropertiesFile* props = app_properties_.getUserSettings();

	sspOscConsole::send_address_s = props->getValue("send_address", "127.0.0.1");
	sspOscConsole::send_port_s = props->getIntValue("send_port", 8001);
	sspOscConsole::receive_port_s = props->getIntValue("receive_port", 9001);

	sspStreamBus::fadein_time_s = props->getDoubleValue("fadein_time", 2.0);
	sspStreamBus::fadeout_time_s = props->getDoubleValue("fadeout_time", 5.0);
	sspStreamBus::volume_time_s = props->getDoubleValue("volume_time", 1.0);

	sspExecutiveManager::startup_proc_s = sspExecutiveManager::Startup{ props->getIntValue("startup_proc", 0) };
	sspExecutiveManager::shutdown_proc_s = sspExecutiveManager::Shutdown{ props->getIntValue("shutdown_proc", 0) };
	sspExecutiveManager::use_play_interval_s = props->getBoolValue("use_interval", true);
	sspExecutiveManager::update_interval_s = props->getDoubleValue("update_interval", 1.0);

	int hour = props->getIntValue("start_hour", 8);
	int minute = props->getIntValue("start_minute", 0);
	sspExecutiveManager::start_time_s = boost::posix_time::time_duration{hour, minute, 0};

	hour = props->getIntValue("end_hour", 20);
	minute = props->getIntValue("end_minute", 0);
	sspExecutiveManager::end_time_s = boost::posix_time::time_duration{ hour, minute, 0 };

	hour = props->getIntValue("reset_hour", 20);
	minute = props->getIntValue("reset_minute", 0);
	sspResetManager::reset_time_s = boost::posix_time::time_duration{ hour, minute, 0 };

	int days = props->getIntValue("reset_interval", 1);
	sspResetManager::reset_interval_s = boost::gregorian::date_duration{ days };

	sspResetManager::watchdog_enable_s = props->getBoolValue("watchdog_enable", false);
	sspResetManager::watchdog_type_s = sspWatchdog::Type{ props->getIntValue("watchdog_type", 0) };
	sspResetManager::watchdog_timeout_s = props->getDoubleValue("watchdog_timeout", 5);
}

void MainComponent::saveProperties()
{
	PropertiesFile* props = app_properties_.getUserSettings();

	props->setValue("send_address", sspOscConsole::send_address_s);
	props->setValue("send_port", sspOscConsole::send_port_s);
	props->setValue("receive_port", sspOscConsole::receive_port_s);

	props->setValue("fadein_time", sspStreamBus::fadein_time_s);
	props->setValue("fadeout_time", sspStreamBus::fadeout_time_s);
	props->setValue("volume_time", sspStreamBus::volume_time_s);

	props->setValue("startup_proc", static_cast<int>(sspExecutiveManager::startup_proc_s));
	props->setValue("shutdown_proc", static_cast<int>(sspExecutiveManager::shutdown_proc_s));
	props->setValue("use_interval", sspExecutiveManager::use_play_interval_s);
	props->setValue("update_interval", sspExecutiveManager::update_interval_s);

	props->setValue("start_hour", sspExecutiveManager::start_time_s.hours());
	props->setValue("start_minute", sspExecutiveManager::start_time_s.minutes());
	props->setValue("end_hour", sspExecutiveManager::end_time_s.hours());
	props->setValue("end_minute", sspExecutiveManager::end_time_s.minutes());

	props->setValue("reset_hour", sspResetManager::reset_time_s.hours());
	props->setValue("reset_minute", sspResetManager::reset_time_s.minutes());
	props->setValue("reset_interval", sspResetManager::reset_interval_s.days());

	props->setValue("watchdog_enable", sspResetManager::watchdog_enable_s);
	props->setValue("watchdog_type", static_cast<int>(sspResetManager::watchdog_type_s));
	props->setValue("watchdog_timeout", sspResetManager::watchdog_timeout_s);
}
