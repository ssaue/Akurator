/*
  ==============================================================================

	This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "app/sspAkuratorApplication.h"

#include "domain/sspDomainData.h"
#include "engine/sspExecutiveManager.h"
#include "engine/sspExecutionState.h"
#include "app/sspCommandIDs.h"

// TODO: Find a more elegant way to solve building different projects
//#define BUILD_STOREDAL 1
//#define BUILD_BEKKELAGET 1
#define BUILD_HMM 1

#ifdef BUILD_STOREDAL
#include "projects/Storedal.h"
#elif BUILD_BEKKELAGET
#include "projects/Bekkelaget.h"
#elif BUILD_HMM
#include "projects/HMM.h"
#else
#include "projects/BlankProject.h"
#endif

#include "access/sspLogging.h"


MainComponent::MainComponent(String file_path)
	: toolbar_factory_(this)
	, current_path_()
	, domain_(std::make_unique<sspDomainData>())
	, manager_(std::make_unique<sspExecutiveManager>())
	, tabs_(std::make_unique<sspTabbedComponent>(domain_.get()))
{
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

	setSize(820, 620);

	if (current_path_.existsAsFile()) {
		MessageManager::callAsync([this] { onStartWithFile(); });
	}
}

MainComponent::~MainComponent()
{
	domain_->saveValuePropertiesFromInputs();
}

//==============================================================================
void MainComponent::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
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
	auto path = fileComponentThatHasChanged->getCurrentFile();
	if (path.existsAsFile()) {
		current_path_ = path;
		onLoad();
	}
}

void MainComponent::onNew()
{
	/*
	** There is currently no GUI for editing project data.
	** Therefore we build content using source files.
	** BlankProject is the minimum content expected.
	*/

#ifdef BUILD_STOREDAL
	Storedal::buildContent(domain_.get());
#elif BUILD_BEKKELAGET
	Bekkelaget::buildContent(domain_.get());
#elif BUILD_HMM
	HMM::buildContent(domain_.get());
#else
	BlankProject::buildContent(domain_.get());
#endif

	domain_->loadValuePropertiesToInputs();
}

void MainComponent::onLoad()
{
	sspAkuratorApplication::getRecentlyOpenedFiles().addFile(current_path_);
	String full_path = current_path_.getFullPathName();
	sspDomainData::loadAll(full_path.toStdString(), domain_.get());
}

void MainComponent::onSave()
{
	if (current_path_.hasFileExtension(".sspx")) {
		String full_path = current_path_.getFullPathName();
		sspDomainData::saveAll(full_path.toStdString(), domain_.get());
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

	// Using spdlog for verification
	std::vector<logging::Config> configs;
	configs.emplace_back(logging::Config{ logging::Type::file,
		logfile.getFullPathName().toStdString(),
		logging::Format::verify,
		spdlog::level::info });

	logging::createLogger(configs, true, logging::FlushPolicy::automatic);

	int errors = 0, warnings = 0;
	bool ok = domain_->verify(errors, warnings) && manager_->verify(errors, warnings);

	logging::flush();
	logging::close();

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

void MainComponent::onStartWithFile()
{
	if (current_path_.existsAsFile()) {
		onLoad();
		if (manager_->startup_proc_s != sspExecutiveManager::Startup::DoNothing) {
			onInit();
			if (manager_->startup_proc_s == sspExecutiveManager::Startup::Play && sspExecutionState::Instance().isInitialized()) {
				onStart();
			}
		}
	}
}

sspToolbarFilenameComponent& MainComponent::getFilenameComponent()
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
