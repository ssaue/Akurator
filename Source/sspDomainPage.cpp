/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.3

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "sspDomainData.h"
#include "sspDomainListboxModel.h"
//[/Headers]

#include "sspDomainPage.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
sspDomainPage::sspDomainPage (sspDomainData* domain)
{
    //[Constructor_pre] You can add your own custom stuff here..
	domain_ = domain;
    //[/Constructor_pre]

    groupComponent.reset (new GroupComponent ("new group",
                                              TRANS("Domain element")));
    addAndMakeVisible (groupComponent.get());

    groupComponent->setBounds (20, 13, 168, 248);

    value_btn_.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (value_btn_.get());
    value_btn_->setButtonText (TRANS("Values"));
    value_btn_->setRadioGroupId (1);
    value_btn_->addListener (this);

    value_btn_->setBounds (38, 41, 150, 24);

    cond_btn_.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (cond_btn_.get());
    cond_btn_->setButtonText (TRANS("Conditionals"));
    cond_btn_->setRadioGroupId (1);
    cond_btn_->addListener (this);

    cond_btn_->setBounds (38, 71, 150, 24);

    string_btn_.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (string_btn_.get());
    string_btn_->setButtonText (TRANS("Strings"));
    string_btn_->setRadioGroupId (1);
    string_btn_->addListener (this);

    string_btn_->setBounds (38, 101, 150, 24);

    player_btn_.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (player_btn_.get());
    player_btn_->setButtonText (TRANS("Players"));
    player_btn_->setRadioGroupId (1);
    player_btn_->addListener (this);

    player_btn_->setBounds (38, 131, 150, 24);

    task_btn_.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (task_btn_.get());
    task_btn_->setButtonText (TRANS("Tasks"));
    task_btn_->setRadioGroupId (1);
    task_btn_->addListener (this);

    task_btn_->setBounds (38, 161, 150, 24);

    timeline_btn_.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (timeline_btn_.get());
    timeline_btn_->setButtonText (TRANS("Timelines"));
    timeline_btn_->setRadioGroupId (1);
    timeline_btn_->addListener (this);

    timeline_btn_->setBounds (38, 191, 150, 24);

    inputs_btn_.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (inputs_btn_.get());
    inputs_btn_->setButtonText (TRANS("Inputs"));
    inputs_btn_->setRadioGroupId (1);
    inputs_btn_->addListener (this);

    inputs_btn_->setBounds (38, 221, 150, 24);

    add_btn_.reset (new TextButton ("new button"));
    addAndMakeVisible (add_btn_.get());
    add_btn_->setButtonText (TRANS("Add"));
    add_btn_->addListener (this);
    add_btn_->setColour (TextButton::buttonColourId, Colours::cornflowerblue);

    add_btn_->setBounds (345, 272, 55, 24);


    //[UserPreSize]

	value_btn_->setToggleState(true, NotificationType::dontSendNotification);
	list_model_.reset(new sspDomainListboxModel<sspValue>(&domain->getValues()));
	listbox_.setModel(list_model_.get());
	listbox_.setMultipleSelectionEnabled(false);
	addAndMakeVisible(listbox_);

    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

sspDomainPage::~sspDomainPage()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    groupComponent = nullptr;
    value_btn_ = nullptr;
    cond_btn_ = nullptr;
    string_btn_ = nullptr;
    player_btn_ = nullptr;
    task_btn_ = nullptr;
    timeline_btn_ = nullptr;
    inputs_btn_ = nullptr;
    add_btn_ = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void sspDomainPage::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void sspDomainPage::resized()
{
    //[UserPreResize] Add your own custom resize code here..
	listbox_.setBounds(200, 13, 350, 248);
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void sspDomainPage::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == value_btn_.get())
    {
        //[UserButtonCode_value_btn_] -- add your button handler code here..
		list_model_.reset(new sspDomainListboxModel<sspValue>(&domain_->getValues()));
		listbox_.setModel(list_model_.get());
		listbox_.updateContent();
        //[/UserButtonCode_value_btn_]
    }
    else if (buttonThatWasClicked == cond_btn_.get())
    {
        //[UserButtonCode_cond_btn_] -- add your button handler code here..
		list_model_.reset(new sspDomainListboxModel<sspConditional>(&domain_->getConditionals()));
		listbox_.setModel(list_model_.get());
		listbox_.updateContent();
        //[/UserButtonCode_cond_btn_]
    }
    else if (buttonThatWasClicked == string_btn_.get())
    {
        //[UserButtonCode_string_btn_] -- add your button handler code here..
		list_model_.reset(new sspDomainListboxModel<sspString>(&domain_->getStrings()));
		listbox_.setModel(list_model_.get());
		listbox_.updateContent();
        //[/UserButtonCode_string_btn_]
    }
    else if (buttonThatWasClicked == player_btn_.get())
    {
        //[UserButtonCode_player_btn_] -- add your button handler code here..
		list_model_.reset(new sspDomainListboxModel<sspPlayer>(&domain_->getPlayers()));
		listbox_.setModel(list_model_.get());
		listbox_.updateContent();
        //[/UserButtonCode_player_btn_]
    }
    else if (buttonThatWasClicked == task_btn_.get())
    {
        //[UserButtonCode_task_btn_] -- add your button handler code here..
		list_model_.reset(new sspDomainListboxModel<sspPlayTask>(&domain_->getPlaytasks()));
		listbox_.setModel(list_model_.get());
		listbox_.updateContent();
        //[/UserButtonCode_task_btn_]
    }
    else if (buttonThatWasClicked == timeline_btn_.get())
    {
        //[UserButtonCode_timeline_btn_] -- add your button handler code here..
		list_model_.reset(new sspDomainListboxModel<sspTimeline>(&domain_->getTimelines()));
		listbox_.setModel(list_model_.get());
		listbox_.updateContent();
        //[/UserButtonCode_timeline_btn_]
    }
    else if (buttonThatWasClicked == inputs_btn_.get())
    {
        //[UserButtonCode_inputs_btn_] -- add your button handler code here..
		list_model_.reset(new sspDomainListboxModel<sspInput>(&domain_->getInputs()));
		listbox_.setModel(list_model_.get());
		listbox_.updateContent();
        //[/UserButtonCode_inputs_btn_]
    }
    else if (buttonThatWasClicked == add_btn_.get())
    {
        //[UserButtonCode_add_btn_] -- add your button handler code here..
//		list_model_->onAdd();
		listbox_.selectRow(0);
        //[/UserButtonCode_add_btn_]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="sspDomainPage" componentName=""
                 parentClasses="public Component" constructorParams="sspDomainData* domain"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
  <GROUPCOMPONENT name="new group" id="df4562115679268f" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="20 13 168 248" title="Domain element"/>
  <TOGGLEBUTTON name="new toggle button" id="42e20d2aa68ecb3f" memberName="value_btn_"
                virtualName="" explicitFocusOrder="0" pos="38 41 150 24" buttonText="Values"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="75eac5c48f25ca55" memberName="cond_btn_"
                virtualName="" explicitFocusOrder="0" pos="38 71 150 24" buttonText="Conditionals"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="e2918ae580faf4bd" memberName="string_btn_"
                virtualName="" explicitFocusOrder="0" pos="38 101 150 24" buttonText="Strings"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="ca946f27840e7362" memberName="player_btn_"
                virtualName="" explicitFocusOrder="0" pos="38 131 150 24" buttonText="Players"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="74612db29e89f002" memberName="task_btn_"
                virtualName="" explicitFocusOrder="0" pos="38 161 150 24" buttonText="Tasks"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="dc165af28e072d36" memberName="timeline_btn_"
                virtualName="" explicitFocusOrder="0" pos="38 191 150 24" buttonText="Timelines"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="6b84667f35c5e93b" memberName="inputs_btn_"
                virtualName="" explicitFocusOrder="0" pos="38 221 150 24" buttonText="Inputs"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <TEXTBUTTON name="new button" id="435e33c41f0fa72c" memberName="add_btn_"
              virtualName="" explicitFocusOrder="0" pos="345 272 55 24" bgColOff="ff6495ed"
              buttonText="Add" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

