/*
  ==============================================================================

    sspToolbarFactory.cpp
    Created: 17 Apr 2019 5:43:58pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "sspToolbarFactory.h"

#include "app/sspCommandIDs.h"
#include "app/sspAkuratorApplication.h"

sspToolbarFilenameComponent::sspToolbarFilenameComponent(const int toolbarItemId)
	: ToolbarItemComponent(toolbarItemId, "Custom Toolbar Item", false)
{
	file_component_.reset(new FilenameComponent("fileComp",
		{},						  // current file
		false,                    // can edit file name,
		false,                    // is directory,
		false,                    // is for saving,
		"*.sspx",				  // browser wildcard suffix,
		{},                       // enforced suffix,
		"Select file to open"));  // text when nothing selected

	addAndMakeVisible(file_component_.get());
}

bool sspToolbarFilenameComponent::getToolbarItemSizes(int /*toolbarDepth*/, bool isVertical, int& preferredSize, int& minSize, int& maxSize)
{
	if (isVertical)
		return false;

	preferredSize = 550;
	minSize = 300;
	maxSize = 800;
	return true;
}

void sspToolbarFilenameComponent::paintButtonArea(Graphics&, int, int, bool, bool)
{
}

void sspToolbarFilenameComponent::contentAreaChanged(const Rectangle<int>& newArea)
{
	file_component_->setSize(newArea.getWidth() - 2, jmin(newArea.getHeight() - 2, 20));
	file_component_->setCentrePosition(newArea.getCentreX(), newArea.getCentreY());
}

void sspToolbarFilenameComponent::addFilenameListener(FilenameComponentListener * listener)
{
	file_component_->addListener(listener);
}

void sspToolbarFilenameComponent::setRecentFiles(const StringArray & filenames)
{
	for (auto elem : filenames) {
		file_component_->addRecentlyUsedFile(elem);
	}
}

void sspToolbarFilenameComponent::setCurrentFile(const File & file)
{
	file_component_->setCurrentFile(file, true, juce::dontSendNotification);
}


sspToolbarFactory::sspToolbarFactory(FilenameComponentListener * listener)
	: filename_listener_(listener)
{
}

void sspToolbarFactory::getAllToolbarItemIds(Array<int>& ids)
{
	// This returns the complete list of all item IDs that are allowed to
	// go in our toolbar. Any items you might want to add must be listed here. The
	// order in which they are listed will be used by the toolbar customisation panel.

	ids.add(sspCommandIDs::DocNew);
	ids.add(sspCommandIDs::DocOpen);
	ids.add(sspCommandIDs::DocSave);
	ids.add(sspCommandIDs::DocSaveAs);
	ids.add(sspCommandIDs::RunVerify);
	ids.add(sspCommandIDs::RunInit);
	ids.add(sspCommandIDs::RunStart);
	ids.add(sspCommandIDs::RunStop);
	ids.add(sspCommandIDs::EditSettings);

	// If you're going to use separators, then they must also be added explicitly
	// to the list.
	ids.add(separatorBarId);
	ids.add(flexibleSpacerId);
}

void sspToolbarFactory::getDefaultItemSet(Array<int>& ids)
{
	// This returns an ordered list of the set of items that make up a
	// toolbar's default set. Not all items need to be on this list, and
	// items can appear multiple times (e.g. the separators used here).
	ids.add(sspCommandIDs::DocNew);
	ids.add(sspCommandIDs::DocSave);
	ids.add(sspCommandIDs::DocSaveAs);
	ids.add(separatorBarId);
	ids.add(flexibleSpacerId);
	ids.add(sspCommandIDs::DocOpen);
	ids.add(flexibleSpacerId);
	ids.add(separatorBarId);
	ids.add(sspCommandIDs::RunVerify);
	ids.add(sspCommandIDs::RunInit);
	ids.add(separatorBarId);
	ids.add(sspCommandIDs::RunStart);
	ids.add(sspCommandIDs::RunStop);
	ids.add(separatorBarId);
	ids.add(sspCommandIDs::EditSettings);
}

ToolbarItemComponent* sspToolbarFactory::createItem(int itemId)
{
	ApplicationCommandManager& cmd_manager = sspAkuratorApplication::getCommandManager();

	switch (itemId)
	{
	case sspCommandIDs::DocNew: {
		ToolbarButton* button = new ToolbarButton(itemId, String("new"),
			Drawable::createFromImageData(BinaryData::documentnew_svg, BinaryData::documentnew_svgSize), 0);
		button->setCommandToTrigger(&cmd_manager, sspCommandIDs::DocNew, true);
		return button;
	}
	case sspCommandIDs::DocOpen: {
		sspToolbarFilenameComponent* box = new sspToolbarFilenameComponent(itemId);
		box->addFilenameListener(filename_listener_);
		box->setCommandToTrigger(&cmd_manager, sspCommandIDs::DocOpen, true);
		return box;
	}
	case sspCommandIDs::DocSave: {
		ToolbarButton* button = new ToolbarButton(itemId, String("save"),
			Drawable::createFromImageData(BinaryData::documentsave_svg, BinaryData::documentsave_svgSize), 0);
		button->setCommandToTrigger(&cmd_manager, sspCommandIDs::DocSave, true);
		return button;
	}
	case sspCommandIDs::DocSaveAs: {
		ToolbarButton* button = new ToolbarButton(itemId, String("save as"),
			Drawable::createFromImageData(BinaryData::documentsaveas_svg, BinaryData::documentsaveas_svgSize), 0);
		button->setCommandToTrigger(&cmd_manager, sspCommandIDs::DocSaveAs, true);
		return button;
	}
	case sspCommandIDs::RunVerify: {
		ToolbarButton* button = new ToolbarButton(itemId, String("verify"),
			Drawable::createFromImageData(BinaryData::runverify_svg, BinaryData::runverify_svgSize), 0);
		button->setCommandToTrigger(&cmd_manager, sspCommandIDs::RunVerify, true);
		return button;
	}
	case sspCommandIDs::RunInit: {
		ToolbarButton* button = new ToolbarButton(itemId, String("init"),
			Drawable::createFromImageData(BinaryData::runinitialize_svg, BinaryData::runinitialize_svgSize), 0);
		button->setCommandToTrigger(&cmd_manager, sspCommandIDs::RunInit, true);
		return button;
	}
	case sspCommandIDs::RunStart: {
		ToolbarButton* button = new ToolbarButton(itemId, String("start"),
			Drawable::createFromImageData(BinaryData::runstart_svg, BinaryData::runstart_svgSize), 0);
		button->setCommandToTrigger(&cmd_manager, sspCommandIDs::RunStart, true);
		return button;
	}
	case sspCommandIDs::RunStop: {
		ToolbarButton* button = new ToolbarButton(itemId, String("stop"),
			Drawable::createFromImageData(BinaryData::runstop_svg, BinaryData::runstop_svgSize), 0);
		button->setCommandToTrigger(&cmd_manager, sspCommandIDs::RunStop, true);
		return button;
	}
	case sspCommandIDs::EditSettings: {
		ToolbarButton* button = new ToolbarButton(itemId, String("edit"),
			Drawable::createFromImageData(BinaryData::editsettings_svg, BinaryData::editsettings_svgSize), 0);
		button->setCommandToTrigger(&cmd_manager, sspCommandIDs::EditSettings, true);
		return button;
	}
	default:
		break;
	}

	return nullptr;
}

