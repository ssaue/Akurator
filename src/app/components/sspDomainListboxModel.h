/*
  ==============================================================================

    sspDomainListboxModel.h
    Created: 3 May 2019 7:54:25pm
    Author:  Admin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

template <typename T>
class sspDomainPool;

class sspListboxModel : public juce::ListBoxModel
{
public:
	virtual void onAdd() = 0;
};

template <typename T>
class sspDomainListboxModel : public sspListboxModel
{
public:
	sspDomainListboxModel(sspDomainPool<T> *pool)
		: pool_(pool)
	{
	}

	virtual void onAdd()
	{
	}

	void onSelected()
	{
		if (row_selected_ < 0) {
			// TODO: Hide domain object menu
		}
		else {
			// TODO: Display a domain object menu
		}
	}

	int getNumRows() override
	{
		return static_cast<int>(pool_->size());
	}

	void paintListBoxItem(int rowNumber, Graphics& g,
		int width, int height, bool rowIsSelected) override
	{
		if (rowIsSelected)
			g.fillAll(Colours::lightblue);

		g.setColour(LookAndFeel::getDefaultLookAndFeel().findColour(Label::textColourId));
		g.setFont(height * 0.7f);

		if (rowNumber < pool_->size()) {
			std::stringstream text;
			text << rowNumber << ": " << std::string(pool_->at(rowNumber)->getName()).c_str();
			g.drawText(text.str(),
				5, 0, width, height,
				Justification::centredLeft, true);
		}
	}

	virtual void listBoxItemClicked(int row, const MouseEvent&) override
	{
		row_selected_ = (row < pool_->size()) ? row : -1;
		onSelected();
	}

	virtual void backgroundClicked(const MouseEvent&) override
	{
		row_selected_ = -1;
		onSelected();
	}

	virtual void selectedRowsChanged(int lastRowSelected) override
	{
		row_selected_ = (lastRowSelected < pool_->size()) ? lastRowSelected : -1;
		onSelected();
	}

	virtual void deleteKeyPressed(int lastRowSelected) override
	{
		if (lastRowSelected < pool_->size()) {
			auto elem = pool_->begin() + lastRowSelected;
			pool_->erase(elem);
		}
		row_selected_ = -1;
		onSelected();
	}


private:
	sspDomainPool<T> *pool_;
	int row_selected_ = -1;
};
