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
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class sspSettingsPage  : public Component,
                         public ComboBox::Listener
{
public:
    //==============================================================================
    sspSettingsPage ();
    ~sspSettingsPage();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	ApplicationProperties app_properties_;

	void loadProperties();
	void saveProperties();

	void onEditStartTime();
	void onEditEndTime();
	void onEditResetTime();

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> label_osc_;
    std::unique_ptr<TextEditor> osc_send_addr_;
    std::unique_ptr<Label> label_osc_sendport_2;
    std::unique_ptr<Label> label_osc_sendport_;
    std::unique_ptr<Label> label_osc_sendaddr_;
    std::unique_ptr<TextEditor> osc_send_port_;
    std::unique_ptr<TextEditor> osc_receive_port_;
    std::unique_ptr<Label> label_osc_2;
    std::unique_ptr<Label> label_osc_sendaddr_2;
    std::unique_ptr<Label> label_osc_sendaddr_3;
    std::unique_ptr<Label> label_osc_sendaddr_4;
    std::unique_ptr<Label> label_osc_sendaddr_5;
    std::unique_ptr<ComboBox> exec_startup_cb_;
    std::unique_ptr<ComboBox> exec_shutdown_cb_;
    std::unique_ptr<TextEditor> exec_start_hour_;
    std::unique_ptr<TextEditor> exec_start_min_;
    std::unique_ptr<Label> label_osc_sendaddr_6;
    std::unique_ptr<TextEditor> exec_update_inteval_;
    std::unique_ptr<Label> label_osc_sendaddr_7;
    std::unique_ptr<TextEditor> exec_end_hour_;
    std::unique_ptr<TextEditor> exec_end_min_;
    std::unique_ptr<Label> label_osc_sendaddr_8;
    std::unique_ptr<ToggleButton> exec_use_interval_;
    std::unique_ptr<Label> label_osc_3;
    std::unique_ptr<Label> label_osc_sendaddr_13;
    std::unique_ptr<TextEditor> exec_start_hour_2;
    std::unique_ptr<TextEditor> exec_start_min_2;
    std::unique_ptr<Label> label_osc_sendaddr_14;
    std::unique_ptr<Label> label_osc_sendaddr_9;
    std::unique_ptr<TextEditor> reset_hour_;
    std::unique_ptr<TextEditor> reset_min_;
    std::unique_ptr<Label> label_osc_sendaddr_11;
    std::unique_ptr<Label> label_osc_sendaddr_10;
    std::unique_ptr<Label> label;
    std::unique_ptr<Label> label2;
    std::unique_ptr<TextEditor> reset_interval_;
    std::unique_ptr<Label> label_osc_4;
    std::unique_ptr<Label> label_osc_sendaddr_12;
    std::unique_ptr<TextEditor> watchdog_timeout_;
    std::unique_ptr<Label> label3;
    std::unique_ptr<Label> label_osc_sendaddr_15;
    std::unique_ptr<ComboBox> watchdog_proc_cb_;
    std::unique_ptr<Label> label_osc_sendaddr_16;
    std::unique_ptr<TextButton> watchdog_soft_btn_;
    std::unique_ptr<TextButton> watchdog_hard_btn_;
    std::unique_ptr<Label> label_osc_5;
    std::unique_ptr<Label> label_osc_sendaddr_17;
    std::unique_ptr<TextEditor> mix_fadein_;
    std::unique_ptr<Label> label4;
    std::unique_ptr<Label> label_osc_sendaddr_18;
    std::unique_ptr<TextEditor> mix_fadeout_;
    std::unique_ptr<Label> label5;
    std::unique_ptr<Label> label_osc_sendaddr_19;
    std::unique_ptr<TextEditor> mix_volume_change_;
    std::unique_ptr<Label> label6;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (sspSettingsPage)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

