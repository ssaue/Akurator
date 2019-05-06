/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "sspToolbarFactory.h"
#include "sspTabbedComponent.h"

class sspDomainData;
class sspExecutiveManager;

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public Component, 
				 	  public ApplicationCommandTarget,
					  public FilenameComponentListener
{
public:
    //==============================================================================
    MainComponent(String file_path);
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;


	//==============================================================================
	ApplicationCommandTarget* getNextCommandTarget() override;

	void getAllCommands(Array<CommandID>& c) override;
	void getCommandInfo(CommandID commandID, ApplicationCommandInfo& result) override;
	bool perform(const InvocationInfo& info) override;
	virtual void filenameComponentChanged(FilenameComponent* fileComponentThatHasChanged) override;

	//==============================================================================

private:
    //==============================================================================
	File current_path_;

	Toolbar toolbar_;
	sspToolbarFactory toolbar_factory_;

	void onNew();
	void onLoad();
	void onSave();
	void onSaveAs();

	void onVerify();
	void onInit();
	void onStart();
	void onStop();

	void onStartWithFile();

	sspToolbarFilenameComponent& getFilenameComponent();

	std::unique_ptr<sspDomainData> domain_;
	std::unique_ptr<sspExecutiveManager> manager_;
	std::unique_ptr<sspTabbedComponent> tabs_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
