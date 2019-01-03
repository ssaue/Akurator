/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public Component, 
				 	  public ApplicationCommandTarget,
					  public MenuBarModel
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	//==============================================================================
	StringArray getMenuBarNames() override;
	PopupMenu getMenuForIndex(int topLevelMenuIndex, const String& menuName) override;
	void menuItemSelected(int menuItemID, int topLevelMenuIndex) override;

	//==============================================================================
	ApplicationCommandTarget* getNextCommandTarget() override;

	void getAllCommands(Array<CommandID>& c) override;

	void getCommandInfo(CommandID commandID, ApplicationCommandInfo& result) override;

	bool perform(const InvocationInfo& info) override;

	//==============================================================================
	enum CommandIDs
	{
		fileNew = 1000,
		fileOpen,
		fileSave,
		fileSaveAs
	};

private:
    //==============================================================================
	ApplicationCommandManager commandManager_;
	std::unique_ptr<MenuBarComponent> menuBar_;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
