/*
  ==============================================================================

    sspRunPage.cpp
    Created: 28 May 2019 9:56:23pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "sspRunPage.h"

#include "domain/sspDomainData.h"
#include "domain/elements/values/sspValueRange.h"
#include "domain/elements/values/sspBasicValue.h"

//==============================================================================
sspRunPage::sspRunPage(sspDomainData* domain) 
	: domain_(domain)
{
	startTimer(200);
}

sspRunPage::~sspRunPage()
{
}

void sspRunPage::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
	auto b = getLocalBounds();

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (b, 1);   // draw an outline around the component

	if (!val_outputs_.empty()) {
		Colour fillColour = Colour(0xfb372a3b);
		g.setColour(fillColour);
		g.fillRoundedRectangle(b.removeFromTop(80).reduced(5).toFloat(), 10.000f);
	}
}

void sspRunPage::resized()
{
	auto b = getLocalBounds();
	b.removeFromTop(25);
	if (!val_outputs_.empty()) {
		auto group_bounds = b.removeFromTop(40).reduced(5);
		for (auto& edit : val_outputs_) {
			std::get<0>(edit)->setBounds(group_bounds.removeFromLeft(100).reduced(10, 5));
		}
	}
	b.removeFromTop(40);
	if (!sliders_.empty()) {
		auto group_bounds = b.removeFromTop(250).reduced(5);
		for (auto& slide : sliders_) {
			std::get<0>(slide)->setBounds(group_bounds.removeFromLeft(100).reduced(5));
		}
	}
}

void sspRunPage::recreate()
{
	ScopedLock lock(cs_);	
	created_ = false;
	val_outputs_.clear();
	val_inputs_.clear();
	sliders_.clear();
}

void sspRunPage::sliderValueChanged(Slider * slider)
{
	for (auto& slide : sliders_) {
		if (std::get<0>(slide).get() == slider) {
			if (auto ptr = std::get<2>(slide).lock()) {
				ptr->setValue(slider->getValue());
			}
		}
	}
}

void sspRunPage::textEditorReturnKeyPressed(TextEditor &editor)
{
	for (auto& inp : val_inputs_) {
		if (std::get<0>(inp).get() == &editor) {
			if (auto ptr = std::get<2>(inp).lock()) {
				ptr->setValue(editor.getText().getDoubleValue());
			}
		}
	}
}

void sspRunPage::timerCallback()
{
	ScopedLock lock(cs_);
	if (!created_) {
		if (createComponents()) {
			resized();
			repaint();
		}
	}

	for (auto& edit : val_outputs_) {
		if (auto ptr = std::get<2>(edit).lock()) {
			std::get<0>(edit)->setText(String(ptr->getValue()));
		}
	}
}

bool sspRunPage::createComponents()
{
	auto output_values = domain_->getOutputValues();
	if (!output_values.empty()) {
		created_ = true;

		for (auto val : output_values) {
			if (auto ptr = val.lock()) {
				auto edit = std::make_unique<TextEditor>();
				addAndMakeVisible(edit.get());
				edit->setReadOnly(true);
				edit->setCaretVisible(true);
				edit->setText(String(ptr->getValue()), false);
				auto label = std::make_unique<Label>();
				addAndMakeVisible(label.get());
				label->setText(std::string(ptr->getName()).c_str(), NotificationType::dontSendNotification);
				label->attachToComponent(edit.get(), false);
				val_outputs_.push_back(std::make_tuple(std::move(edit), std::move(label), std::move(ptr)));
			}
		}
	}

	auto input_values = domain_->getInputValues();
	if (!input_values.empty()) {
		created_ = true;

		for (auto val : input_values) {
			if (auto s_ptr = std::dynamic_pointer_cast<sspValueRange>(val.lock())) {
				auto slide = std::make_unique<Slider>(Slider::LinearVertical, Slider::TextBoxBelow);
				addAndMakeVisible(slide.get());
				slide->setRange(s_ptr->getMin(), s_ptr->getMax());
				slide->setValue(s_ptr->getValue());
				slide->addListener(this);
				auto label = std::make_unique<Label>();
				addAndMakeVisible(label.get());
				label->setText(std::string(s_ptr->getName()).c_str(), NotificationType::dontSendNotification);
				label->attachToComponent(slide.get(), false);
				sliders_.push_back(std::make_tuple(std::move(slide), std::move(label), s_ptr));
			}
			else if (auto b_ptr = std::dynamic_pointer_cast<sspBasicValue>(val.lock())) {
				auto edit = std::make_unique<TextEditor>();
				addAndMakeVisible(edit.get());
				edit->setReadOnly(false);
				edit->setCaretVisible(true);
				edit->setText(String(b_ptr->getValue()), false);
				edit->addListener(this);
				auto label = std::make_unique<Label>();
				addAndMakeVisible(label.get());
				label->setText(std::string(b_ptr->getName()).c_str(), NotificationType::dontSendNotification);
				label->attachToComponent(edit.get(), false);
				val_inputs_.push_back(std::make_tuple(std::move(edit), std::move(label), b_ptr));
			}
		}
	}
	return created_;
}
