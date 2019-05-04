/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "sspAkuratorApplication.h"

#include "sspDomainData.h"
#include "sspExecutiveManager.h"
#include "sspExecutionState.h"
#include "sspCommandIDs.h"

#include "Storedal.h"

#include <fstream>
#include <boost/archive/xml_oarchive.hpp> 
#include <boost/archive/xml_iarchive.hpp> 

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>

//==============================================================================
MainComponent::MainComponent(String file_path)
	: toolbar_factory_(this)
	, current_path_()
	, domain_(std::make_unique<sspDomainData>())
	, manager_(std::make_unique<sspExecutiveManager>())
	, tabs_(std::make_unique<sspTabbedComponent>(domain_.get()))
{
	domain_->createInitialContent();

	if (file_path.isNotEmpty() && File::isAbsolutePath(file_path)) {
		File path = file_path;
		if (path.existsAsFile()) {
			current_path_ = file_path;
		}
	}

	ApplicationCommandManager& cmd_manager = sspAkuratorApplication::getCommandManager();
	cmd_manager.registerAllCommandsForTarget(this);
	addKeyListener(cmd_manager.getKeyMappings());

	addAndMakeVisible(*tabs_.get());
	addAndMakeVisible(toolbar_);
	toolbar_.addDefaultItems(toolbar_factory_);

	getFilenameComponent().setCurrentFile(current_path_);
	getFilenameComponent().setRecentFiles(sspAkuratorApplication::getRecentlyOpenedFiles().getAllFilenames());

    setSize (820, 620);
}

MainComponent::~MainComponent()
{
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
	toolbar_.setBounds(b.removeFromTop(40));
	tabs_->setBounds(b.reduced(4));
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
		sspCommandIDs::DocSaveAs, 
		sspCommandIDs::RunVerify,
		sspCommandIDs::RunInit,
		sspCommandIDs::RunStart,
		sspCommandIDs::RunStop,
		sspCommandIDs::EditSettings
	};

	c.addArray(commands);
}

void MainComponent::getCommandInfo(CommandID commandID, ApplicationCommandInfo& result)
{
	switch (commandID)
	{
	case sspCommandIDs::DocNew:
		result.setInfo("New...", "Create a new Akurator project", "File", 0);
		result.addDefaultKeypress('n', ModifierKeys::commandModifier);
		result.setActive(!sspExecutionState::Instance().isRunning());
		break;
	case sspCommandIDs::DocOpen:
		result.setInfo("Open...", "Open Akurator project file", "File", 0);
		result.setActive(!sspExecutionState::Instance().isRunning());
		break;
	case sspCommandIDs::DocSave:
		result.setInfo("Save...", "Save Akurator project to file", "File", 0);
		result.addDefaultKeypress('s', ModifierKeys::commandModifier);
		result.setActive(!sspExecutionState::Instance().isRunning());
		break;
	case sspCommandIDs::DocSaveAs:
		result.setInfo("Save as...", "Save Akurator project to a different file", "File", 0);
		result.addDefaultKeypress('a', ModifierKeys::commandModifier);
		result.setActive(!sspExecutionState::Instance().isRunning());
		break;
	case sspCommandIDs::RunVerify:
		result.setInfo("Verify", "Verify project correctness", "Run", 0);
		result.addDefaultKeypress('v', ModifierKeys::commandModifier);
		result.setActive(!sspExecutionState::Instance().isRunning() && current_path_.existsAsFile());
		break;
	case sspCommandIDs::RunInit:
		result.setInfo("Initialize", "Initialize project", "Run", 0);
		result.addDefaultKeypress('i', ModifierKeys::commandModifier);
		result.setActive(!sspExecutionState::Instance().isRunning() && sspExecutionState::Instance().isVerified());
		break;
	case sspCommandIDs::RunStart:
		result.setInfo("Start", "Start running project", "Run", 0);
		result.addDefaultKeypress(KeyPress::spaceKey, ModifierKeys::noModifiers);
		result.setActive(!sspExecutionState::Instance().isRunning() && sspExecutionState::Instance().isInitialized());
		break;
	case sspCommandIDs::RunStop:
		result.setInfo("Stop", "Stop running project", "Run", 0);
		result.addDefaultKeypress(KeyPress::escapeKey, ModifierKeys::noModifiers);
		result.setActive(sspExecutionState::Instance().isRunning());
		break;
	case sspCommandIDs::EditSettings:
		result.setInfo("Edit", "Edit project settings", "Edit", 0);
		result.addDefaultKeypress('e', ModifierKeys::commandModifier);
		result.setActive(!sspExecutionState::Instance().isRunning());
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
		onNew();
		break;
	case sspCommandIDs::DocSave:
		onSave();
		break;
	case sspCommandIDs::DocSaveAs:
		onSaveAs();
		break;
	case sspCommandIDs::RunVerify: 
		onVerify();
		break;
	case sspCommandIDs::RunInit:
		onInit();
		break;
	case sspCommandIDs::RunStart:
		onStart();
		break;
	case sspCommandIDs::RunStop:
		onStop();
		break;
	case sspCommandIDs::EditSettings:
		// TODO: Open settings panels
		break;
	default:
		return false;
	}

	return true;
}

