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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"

class sspDomainData;
class sspListboxModel;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class sspDomainPage  : public Component,
                       public Button::Listener
{
public:
    //==============================================================================
    sspDomainPage (sspDomainData* domain);
    ~sspDomainPage();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	sspDomainData* domain_;
	ListBox listbox_;
	std::unique_ptr<sspListboxModel> list_model_;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<GroupComponent> groupComponent;
    std::unique_ptr<ToggleButton> value_btn_;
    std::unique_ptr<ToggleButton> cond_btn_;
    std::unique_ptr<ToggleButton> string_btn_;
    std::unique_ptr<ToggleButton> player_btn_;
    std::unique_ptr<ToggleButton> task_btn_;
    std::unique_ptr<ToggleButton> timeline_btn_;
    std::unique_ptr<ToggleButton> inputs_btn_;
    std::unique_ptr<TextButton> add_btn_;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (sspDomainPage)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

