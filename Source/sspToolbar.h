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
	sspToolbarFactory(FilenameComponentListener* listener);

	void getAllToolbarItemIds(Array<int>& ids) override;
	void getDefaultItemSet(Array<int>& ids) override;
	void setFilepath(const File& path);

	ToolbarItemComponent* createItem(int itemId);

private:
	FilenameComponentListener* filename_listener_;
	File filepath_;

	class CustomFilenameComponent : public ToolbarItemComponent
	{
	public:
		CustomFilenameComponent(const int toolbarItemId, const File& init_file_path);

		bool getToolbarItemSizes(int /*toolbarDepth*/, bool isVertical,
			int& preferredSize, int& minSize, int& maxSize) override;
		void paintButtonArea(Graphics&, int, int, bool, bool) override;
		void contentAreaChanged(const Rectangle<int>& newArea) override;
		void addFilenameListener(FilenameComponentListener* listener);

	private:
		std::unique_ptr<FilenameComponent> file_component_;
	};
};