void MainComponent::filenameComponentChanged(FilenameComponent* fileComponentThatHasChanged)
{
	current_path_ = fileComponentThatHasChanged->getCurrentFile();
	sspAkuratorApplication::getRecentlyOpenedFiles().addFile(current_path_);

	String full_path = current_path_.getFullPathName();
	std::ifstream is(full_path.toStdString());
	boost::archive::xml_iarchive ia(is);
	domain_->clearContents();
	manager_->clearContents();
	ia >> boost::serialization::make_nvp("sspDomainData", *domain_.get()) >> boost::serialization::make_nvp("sspExecutiveManager", *manager_.get());
}

void MainComponent::onNew()
{
	domain_->clearContents();
	manager_->clearContents();
	domain_->createInitialContent();
	Storedal::buildContent(domain_.get(), manager_->getPlayManager());
}

void MainComponent::onSave()
{
	if (current_path_.hasFileExtension(".sspx")) {
		String full_path = current_path_.getFullPathName();
		std::ofstream os(full_path.toStdString());
		boost::archive::xml_oarchive oa(os);
		oa << boost::serialization::make_nvp("sspDomainData", *domain_.get()) << boost::serialization::make_nvp("sspExecutiveManager", *manager_.get());
	}
	else {
		onSaveAs();
	}
}

void MainComponent::onSaveAs()
{
	File previous;
	if (current_path_.existsAsFile()) {
		previous = current_path_.getParentDirectory();
	}
	FileChooser chooser("Save project as ...", previous, "*.sspx");
	if (chooser.browseForFileToSave(true)) {
		current_path_ = chooser.getResult();
		// Update the file browser in the tool bar
		getFilenameComponent().setCurrentFile(current_path_);
		sspAkuratorApplication::getRecentlyOpenedFiles().addFile(current_path_);

		onSave();
	}
}

void MainComponent::onVerify()
{
	auto directory = current_path_.getParentDirectory();
	auto logfile = directory.getChildFile(current_path_.getFileNameWithoutExtension() + ".log");
	
	// Create a log file. If it already exists, then delete if first
	Result result = logfile.deleteFile() ? Result::ok() : Result::fail("Unable to delete previous logfile");
	if (result.wasOk()) {
		result = logfile.create();
	}
	if (result.failed()) {
		AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon,
			"Project verification", "Logfile creation failed: " + result.getErrorMessage());
		return;
	}

	// Using boost log for verification
	using namespace boost::log;
	auto sink = add_file_log(logfile.getFullPathName().toStdString());
	core::get()->set_filter(trivial::severity >= trivial::info);

	int errors = 0, warnings = 0;
	bool ok = domain_->verify(errors, warnings) && manager_->verify(errors, warnings);
	core::get()->remove_sink(sink);

	sspExecutionState::Instance().verified(ok);
	if (ok) {
		AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon,
			"Project verification success",
			"There are " + String(warnings) + " warnings in the project file. Check log file: " + logfile.getFullPathName());
	}
	else {
		AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon,
			"Project verification failed", 
			"There are " + String(errors) + " errors in the project file. Check log file: " + logfile.getFullPathName());
	}
}

void MainComponent::onInit()
{
	bool ok = manager_->initialize(*(domain_.get()));
	sspExecutionState::Instance().initialized(ok);
	if (!ok) {
		String cause;
		switch (manager_->getLastError()) {
		case sspExecutiveManager::Error::Inputs:
			cause = "Inputs failed";
			break;
		case sspExecutiveManager::Error::Reset:
			cause = "Reset manager failed";
			break;
		case sspExecutiveManager::Error::Play:
			cause = "Play manager failed";
			break;
		default:
			break;
		}
		AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon,
			"Project initialization failed", cause);
	}
}

void MainComponent::onStart()
{
	manager_->start();
}

void MainComponent::onStop()
{
	manager_->stop();
}

sspToolbarFilenameComponent & MainComponent::getFilenameComponent()
{
	sspToolbarFilenameComponent* comp = nullptr;
	for (int i = 0; i < toolbar_.getNumItems(); ++i) {
		if (toolbar_.getItemId(i) == sspCommandIDs::DocOpen) {
			comp = dynamic_cast<sspToolbarFilenameComponent*> (toolbar_.getItemComponent(i));
			break;
		}
	}
	jassert(comp != nullptr);
	return *comp;
}
