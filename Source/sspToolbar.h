/*
  ==============================================================================

    sspToolbar.h
    Created: 17 Apr 2019 5:43:58pm
    Author:  Sigurd Saue

	Eight icons created by GNOME icon artists - https://github.com/GNOME/gnome-icon-theme 
	CC BY-SA 3.0: 
		https://commons.wikimedia.org/w/index.php?curid=3375538
		https://commons.wikimedia.org/w/index.php?curid=3375537
		https://commons.wikimedia.org/w/index.php?curid=3375524
		https://commons.wikimedia.org/w/index.php?curid=4339717
		https://commons.wikimedia.org/w/index.php?curid=4015399
		https://commons.wikimedia.org/w/index.php?curid=4015400
		https://commons.wikimedia.org/w/index.php?curid=4339715
		https://commons.wikimedia.org/w/index.php?curid=3375570
  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


class sspToolbarFactory : public ToolbarItemFactory
{
public:
	sspToolbarFactory() = default;

	void getAllToolbarItemIds(Array<int>& ids) override;
	void getDefaultItemSet(Array<int>& ids) override;

	ToolbarItemComponent* createItem(int itemId);

private:

	class CustomFilenameComponent : public ToolbarItemComponent
	{
	public:
		CustomFilenameComponent(const int toolbarItemId)
			: ToolbarItemComponent(toolbarItemId, "Custom Toolbar Item", false)
		{
			file_component_.reset(new FilenameComponent("fileComp",
				{},			              // current file
				false,                    // can edit file name,
				false,                    // is directory,
				false,                    // is for saving,
				"*.sspx",				  // browser wildcard suffix,
				{},                       // enforced suffix,
				"Select file to open"));  // text when nothing selected

			addAndMakeVisible(file_component_.get());
		}

		bool getToolbarItemSizes(int /*toolbarDepth*/, bool isVertical,
			int& preferredSize, int& minSize, int& maxSize) override
		{
			if (isVertical)
				return false;

			preferredSize = 400;
			minSize = 200;
			maxSize = 600;
			return true;
		}

		void paintButtonArea(Graphics&, int, int, bool, bool) override
		{
		}

		void contentAreaChanged(const Rectangle<int>& newArea) override
		{
			file_component_->setSize(newArea.getWidth() - 2, jmin(newArea.getHeight() - 2, 20));
			file_component_->setCentrePosition(newArea.getCentreX(), newArea.getCentreY());
		}

	private:

		std::unique_ptr<FilenameComponent> file_component_;
	};
};

