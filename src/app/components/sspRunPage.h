/*
  ==============================================================================

    sspRunPage.h
    Created: 28 May 2019 9:56:23pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class sspDomainData;
class sspValue;
class sspBasicValue;
class sspValueRange;

class sspRunPage : public juce::Component
	, private juce::Slider::Listener
	, private juce::TextEditor::Listener
	, private juce::Timer
{
public:
    sspRunPage(sspDomainData* domain);
    ~sspRunPage();

    void paint (juce::Graphics&) override;
    void resized() override;

	void recreate();

private:
	sspDomainData* domain_;
	bool created_ = false;

	std::vector<std::tuple<std::unique_ptr<TextEditor>, std::unique_ptr<Label>, std::weak_ptr<sspValue>>> val_outputs_;
	std::vector<std::tuple<std::unique_ptr<TextEditor>, std::unique_ptr<Label>, std::weak_ptr<sspBasicValue>>> val_inputs_;
	std::vector<std::tuple<std::unique_ptr<Slider>, std::unique_ptr<Label>, std::weak_ptr<sspValueRange>>> sliders_;

	bool createComponents();
	void sliderValueChanged(Slider* slider) override;
	virtual void textEditorReturnKeyPressed(TextEditor&) override;
	void timerCallback() override;

	CriticalSection cs_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (sspRunPage)
};
