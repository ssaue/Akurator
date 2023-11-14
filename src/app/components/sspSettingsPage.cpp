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
#include "engine/sspStreamBus.h"
#include "access/osc/sspOscConsole.h"
#include "engine/sspExecutiveManager.h"
#include "engine/sspResetManager.h"
#include "app/sspAkuratorApplication.h"
//[/Headers]

#include "sspSettingsPage.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
sspSettingsPage::sspSettingsPage ()
{
    label_osc_.reset (new Label ("OSC heading",
                                 TRANS("OSC\n")));
    addAndMakeVisible (label_osc_.get());
    label_osc_->setFont (Font (25.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_->setJustificationType (Justification::centredLeft);
    label_osc_->setEditable (false, false, false);
    label_osc_->setColour (TextEditor::textColourId, Colours::black);
    label_osc_->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_->setBounds (465, 30, 56, 24);

    osc_send_addr_.reset (new TextEditor ("send_addr_editor"));
    addAndMakeVisible (osc_send_addr_.get());
    osc_send_addr_->setMultiLine (false);
    osc_send_addr_->setReturnKeyStartsNewLine (false);
    osc_send_addr_->setReadOnly (false);
    osc_send_addr_->setScrollbarsShown (false);
    osc_send_addr_->setCaretVisible (true);
    osc_send_addr_->setPopupMenuEnabled (false);
    osc_send_addr_->setText (String());

    osc_send_addr_->setBounds (576, 60, 110, 24);

    label_osc_sendport_2.reset (new Label ("Osc receive port",
                                           TRANS("Receive port:")));
    addAndMakeVisible (label_osc_sendport_2.get());
    label_osc_sendport_2->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_sendport_2->setJustificationType (Justification::centredLeft);
    label_osc_sendport_2->setEditable (false, false, false);
    label_osc_sendport_2->setColour (TextEditor::textColourId, Colours::black);
    label_osc_sendport_2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_sendport_2->setBounds (465, 120, 96, 24);

    label_osc_sendport_.reset (new Label ("Osc send port",
                                          TRANS("Send port:")));
    addAndMakeVisible (label_osc_sendport_.get());
    label_osc_sendport_->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_sendport_->setJustificationType (Justification::centredLeft);
    label_osc_sendport_->setEditable (false, false, false);
    label_osc_sendport_->setColour (TextEditor::textColourId, Colours::black);
    label_osc_sendport_->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_sendport_->setBounds (465, 90, 80, 24);

    label_osc_sendaddr_.reset (new Label ("osc_send_adress",
                                          TRANS("Send address:")));
    addAndMakeVisible (label_osc_sendaddr_.get());
    label_osc_sendaddr_->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_sendaddr_->setJustificationType (Justification::centredLeft);
    label_osc_sendaddr_->setEditable (false, false, false);
    label_osc_sendaddr_->setColour (TextEditor::textColourId, Colours::black);
    label_osc_sendaddr_->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_sendaddr_->setBounds (465, 60, 96, 24);

    osc_send_port_.reset (new TextEditor ("send_port_editor"));
    addAndMakeVisible (osc_send_port_.get());
    osc_send_port_->setMultiLine (false);
    osc_send_port_->setReturnKeyStartsNewLine (false);
    osc_send_port_->setReadOnly (false);
    osc_send_port_->setScrollbarsShown (false);
    osc_send_port_->setCaretVisible (true);
    osc_send_port_->setPopupMenuEnabled (false);
    osc_send_port_->setText (String());

    osc_send_port_->setBounds (576, 90, 50, 24);

    osc_receive_port_.reset (new TextEditor ("receive_port_editor"));
    addAndMakeVisible (osc_receive_port_.get());
    osc_receive_port_->setMultiLine (false);
    osc_receive_port_->setReturnKeyStartsNewLine (false);
    osc_receive_port_->setReadOnly (false);
    osc_receive_port_->setScrollbarsShown (false);
    osc_receive_port_->setCaretVisible (true);
    osc_receive_port_->setPopupMenuEnabled (false);
    osc_receive_port_->setText (String());

    osc_receive_port_->setBounds (576, 120, 50, 24);

    /*****************************************************************************/

    label_osc_2.reset (new Label ("exec_heading",
                                  TRANS("Exec\n")));
    addAndMakeVisible (label_osc_2.get());
    label_osc_2->setFont (Font (25.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_2->setJustificationType (Justification::centredLeft);
    label_osc_2->setEditable (false, false, false);
    label_osc_2->setColour (TextEditor::textColourId, Colours::black);
    label_osc_2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_2->setBounds (32, 30, 80, 24);

    label_osc_sendaddr_2.reset (new Label ("exec_startup",
                                           TRANS("Startup proceedure:")));
    addAndMakeVisible (label_osc_sendaddr_2.get());
    label_osc_sendaddr_2->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_sendaddr_2->setJustificationType (Justification::centredLeft);
    label_osc_sendaddr_2->setEditable (false, false, false);
    label_osc_sendaddr_2->setColour (TextEditor::textColourId, Colours::black);
    label_osc_sendaddr_2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_sendaddr_2->setBounds (32, 60, 152, 24);

    label_osc_sendaddr_3.reset (new Label ("exec_shutdown",
                                           TRANS("Shutdown proceedure:")));
    addAndMakeVisible (label_osc_sendaddr_3.get());
    label_osc_sendaddr_3->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_sendaddr_3->setJustificationType (Justification::centredLeft);
    label_osc_sendaddr_3->setEditable (false, false, false);
    label_osc_sendaddr_3->setColour (TextEditor::textColourId, Colours::black);
    label_osc_sendaddr_3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_sendaddr_3->setBounds (32, 90, 152, 24);

    label_osc_sendaddr_4.reset (new Label ("exec_play_interval",
                                           TRANS("Play interval:")));
    addAndMakeVisible (label_osc_sendaddr_4.get());
    label_osc_sendaddr_4->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_sendaddr_4->setJustificationType (Justification::centredLeft);
    label_osc_sendaddr_4->setEditable (false, false, false);
    label_osc_sendaddr_4->setColour (TextEditor::textColourId, Colours::black);
    label_osc_sendaddr_4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_sendaddr_4->setBounds (32, 120, 152, 24);

    label_osc_sendaddr_5.reset (new Label ("exec_update_interval",
                                           TRANS("Update interval:")));
    addAndMakeVisible (label_osc_sendaddr_5.get());
    label_osc_sendaddr_5->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_sendaddr_5->setJustificationType (Justification::centredLeft);
    label_osc_sendaddr_5->setEditable (false, false, false);
    label_osc_sendaddr_5->setColour (TextEditor::textColourId, Colours::black);
    label_osc_sendaddr_5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_sendaddr_5->setBounds (32, 150, 152, 24);

    exec_startup_cb_.reset (new ComboBox ("exec_startup_proc"));
    addAndMakeVisible (exec_startup_cb_.get());
    exec_startup_cb_->setEditableText (false);
    exec_startup_cb_->setJustificationType (Justification::centredLeft);
    exec_startup_cb_->setTextWhenNothingSelected (TRANS("Select proceedure"));
    exec_startup_cb_->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    exec_startup_cb_->addItem (TRANS("Do nothing"), 1);
    exec_startup_cb_->addItem (TRANS("Initialize"), 2);
    exec_startup_cb_->addItem (TRANS("Play"), 3);
    exec_startup_cb_->addListener (this);

    exec_startup_cb_->setBounds (195, 60, 150, 24);

    exec_shutdown_cb_.reset (new ComboBox ("exec_shutdown_proc"));
    addAndMakeVisible (exec_shutdown_cb_.get());
    exec_shutdown_cb_->setEditableText (false);
    exec_shutdown_cb_->setJustificationType (Justification::centredLeft);
    exec_shutdown_cb_->setTextWhenNothingSelected (TRANS("Select proceedure"));
    exec_shutdown_cb_->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    exec_shutdown_cb_->addItem (TRANS("Keep running"), 1);
    exec_shutdown_cb_->addItem (TRANS("Stop"), 2);
    exec_shutdown_cb_->addItem (TRANS("Exit"), 3);
    exec_shutdown_cb_->addListener (this);

    exec_shutdown_cb_->setBounds (195, 90, 150, 24);

    exec_start_hour_.reset (new TextEditor ("exec_starttime_hour"));
    addAndMakeVisible (exec_start_hour_.get());
    exec_start_hour_->setMultiLine (false);
    exec_start_hour_->setReturnKeyStartsNewLine (false);
    exec_start_hour_->setReadOnly (false);
    exec_start_hour_->setScrollbarsShown (false);
    exec_start_hour_->setCaretVisible (true);
    exec_start_hour_->setPopupMenuEnabled (false);
    exec_start_hour_->setText (String());

    exec_start_hour_->setBounds (195, 120, 25, 24);

    exec_start_min_.reset (new TextEditor ("exec_starttime_minute"));
    addAndMakeVisible (exec_start_min_.get());
    exec_start_min_->setMultiLine (false);
    exec_start_min_->setReturnKeyStartsNewLine (false);
    exec_start_min_->setReadOnly (false);
    exec_start_min_->setScrollbarsShown (false);
    exec_start_min_->setCaretVisible (true);
    exec_start_min_->setPopupMenuEnabled (false);
    exec_start_min_->setText (String());

    exec_start_min_->setBounds (230, 120, 25, 24);

    label_osc_sendaddr_6.reset (new Label ("colon_label1",
                                           TRANS(":")));
    addAndMakeVisible (label_osc_sendaddr_6.get());
    label_osc_sendaddr_6->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_sendaddr_6->setJustificationType (Justification::centred);
    label_osc_sendaddr_6->setEditable (false, false, false);
    label_osc_sendaddr_6->setColour (TextEditor::textColourId, Colours::black);
    label_osc_sendaddr_6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_sendaddr_6->setBounds (216, 120, 16, 24);

    exec_update_inteval_.reset (new TextEditor ("exec_update_interval"));
    addAndMakeVisible (exec_update_inteval_.get());
    exec_update_inteval_->setMultiLine (false);
    exec_update_inteval_->setReturnKeyStartsNewLine (false);
    exec_update_inteval_->setReadOnly (false);
    exec_update_inteval_->setScrollbarsShown (false);
    exec_update_inteval_->setCaretVisible (true);
    exec_update_inteval_->setPopupMenuEnabled (false);
    exec_update_inteval_->setText (String());

    exec_update_inteval_->setBounds (195, 150, 37, 24);

    label_osc_sendaddr_7.reset (new Label ("dash_label",
                                           TRANS("-")));
    addAndMakeVisible (label_osc_sendaddr_7.get());
    label_osc_sendaddr_7->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_sendaddr_7->setJustificationType (Justification::centred);
    label_osc_sendaddr_7->setEditable (false, false, false);
    label_osc_sendaddr_7->setColour (TextEditor::textColourId, Colours::black);
    label_osc_sendaddr_7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_sendaddr_7->setBounds (261, 120, 16, 24);

    exec_end_hour_.reset (new TextEditor ("exec_endtime_hour"));
    addAndMakeVisible (exec_end_hour_.get());
    exec_end_hour_->setMultiLine (false);
    exec_end_hour_->setReturnKeyStartsNewLine (false);
    exec_end_hour_->setReadOnly (false);
    exec_end_hour_->setScrollbarsShown (false);
    exec_end_hour_->setCaretVisible (true);
    exec_end_hour_->setPopupMenuEnabled (false);
    exec_end_hour_->setText (String());

    exec_end_hour_->setBounds (283, 120, 25, 24);

    exec_end_min_.reset (new TextEditor ("exec_endtime_minute"));
    addAndMakeVisible (exec_end_min_.get());
    exec_end_min_->setMultiLine (false);
    exec_end_min_->setReturnKeyStartsNewLine (false);
    exec_end_min_->setReadOnly (false);
    exec_end_min_->setScrollbarsShown (false);
    exec_end_min_->setCaretVisible (true);
    exec_end_min_->setPopupMenuEnabled (false);
    exec_end_min_->setText (String());

    exec_end_min_->setBounds (318, 120, 25, 24);

    label_osc_sendaddr_8.reset (new Label ("colon_label2",
                                           TRANS(":")));
    addAndMakeVisible (label_osc_sendaddr_8.get());
    label_osc_sendaddr_8->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_sendaddr_8->setJustificationType (Justification::centred);
    label_osc_sendaddr_8->setEditable (false, false, false);
    label_osc_sendaddr_8->setColour (TextEditor::textColourId, Colours::black);
    label_osc_sendaddr_8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_sendaddr_8->setBounds (304, 120, 16, 24);

    exec_use_interval_.reset (new ToggleButton ("exec_use_interval"));
    addAndMakeVisible (exec_use_interval_.get());
    exec_use_interval_->setButtonText (TRANS("Use"));

    exec_use_interval_->setBounds (354, 120, 75, 24);

    label_osc_sendaddr_13.reset(new Label("exec_play_interval",
        TRANS("Play interval:")));
    addAndMakeVisible(label_osc_sendaddr_13.get());
    label_osc_sendaddr_13->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
    label_osc_sendaddr_13->setJustificationType(Justification::centredLeft);
    label_osc_sendaddr_13->setEditable(false, false, false);
    label_osc_sendaddr_13->setColour(TextEditor::textColourId, Colours::black);
    label_osc_sendaddr_13->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

    label_osc_sendaddr_13->setBounds(32, 120, 152, 24);

    label.reset(new Label("new label",
        TRANS("seconds")));
    addAndMakeVisible(label.get());
    label->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
    label->setJustificationType(Justification::centredLeft);
    label->setEditable(false, false, false);
    label->setColour(TextEditor::textColourId, Colours::black);
    label->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

    label->setBounds(239, 150, 71, 24);

    /***************************************************************************/

    addAndMakeVisible(label_midi_);
    label_midi_.setFont(Font(25.00f, Font::plain).withTypefaceStyle("Regular"));
    label_midi_.setJustificationType(Justification::centredLeft);
    label_midi_.setEditable(false, false, false);
    label_midi_.setColour(TextEditor::textColourId, Colours::black);
    label_midi_.setColour(TextEditor::backgroundColourId, Colour(0x00000000));

    label_midi_.setBounds(32, 227, 80, 24);

    addAndMakeVisible(label_midi_input_);
    label_midi_input_.setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
    label_midi_input_.setJustificationType(Justification::centredLeft);
    label_midi_input_.setEditable(false, false, false);
    label_midi_input_.setColour(TextEditor::textColourId, Colours::black);
    label_midi_input_.setColour(TextEditor::backgroundColourId, Colour(0x00000000));

    label_midi_input_.setBounds(32, 257, 152, 24);

    addAndMakeVisible(label_midi_output_);
    label_midi_output_.setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
    label_midi_output_.setJustificationType(Justification::centredLeft);
    label_midi_output_.setEditable(false, false, false);
    label_midi_output_.setColour(TextEditor::textColourId, Colours::black);
    label_midi_output_.setColour(TextEditor::backgroundColourId, Colour(0x00000000));

    label_midi_output_.setBounds(32, 287, 152, 24);

    cb_midi_input_.reset(new ComboBox("midi_input"));
    addAndMakeVisible(cb_midi_input_.get());
    cb_midi_input_->setEditableText(false);
    cb_midi_input_->setJustificationType(Justification::centredLeft);
    cb_midi_input_->setTextWhenNothingSelected(TRANS("Select input"));
    cb_midi_input_->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_input_->addListener(this);

    cb_midi_input_->setBounds(195, 257, 150, 24);

    cb_midi_output_.reset(new ComboBox("midi_output"));
    addAndMakeVisible(cb_midi_output_.get());
    cb_midi_output_->setEditableText(false);
    cb_midi_output_->setJustificationType(Justification::centredLeft);
    cb_midi_output_->setTextWhenNothingSelected(TRANS("Select output"));
    cb_midi_output_->setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    cb_midi_output_->addListener(this);

    cb_midi_output_->setBounds(195, 287, 150, 24);

    /******************************************************************************/

    label_osc_3.reset (new Label ("reset_heading",
                                  TRANS("Reset\n")));
    addAndMakeVisible (label_osc_3.get());
    label_osc_3->setFont (Font (25.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_3->setJustificationType (Justification::centredLeft);
    label_osc_3->setEditable (false, false, false);
    label_osc_3->setColour (TextEditor::textColourId, Colours::black);
    label_osc_3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_3->setBounds (465, 360, 80, 24);

    label_osc_sendaddr_9.reset (new Label ("reset_time",
                                           TRANS("Time of day:")));
    addAndMakeVisible (label_osc_sendaddr_9.get());
    label_osc_sendaddr_9->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_sendaddr_9->setJustificationType (Justification::centredLeft);
    label_osc_sendaddr_9->setEditable (false, false, false);
    label_osc_sendaddr_9->setColour (TextEditor::textColourId, Colours::black);
    label_osc_sendaddr_9->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_sendaddr_9->setBounds (465, 390, 152, 24);

    reset_hour_.reset (new TextEditor ("reset_hour"));
    addAndMakeVisible (reset_hour_.get());
    reset_hour_->setMultiLine (false);
    reset_hour_->setReturnKeyStartsNewLine (false);
    reset_hour_->setReadOnly (false);
    reset_hour_->setScrollbarsShown (false);
    reset_hour_->setCaretVisible (true);
    reset_hour_->setPopupMenuEnabled (false);
    reset_hour_->setText (String());

    reset_hour_->setBounds (628, 390, 25, 24);

    reset_min_.reset (new TextEditor ("reset_minute"));
    addAndMakeVisible (reset_min_.get());
    reset_min_->setMultiLine (false);
    reset_min_->setReturnKeyStartsNewLine (false);
    reset_min_->setReadOnly (false);
    reset_min_->setScrollbarsShown (false);
    reset_min_->setCaretVisible (true);
    reset_min_->setPopupMenuEnabled (false);
    reset_min_->setText (String());

    reset_min_->setBounds (663, 390, 25, 24);

    label_osc_sendaddr_11.reset (new Label ("colon_label4",
                                            TRANS(":")));
    addAndMakeVisible (label_osc_sendaddr_11.get());
    label_osc_sendaddr_11->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_sendaddr_11->setJustificationType (Justification::centred);
    label_osc_sendaddr_11->setEditable (false, false, false);
    label_osc_sendaddr_11->setColour (TextEditor::textColourId, Colours::black);
    label_osc_sendaddr_11->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_sendaddr_11->setBounds (649, 390, 16, 24);

    label_osc_sendaddr_10.reset (new Label ("reset_interval",
                                            TRANS("Reset interval:")));
    addAndMakeVisible (label_osc_sendaddr_10.get());
    label_osc_sendaddr_10->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_sendaddr_10->setJustificationType (Justification::centredLeft);
    label_osc_sendaddr_10->setEditable (false, false, false);
    label_osc_sendaddr_10->setColour (TextEditor::textColourId, Colours::black);
    label_osc_sendaddr_10->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_sendaddr_10->setBounds (465, 420, 152, 24);

    label2.reset(new Label("new label",
        TRANS("days")));
    addAndMakeVisible(label2.get());
    label2->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
    label2->setJustificationType(Justification::centredLeft);
    label2->setEditable(false, false, false);
    label2->setColour(TextEditor::textColourId, Colours::black);
    label2->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

    label2->setBounds(672, 420, 46, 24);

    reset_interval_.reset(new TextEditor("reset_interval_"));
    addAndMakeVisible(reset_interval_.get());
    reset_interval_->setMultiLine(false);
    reset_interval_->setReturnKeyStartsNewLine(false);
    reset_interval_->setReadOnly(false);
    reset_interval_->setScrollbarsShown(false);
    reset_interval_->setCaretVisible(true);
    reset_interval_->setPopupMenuEnabled(false);
    reset_interval_->setText(String());

    reset_interval_->setBounds(628, 420, 37, 24);

    /************************************************************************************/

    label_osc_4.reset (new Label ("watchdog_heading",
                                  TRANS("Watchdog\n")));
    addAndMakeVisible (label_osc_4.get());
    label_osc_4->setFont (Font (25.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_4->setJustificationType (Justification::centredLeft);
    label_osc_4->setEditable (false, false, false);
    label_osc_4->setColour (TextEditor::textColourId, Colours::black);
    label_osc_4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_4->setBounds (32, 360, 144, 24);

    label_osc_sendaddr_12.reset (new Label ("watchdog_timeout",
                                            TRANS("Timeout:")));
    addAndMakeVisible (label_osc_sendaddr_12.get());
    label_osc_sendaddr_12->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_sendaddr_12->setJustificationType (Justification::centredLeft);
    label_osc_sendaddr_12->setEditable (false, false, false);
    label_osc_sendaddr_12->setColour (TextEditor::textColourId, Colours::black);
    label_osc_sendaddr_12->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_sendaddr_12->setBounds (32, 420, 152, 24);

    watchdog_timeout_.reset (new TextEditor ("watchdog_timeout"));
    addAndMakeVisible (watchdog_timeout_.get());
    watchdog_timeout_->setMultiLine (false);
    watchdog_timeout_->setReturnKeyStartsNewLine (false);
    watchdog_timeout_->setReadOnly (false);
    watchdog_timeout_->setScrollbarsShown (false);
    watchdog_timeout_->setCaretVisible (true);
    watchdog_timeout_->setPopupMenuEnabled (false);
    watchdog_timeout_->setText (String());

    watchdog_timeout_->setBounds (195, 420, 37, 24);

    label3.reset (new Label ("watchdog_seconds",
                             TRANS("seconds")));
    addAndMakeVisible (label3.get());
    label3->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label3->setBounds (239, 420, 71, 24);

    label_osc_sendaddr_15.reset (new Label ("watchdog_procedure",
                                            TRANS("Watchdog proceedure:")));
    addAndMakeVisible (label_osc_sendaddr_15.get());
    label_osc_sendaddr_15->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_sendaddr_15->setJustificationType (Justification::centredLeft);
    label_osc_sendaddr_15->setEditable (false, false, false);
    label_osc_sendaddr_15->setColour (TextEditor::textColourId, Colours::black);
    label_osc_sendaddr_15->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_sendaddr_15->setBounds (32, 390, 152, 24);

    watchdog_proc_cb_.reset (new ComboBox ("watchdog_proc"));
    addAndMakeVisible (watchdog_proc_cb_.get());
    watchdog_proc_cb_->setEditableText (false);
    watchdog_proc_cb_->setJustificationType (Justification::centredLeft);
    watchdog_proc_cb_->setTextWhenNothingSelected (TRANS("Select proceedure"));
    watchdog_proc_cb_->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    watchdog_proc_cb_->addItem (TRANS("None"), 1);
    watchdog_proc_cb_->addListener (this);

    watchdog_proc_cb_->setBounds (195, 390, 150, 24);

    label_osc_sendaddr_16.reset (new Label ("watchdog_reboot",
                                            TRANS("Reboot test:")));
    addAndMakeVisible (label_osc_sendaddr_16.get());
    label_osc_sendaddr_16->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_sendaddr_16->setJustificationType (Justification::centredLeft);
    label_osc_sendaddr_16->setEditable (false, false, false);
    label_osc_sendaddr_16->setColour (TextEditor::textColourId, Colours::black);
    label_osc_sendaddr_16->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_sendaddr_16->setBounds (32, 450, 152, 24);

    watchdog_soft_btn_.reset (new TextButton ("soft_reboot"));
    addAndMakeVisible (watchdog_soft_btn_.get());
    watchdog_soft_btn_->setButtonText (TRANS("Soft reboot"));
    watchdog_soft_btn_->setColour (TextButton::buttonColourId, Colours::brown);

    watchdog_soft_btn_->setBounds (195, 450, 150, 24);

    watchdog_hard_btn_.reset (new TextButton ("hard_reboot"));
    addAndMakeVisible (watchdog_hard_btn_.get());
    watchdog_hard_btn_->setButtonText (TRANS("Hard reboot"));
    watchdog_hard_btn_->setColour (TextButton::buttonColourId, Colours::brown);

    watchdog_hard_btn_->setBounds (195, 480, 150, 24);

    /***************************************************************/

    label_osc_5.reset (new Label ("OSC heading",
                                  TRANS("Mixer\n")));
    addAndMakeVisible (label_osc_5.get());
    label_osc_5->setFont (Font (25.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_5->setJustificationType (Justification::centredLeft);
    label_osc_5->setEditable (false, false, false);
    label_osc_5->setColour (TextEditor::textColourId, Colours::black);
    label_osc_5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_5->setBounds (465, 192, 80, 24);

    label_osc_sendaddr_17.reset (new Label ("osc_send_adress",
                                            TRANS("Fade-in time:")));
    addAndMakeVisible (label_osc_sendaddr_17.get());
    label_osc_sendaddr_17->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_sendaddr_17->setJustificationType (Justification::centredLeft);
    label_osc_sendaddr_17->setEditable (false, false, false);
    label_osc_sendaddr_17->setColour (TextEditor::textColourId, Colours::black);
    label_osc_sendaddr_17->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_sendaddr_17->setBounds (465, 222, 110, 24);

    mix_fadein_.reset (new TextEditor ("fadein_time"));
    addAndMakeVisible (mix_fadein_.get());
    mix_fadein_->setMultiLine (false);
    mix_fadein_->setReturnKeyStartsNewLine (false);
    mix_fadein_->setReadOnly (false);
    mix_fadein_->setScrollbarsShown (false);
    mix_fadein_->setCaretVisible (true);
    mix_fadein_->setPopupMenuEnabled (false);
    mix_fadein_->setText (String());

    mix_fadein_->setBounds (574, 222, 37, 24);

    label4.reset (new Label ("new label",
                             TRANS("seconds")));
    addAndMakeVisible (label4.get());
    label4->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label4->setBounds (615, 222, 71, 24);

    label_osc_sendaddr_18.reset (new Label ("osc_send_adress",
                                            TRANS("Fade-out time:")));
    addAndMakeVisible (label_osc_sendaddr_18.get());
    label_osc_sendaddr_18->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_sendaddr_18->setJustificationType (Justification::centredLeft);
    label_osc_sendaddr_18->setEditable (false, false, false);
    label_osc_sendaddr_18->setColour (TextEditor::textColourId, Colours::black);
    label_osc_sendaddr_18->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_sendaddr_18->setBounds (465, 252, 110, 24);

    mix_fadeout_.reset (new TextEditor ("fadeout_time"));
    addAndMakeVisible (mix_fadeout_.get());
    mix_fadeout_->setMultiLine (false);
    mix_fadeout_->setReturnKeyStartsNewLine (false);
    mix_fadeout_->setReadOnly (false);
    mix_fadeout_->setScrollbarsShown (false);
    mix_fadeout_->setCaretVisible (true);
    mix_fadeout_->setPopupMenuEnabled (false);
    mix_fadeout_->setText (String());

    mix_fadeout_->setBounds (574, 252, 37, 24);

    label5.reset (new Label ("new label",
                             TRANS("seconds")));
    addAndMakeVisible (label5.get());
    label5->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label5->setBounds (615, 252, 71, 24);

    label_osc_sendaddr_19.reset (new Label ("osc_send_adress",
                                            TRANS("Volume change:")));
    addAndMakeVisible (label_osc_sendaddr_19.get());
    label_osc_sendaddr_19->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label_osc_sendaddr_19->setJustificationType (Justification::centredLeft);
    label_osc_sendaddr_19->setEditable (false, false, false);
    label_osc_sendaddr_19->setColour (TextEditor::textColourId, Colours::black);
    label_osc_sendaddr_19->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label_osc_sendaddr_19->setBounds (465, 282, 110, 24);

    mix_volume_change_.reset (new TextEditor ("volume_change_time"));
    addAndMakeVisible (mix_volume_change_.get());
    mix_volume_change_->setMultiLine (false);
    mix_volume_change_->setReturnKeyStartsNewLine (false);
    mix_volume_change_->setReadOnly (false);
    mix_volume_change_->setScrollbarsShown (false);
    mix_volume_change_->setCaretVisible (true);
    mix_volume_change_->setPopupMenuEnabled (false);
    mix_volume_change_->setText (String());

    mix_volume_change_->setBounds (574, 282, 37, 24);

    label6.reset (new Label ("new label",
                             TRANS("seconds")));
    addAndMakeVisible (label6.get());
    label6->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label6->setBounds (615, 282, 71, 24);


    //[UserPreSize]
	osc_send_port_->setInputRestrictions(5, "0123456789");
	osc_receive_port_->setInputRestrictions(5, "0123456789");
	exec_start_hour_->setInputRestrictions(2, "0123456789");
	exec_start_min_->setInputRestrictions(2, "0123456789");
	exec_end_hour_->setInputRestrictions(2, "0123456789");
	exec_end_min_->setInputRestrictions(2, "0123456789");
	exec_update_inteval_->setInputRestrictions(5, "0123456789.");
	reset_hour_->setInputRestrictions(2, "0123456789");
	reset_min_->setInputRestrictions(2, "0123456789");
	reset_interval_->setInputRestrictions(2, "0123456789");
	watchdog_timeout_->setInputRestrictions(5, "0123456789.");
	mix_fadein_->setInputRestrictions(5, "0123456789.");
	mix_fadeout_->setInputRestrictions(5, "0123456789.");
	mix_volume_change_->setInputRestrictions(5, "0123456789.");

	osc_send_addr_->onReturnKey = [this] { sspOscConsole::send_address_s = osc_send_addr_->getText().toStdString(); };
	osc_send_port_->onReturnKey = [this] { sspOscConsole::send_port_s = osc_send_port_->getText().getIntValue(); };
	osc_receive_port_->onReturnKey = [this] { sspOscConsole::receive_port_s = osc_receive_port_->getText().getIntValue(); };
	exec_start_hour_->onReturnKey = [this] { onEditStartTime(); };
	exec_start_min_->onReturnKey = [this] { onEditStartTime(); };
	exec_end_hour_->onReturnKey = [this] { onEditEndTime(); };
	exec_end_min_->onReturnKey = [this] { onEditEndTime(); };
	exec_use_interval_->onStateChange = [this] {sspExecutiveManager::use_play_interval_s = exec_use_interval_->getToggleState(); };
	exec_update_inteval_->onReturnKey = [this] {sspExecutiveManager::update_interval_s = exec_update_inteval_->getText().getDoubleValue(); };
	reset_hour_->onReturnKey = [this] { onEditResetTime(); };
	reset_min_->onReturnKey = [this] { onEditResetTime(); };
	reset_interval_->onReturnKey = [this] {sspResetManager::reset_interval_s = boost::gregorian::date_duration{ reset_interval_->getText().getIntValue() }; };
	watchdog_timeout_->onReturnKey = [this] {sspResetManager::watchdog_timeout_s = watchdog_timeout_->getText().getDoubleValue(); };
	watchdog_soft_btn_->onClick = [this] {sspResetManager::softReboot(); };
	mix_fadein_->onReturnKey = [this] {sspStreamBus::fadein_time_s = mix_fadein_->getText().getDoubleValue(); };
	mix_fadeout_->onReturnKey = [this] {sspStreamBus::fadeout_time_s = mix_fadeout_->getText().getDoubleValue(); };
	mix_volume_change_->onReturnKey = [this] {sspStreamBus::volume_time_s = mix_volume_change_->getText().getDoubleValue(); };

    //[/UserPreSize]

    setSize (600, 400);

    //[Constructor] You can add your own custom stuff here..
	PropertiesFile::Options options;
	options.applicationName = ProjectInfo::projectName;
	options.folderName = File::getSpecialLocation(File::SpecialLocationType::userApplicationDataDirectory).getChildFile(ProjectInfo::projectName).getFullPathName();
	options.filenameSuffix = ".settings";
	options.osxLibrarySubFolder = "Application Support";
	options.storageFormat = PropertiesFile::storeAsXML;
	app_properties_.setStorageParameters(options);

	loadProperties();

	osc_send_addr_->setText(sspOscConsole::send_address_s, false);
	osc_send_port_->setText(String(sspOscConsole::send_port_s), false);
	osc_receive_port_->setText(String(sspOscConsole::receive_port_s), false);

	exec_startup_cb_->setSelectedItemIndex(static_cast<int>(sspExecutiveManager::startup_proc_s), NotificationType::dontSendNotification);
	exec_shutdown_cb_->setSelectedItemIndex(static_cast<int>(sspExecutiveManager::shutdown_proc_s), NotificationType::dontSendNotification);

	exec_start_hour_->setText(String(sspExecutiveManager::start_time_s.hours()), false);
	exec_start_min_->setText(String(sspExecutiveManager::start_time_s.minutes()), false);
	exec_end_hour_->setText(String(sspExecutiveManager::end_time_s.hours()), false);
	exec_end_min_->setText(String(sspExecutiveManager::end_time_s.minutes()), false);
	exec_use_interval_->setToggleState(sspExecutiveManager::use_play_interval_s, NotificationType::dontSendNotification);
	exec_update_inteval_->setText(String(sspExecutiveManager::update_interval_s), false);

	reset_hour_->setText(String(sspResetManager::reset_time_s.hours()), false);
	reset_min_->setText(String(sspResetManager::reset_time_s.minutes()), false);
	reset_interval_->setText(String(sspResetManager::reset_interval_s.days()), false);

	watchdog_proc_cb_->setSelectedItemIndex(static_cast<int>(sspResetManager::watchdog_type_s), NotificationType::dontSendNotification);
	watchdog_timeout_->setText(String(sspResetManager::watchdog_timeout_s), false);

	mix_fadein_->setText(String(sspStreamBus::fadein_time_s), false);
	mix_fadeout_->setText(String(sspStreamBus::fadeout_time_s), false);
	mix_volume_change_->setText(String(sspStreamBus::volume_time_s), false);

    //[/Constructor]
}

sspSettingsPage::~sspSettingsPage()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	saveProperties();
    //[/Destructor_pre]

    label_osc_ = nullptr;
    osc_send_addr_ = nullptr;
    label_osc_sendport_2 = nullptr;
    label_osc_sendport_ = nullptr;
    label_osc_sendaddr_ = nullptr;
    osc_send_port_ = nullptr;
    osc_receive_port_ = nullptr;
    label_osc_2 = nullptr;
    label_osc_sendaddr_2 = nullptr;
    label_osc_sendaddr_3 = nullptr;
    label_osc_sendaddr_4 = nullptr;
    label_osc_sendaddr_5 = nullptr;
    exec_startup_cb_ = nullptr;
    exec_shutdown_cb_ = nullptr;
    exec_start_hour_ = nullptr;
    exec_start_min_ = nullptr;
    label_osc_sendaddr_6 = nullptr;
    exec_update_inteval_ = nullptr;
    label_osc_sendaddr_7 = nullptr;
    exec_end_hour_ = nullptr;
    exec_end_min_ = nullptr;
    label_osc_sendaddr_8 = nullptr;
    exec_use_interval_ = nullptr;
    label_osc_3 = nullptr;
    label_osc_sendaddr_13 = nullptr;
    label_osc_sendaddr_9 = nullptr;
    reset_hour_ = nullptr;
    reset_min_ = nullptr;
    label_osc_sendaddr_11 = nullptr;
    label_osc_sendaddr_10 = nullptr;
    label = nullptr;
    label2 = nullptr;
    reset_interval_ = nullptr;
    label_osc_4 = nullptr;
    label_osc_sendaddr_12 = nullptr;
    watchdog_timeout_ = nullptr;
    label3 = nullptr;
    label_osc_sendaddr_15 = nullptr;
    watchdog_proc_cb_ = nullptr;
    label_osc_sendaddr_16 = nullptr;
    watchdog_soft_btn_ = nullptr;
    watchdog_hard_btn_ = nullptr;
    label_osc_5 = nullptr;
    label_osc_sendaddr_17 = nullptr;
    mix_fadein_ = nullptr;
    label4 = nullptr;
    label_osc_sendaddr_18 = nullptr;
    mix_fadeout_ = nullptr;
    label5 = nullptr;
    label_osc_sendaddr_19 = nullptr;
    mix_volume_change_ = nullptr;
    label6 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void sspSettingsPage::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    {
        float x = 20.0f, y = 15.0f, width = 412.0f, height = 177.0f;
        Colour fillColour = Colour(0xfb372a3b);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour(fillColour);
        g.fillRoundedRectangle(x, y, width, height, 10.000f);
    }

    {
        float x = 20.0f, y = 212.0f, width = 412.0f, height = 113.0f;
        Colour fillColour = Colour(0xfb372a3b);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour(fillColour);
        g.fillRoundedRectangle(x, y, width, height, 10.000f);
    }

    {
        float x = 20.0f, y = 345.0f, width = 412.0f, height = 170.0f;
        Colour fillColour = Colour(0xfb372a3b);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour(fillColour);
        g.fillRoundedRectangle(x, y, width, height, 10.000f);
    }

    {
        float x = 455.0f, y = 15.0f, width = 260.0f, height = 145.0f;
        Colour fillColour = Colour (0xfb372a3b);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
    }

    {
        float x = 455.0f, y = 182.0f, width = 260.0f, height = 140.0f;
        Colour fillColour = Colour(0xfb372a3b);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour(fillColour);
        g.fillRoundedRectangle(x, y, width, height, 10.000f);
    }

    {
        float x = 455.0f, y = 345.0f, width = 260.0f, height = 113.0f;
        Colour fillColour = Colour (0xfb372a3b);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void sspSettingsPage::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void sspSettingsPage::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == exec_startup_cb_.get())
    {
        //[UserComboBoxCode_exec_startup_cb_] -- add your combo box handling code here..
		sspExecutiveManager::startup_proc_s = sspExecutiveManager::Startup{ exec_startup_cb_->getSelectedItemIndex() };
        //[/UserComboBoxCode_exec_startup_cb_]
    }
    else if (comboBoxThatHasChanged == exec_shutdown_cb_.get())
    {
        //[UserComboBoxCode_exec_shutdown_cb_] -- add your combo box handling code here..
		sspExecutiveManager::shutdown_proc_s = sspExecutiveManager::Shutdown{ exec_shutdown_cb_->getSelectedItemIndex() };
        //[/UserComboBoxCode_exec_shutdown_cb_]
    }
    else if (comboBoxThatHasChanged == watchdog_proc_cb_.get())
    {
        //[UserComboBoxCode_watchdog_proc_cb_] -- add your combo box handling code here..
		sspResetManager::watchdog_type_s = sspWatchdog::Type { watchdog_proc_cb_->getSelectedItemIndex() };
        //[/UserComboBoxCode_watchdog_proc_cb_]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void sspSettingsPage::loadProperties()
{
	PropertiesFile* props = app_properties_.getUserSettings();

	sspAkuratorApplication::getRecentlyOpenedFiles().restoreFromString(props->getValue("recent_files"));
	sspAkuratorApplication::getRecentlyOpenedFiles().removeNonExistentFiles();

	sspOscConsole::send_address_s = props->getValue("send_address", "127.0.0.1").toStdString();
	sspOscConsole::send_port_s = props->getIntValue("send_port", 8001);
	sspOscConsole::receive_port_s = props->getIntValue("receive_port", 9001);

	sspStreamBus::fadein_time_s = props->getDoubleValue("fadein_time", 2.0);
	sspStreamBus::fadeout_time_s = props->getDoubleValue("fadeout_time", 5.0);
	sspStreamBus::volume_time_s = props->getDoubleValue("volume_time", 1.0);

	sspExecutiveManager::startup_proc_s = sspExecutiveManager::Startup{ props->getIntValue("startup_proc", 0) };
	sspExecutiveManager::shutdown_proc_s = sspExecutiveManager::Shutdown{ props->getIntValue("shutdown_proc", 0) };
	sspExecutiveManager::use_play_interval_s = props->getBoolValue("use_interval", true);
	sspExecutiveManager::update_interval_s = props->getDoubleValue("update_interval", 1.0);

	int hour = props->getIntValue("start_hour", 8);
	int minute = props->getIntValue("start_minute", 0);
	sspExecutiveManager::start_time_s = boost::posix_time::time_duration{ hour, minute, 0 };

	hour = props->getIntValue("end_hour", 20);
	minute = props->getIntValue("end_minute", 0);
	sspExecutiveManager::end_time_s = boost::posix_time::time_duration{ hour, minute, 0 };

	hour = props->getIntValue("reset_hour", 20);
	minute = props->getIntValue("reset_minute", 0);
	sspResetManager::reset_time_s = boost::posix_time::time_duration{ hour, minute, 0 };

	int days = props->getIntValue("reset_interval", 1);
	sspResetManager::reset_interval_s = boost::gregorian::date_duration{ days };

	sspResetManager::watchdog_type_s = sspWatchdog::Type{ props->getIntValue("watchdog_type", 0) };
	sspResetManager::watchdog_timeout_s = props->getDoubleValue("watchdog_timeout", 5);

	// Load input value properties (we don't know how many)
	sspDomainData::value_properties_s.clear();
	for (int i = 0;; ++i) {
		String name = "input_value_" + String(i);
		if (props->containsKey(name)) {
			sspDomainData::value_properties_s.push_back(props->getDoubleValue(name, 0.0));
		}
		else {
			break;
		}
	}
}

void sspSettingsPage::saveProperties()
{
	PropertiesFile* props = app_properties_.getUserSettings();

	props->setValue("recent_files", sspAkuratorApplication::getRecentlyOpenedFiles().toString());

	props->setValue("send_address", String(sspOscConsole::send_address_s));
	props->setValue("send_port", sspOscConsole::send_port_s);
	props->setValue("receive_port", sspOscConsole::receive_port_s);

	props->setValue("fadein_time", sspStreamBus::fadein_time_s);
	props->setValue("fadeout_time", sspStreamBus::fadeout_time_s);
	props->setValue("volume_time", sspStreamBus::volume_time_s);

	props->setValue("startup_proc", static_cast<int>(sspExecutiveManager::startup_proc_s));
	props->setValue("shutdown_proc", static_cast<int>(sspExecutiveManager::shutdown_proc_s));
	props->setValue("use_interval", sspExecutiveManager::use_play_interval_s);
	props->setValue("update_interval", sspExecutiveManager::update_interval_s);

	props->setValue("start_hour", sspExecutiveManager::start_time_s.hours());
	props->setValue("start_minute", sspExecutiveManager::start_time_s.minutes());
	props->setValue("end_hour", sspExecutiveManager::end_time_s.hours());
	props->setValue("end_minute", sspExecutiveManager::end_time_s.minutes());

	props->setValue("reset_hour", sspResetManager::reset_time_s.hours());
	props->setValue("reset_minute", sspResetManager::reset_time_s.minutes());
	props->setValue("reset_interval", static_cast<int>(sspResetManager::reset_interval_s.days()));

	props->setValue("watchdog_type", static_cast<int>(sspResetManager::watchdog_type_s));
	props->setValue("watchdog_timeout", sspResetManager::watchdog_timeout_s);

	// Save input value properties
	auto vals = sspDomainData::value_properties_s;
	for (int i = 0; i < vals.size(); ++i) {
		String name = "input_value_" + String(i);
		props->setValue(name, vals[i]);
	}
}

void sspSettingsPage::onEditStartTime()
{
	int hour = exec_start_hour_->getText().getIntValue();
	int minute = exec_start_min_->getText().getIntValue();
	sspExecutiveManager::start_time_s = boost::posix_time::time_duration{ hour, minute, 0 };
}

void sspSettingsPage::onEditEndTime()
{
	int hour = exec_end_hour_->getText().getIntValue();
	int minute = exec_end_min_->getText().getIntValue();
	sspExecutiveManager::end_time_s = boost::posix_time::time_duration{ hour, minute, 0 };
}

void sspSettingsPage::onEditResetTime()
{
	int hour = reset_hour_->getText().getIntValue();
	int minute = reset_min_->getText().getIntValue();
	sspResetManager::reset_time_s = boost::posix_time::time_duration{ hour, minute, 0 };
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="sspSettingsPage" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44">
    <ROUNDRECT pos="455 15 260 145" cornerSize="1e1" fill="solid: fb372a3b"
               hasStroke="0"/>
    <ROUNDRECT pos="20 15 412 177" cornerSize="1e1" fill="solid: fb372a3b" hasStroke="0"/>
    <ROUNDRECT pos="455 340 260 113" cornerSize="1e1" fill="solid: fb372a3b"
               hasStroke="0"/>
    <ROUNDRECT pos="20 283 412 170" cornerSize="1e1" fill="solid: fb372a3b"
               hasStroke="0"/>
    <ROUNDRECT pos="455 180 260 140" cornerSize="1e1" fill="solid: fb372a3b"
               hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="OSC heading" id="34ed693e197018ab" memberName="label_osc_"
         virtualName="" explicitFocusOrder="0" pos="465 30 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="OSC&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="2.5e1"
         kerning="0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="send_addr_editor" id="aae4df3090e4d4b1" memberName="osc_send_addr_"
              virtualName="" explicitFocusOrder="0" pos="576 60 110 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="0"/>
  <LABEL name="Osc receive port" id="12401d3f9c080796" memberName="label_osc_sendport_2"
         virtualName="" explicitFocusOrder="0" pos="465 120 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Receive port:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="1.5e1" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="Osc send port" id="7b0d7a94d123afdb" memberName="label_osc_sendport_"
         virtualName="" explicitFocusOrder="0" pos="465 90 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Send port:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="1.5e1"
         kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="osc_send_adress" id="7e914cf4d34466e3" memberName="label_osc_sendaddr_"
         virtualName="" explicitFocusOrder="0" pos="465 60 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Send address:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="1.5e1" kerning="0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="send_port_editor" id="e20132cc71e8be09" memberName="osc_send_port_"
              virtualName="" explicitFocusOrder="0" pos="576 90 50 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="0"/>
  <TEXTEDITOR name="receive_port_editor" id="29d40c6d87f5baed" memberName="osc_receive_port_"
              virtualName="" explicitFocusOrder="0" pos="576 120 50 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="0"/>
  <LABEL name="OSC heading" id="5bb4fb6610dbafdd" memberName="label_osc_2"
         virtualName="" explicitFocusOrder="0" pos="32 30 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Exec&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="2.5e1"
         kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="osc_send_adress" id="735963bd497d32b0" memberName="label_osc_sendaddr_2"
         virtualName="" explicitFocusOrder="0" pos="32 60 152 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Startup proceedure:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="1.5e1" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="osc_send_adress" id="2b31ecd1a922d855" memberName="label_osc_sendaddr_3"
         virtualName="" explicitFocusOrder="0" pos="32 90 152 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Shutdown proceedure:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="1.5e1" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="osc_send_adress" id="83f385de8a3ff0e7" memberName="label_osc_sendaddr_4"
         virtualName="" explicitFocusOrder="0" pos="32 120 152 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Play interval:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="1.5e1" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="osc_send_adress" id="7460b2d005682854" memberName="label_osc_sendaddr_5"
         virtualName="" explicitFocusOrder="0" pos="32 150 152 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Update interval:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="1.5e1" kerning="0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="startup_proc" id="af295f48d85da11" memberName="exec_startup_cb_"
            virtualName="" explicitFocusOrder="0" pos="195 60 150 24" editable="0"
            layout="33" items="Do nothing&#10;Initialize&#10;Play" textWhenNonSelected="Select proceedure"
            textWhenNoItems="(no choices)"/>
  <COMBOBOX name="shutdown_proc" id="5762e09aa22688cb" memberName="exec_shutdown_cb_"
            virtualName="" explicitFocusOrder="0" pos="195 90 150 24" editable="0"
            layout="33" items="Keep running&#10;Stop&#10;Exit" textWhenNonSelected="Select proceedure"
            textWhenNoItems="(no choices)"/>
  <TEXTEDITOR name="starttime_hour" id="86c6fdbdf8e2df64" memberName="exec_start_hour_"
              virtualName="" explicitFocusOrder="0" pos="195 120 25 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="0"/>
  <TEXTEDITOR name="starttime_minute" id="a07c031bf95d3f4f" memberName="exec_start_min_"
              virtualName="" explicitFocusOrder="0" pos="230 120 25 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="0"/>
  <LABEL name="osc_send_adress" id="8bb70240315c7093" memberName="label_osc_sendaddr_6"
         virtualName="" explicitFocusOrder="0" pos="216 120 16 24" edTextCol="ff000000"
         edBkgCol="0" labelText=":" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="1.5e1"
         kerning="0" bold="0" italic="0" justification="36"/>
  <TEXTEDITOR name="update_interval" id="bf274a0c5be4143e" memberName="exec_update_inteval_"
              virtualName="" explicitFocusOrder="0" pos="195 150 37 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="0"/>
  <LABEL name="osc_send_adress" id="594be5398a83c97f" memberName="label_osc_sendaddr_7"
         virtualName="" explicitFocusOrder="0" pos="261 120 16 24" edTextCol="ff000000"
         edBkgCol="0" labelText="-" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="1.5e1"
         kerning="0" bold="0" italic="0" justification="36"/>
  <TEXTEDITOR name="endtime_hour" id="e54ca9fbb682c6db" memberName="exec_end_hour_"
              virtualName="" explicitFocusOrder="0" pos="283 120 25 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="0"/>
  <TEXTEDITOR name="endtime_minute" id="c05b4efbe7729080" memberName="exec_end_min_"
              virtualName="" explicitFocusOrder="0" pos="318 120 25 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="0"/>
  <LABEL name="osc_send_adress" id="664287ccecd44869" memberName="label_osc_sendaddr_8"
         virtualName="" explicitFocusOrder="0" pos="304 120 16 24" edTextCol="ff000000"
         edBkgCol="0" labelText=":" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="1.5e1"
         kerning="0" bold="0" italic="0" justification="36"/>
  <TOGGLEBUTTON name="new toggle button" id="c2b051aa009d9ccd" memberName="exec_use_interval_"
                virtualName="" explicitFocusOrder="0" pos="354 120 75 24" buttonText="Use"
                connectedEdges="0" needsCallback="0" radioGroupId="0" state="0"/>
  <LABEL name="OSC heading" id="e646e2a8680c0782" memberName="label_osc_3"
         virtualName="" explicitFocusOrder="0" pos="465 358 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Reset&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="2.5e1"
         kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="osc_send_adress" id="e359c6b1dec92863" memberName="label_osc_sendaddr_13"
         virtualName="" explicitFocusOrder="0" pos="32 120 152 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Play interval:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="1.5e1" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="osc_send_adress" id="fe01dc89ceefa985" memberName="label_osc_sendaddr_14"
         virtualName="" explicitFocusOrder="0" pos="216 120 16 24" edTextCol="ff000000"
         edBkgCol="0" labelText=":" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="1.5e1"
         kerning="0" bold="0" italic="0" justification="36"/>
  <LABEL name="osc_send_adress" id="a54117a86617a032" memberName="label_osc_sendaddr_9"
         virtualName="" explicitFocusOrder="0" pos="465 388 152 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Time of day:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="1.5e1" kerning="0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="reset_hour" id="7155cad94482e" memberName="reset_hour_"
              virtualName="" explicitFocusOrder="0" pos="628 388 25 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="0"/>
  <TEXTEDITOR name="reset_minute" id="800627da3cbe977c" memberName="reset_min_"
              virtualName="" explicitFocusOrder="0" pos="663 388 25 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="0"/>
  <LABEL name="osc_send_adress" id="6c465bc403aba25c" memberName="label_osc_sendaddr_11"
         virtualName="" explicitFocusOrder="0" pos="649 388 16 24" edTextCol="ff000000"
         edBkgCol="0" labelText=":" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="1.5e1"
         kerning="0" bold="0" italic="0" justification="36"/>
  <LABEL name="osc_send_adress" id="736d1ca96da8fb16" memberName="label_osc_sendaddr_10"
         virtualName="" explicitFocusOrder="0" pos="465 418 152 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Reset interval:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="1.5e1" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="647dae06d80f9dda" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="239 150 71 24" edTextCol="ff000000"
         edBkgCol="0" labelText="seconds" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="1.5e1"
         kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="a13f9fd9b4e6de9" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="672 418 46 24" edTextCol="ff000000"
         edBkgCol="0" labelText="days" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="1.5e1"
         kerning="0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="reset_interval_" id="8adfbf1984e5a890" memberName="reset_interval_"
              virtualName="" explicitFocusOrder="0" pos="628 418 37 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="0"/>
  <LABEL name="OSC heading" id="f8130b7cb88b7651" memberName="label_osc_4"
         virtualName="" explicitFocusOrder="0" pos="32 299 144 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Watchdog&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="2.5e1" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="osc_send_adress" id="4dad367c9d32657f" memberName="label_osc_sendaddr_12"
         virtualName="" explicitFocusOrder="0" pos="32 359 152 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Timeout:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="1.5e1"
         kerning="0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="watchdog_timeout" id="7dcee50a1656053" memberName="watchdog_timeout_"
              virtualName="" explicitFocusOrder="0" pos="195 359 37 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="0"/>
  <LABEL name="new label" id="c21d34766f77eee9" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="239 359 71 24" edTextCol="ff000000"
         edBkgCol="0" labelText="seconds" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="1.5e1"
         kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="osc_send_adress" id="d6d0361097a92a93" memberName="label_osc_sendaddr_15"
         virtualName="" explicitFocusOrder="0" pos="32 329 152 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Watchdog proceedure:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="1.5e1" kerning="0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="watchdog_proc" id="c0cc6794ac3fef5f" memberName="watchdog_proc_cb_"
            virtualName="" explicitFocusOrder="0" pos="195 329 150 24" editable="0"
            layout="33" items="None" textWhenNonSelected="Select proceedure"
            textWhenNoItems="(no choices)"/>
  <LABEL name="osc_send_adress" id="debb3a74a1d1471d" memberName="label_osc_sendaddr_16"
         virtualName="" explicitFocusOrder="0" pos="32 389 152 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Reboot test:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="1.5e1" kerning="0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="soft_reboot" id="cf51d4ed10ca84bb" memberName="watchdog_soft_btn_"
              virtualName="" explicitFocusOrder="0" pos="195 389 150 24" bgColOff="ffa52a2a"
              buttonText="Soft reboot" connectedEdges="0" needsCallback="0"
              radioGroupId="0"/>
  <TEXTBUTTON name="hard_reboot" id="3bb1ec125d000bc7" memberName="watchdog_hard_btn_"
              virtualName="" explicitFocusOrder="0" pos="195 419 150 24" bgColOff="ffa52a2a"
              buttonText="Hard reboot" connectedEdges="0" needsCallback="0"
              radioGroupId="0"/>
  <LABEL name="OSC heading" id="2ff0d7a77e3ca678" memberName="label_osc_5"
         virtualName="" explicitFocusOrder="0" pos="465 190 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Mixer&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="2.5e1"
         kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="osc_send_adress" id="811cce34212f8bc3" memberName="label_osc_sendaddr_17"
         virtualName="" explicitFocusOrder="0" pos="465 220 110 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Fade-in time:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="1.5e1" kerning="0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="fadein_time" id="889ecee1501ecdff" memberName="mix_fadein_"
              virtualName="" explicitFocusOrder="0" pos="574 220 37 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="0"/>
  <LABEL name="new label" id="b1703552669e79e6" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="615 220 71 24" edTextCol="ff000000"
         edBkgCol="0" labelText="seconds" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="1.5e1"
         kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="osc_send_adress" id="f9f5edf96b63d619" memberName="label_osc_sendaddr_18"
         virtualName="" explicitFocusOrder="0" pos="465 250 110 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Fade-out time:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="1.5e1" kerning="0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="fadeout_time" id="25fa65456494a13f" memberName="mix_fadeout_"
              virtualName="" explicitFocusOrder="0" pos="574 250 37 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="0"/>
  <LABEL name="new label" id="8e193b3dd22746af" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="615 250 71 24" edTextCol="ff000000"
         edBkgCol="0" labelText="seconds" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="1.5e1"
         kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="osc_send_adress" id="4d8300c36f9d8277" memberName="label_osc_sendaddr_19"
         virtualName="" explicitFocusOrder="0" pos="465 280 110 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Volume change:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="1.5e1" kerning="0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="volume_change_time" id="b71fb9efb97f4e6e" memberName="mix_volume_change_"
              virtualName="" explicitFocusOrder="0" pos="574 280 37 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="0"/>
  <LABEL name="new label" id="55e7f47089eb3264" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="615 280 71 24" edTextCol="ff000000"
         edBkgCol="0" labelText="seconds" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="1.5e1"
         kerning="0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

