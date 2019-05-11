/*
  ==============================================================================

    sspDomainData.cpp
    Created: 4 Jan 2019 1:27:47pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspDomainData.h"

sspDomainData::sspDomainData()
	: values_(), conditionals_(), strings_(), players_(), tasks_(), timelines_(), inputs_()
{
}

sspWeakVector<sspValueRange> sspDomainData::getAllPossibleInputValues()
{
	sspWeakVector<sspValueRange> inputs;
	for (auto value : values_) {
		auto range = std::dynamic_pointer_cast<sspValueRange>(value);
		if (range) inputs.push_back(range);
	}
	return std::move(inputs);
}

sspWeakVector<sspBoolean> sspDomainData::getAllPossibleInputConditionals()
{
	sspWeakVector<sspBoolean> inputs;
	for (auto cond : conditionals_) {
		auto boolean = std::dynamic_pointer_cast<sspBoolean>(cond);
		if (boolean) inputs.push_back(boolean);
	}
	return std::move(inputs);
}

void sspDomainData::createInitialContent()
{
	// Add root stream
	auto root = std::make_shared<sspTimeline>();
	root->setName("Root stream");
	timelines_.push_back(std::move(root));
}

void sspDomainData::clearContents()
{
	values_.clear();
	conditionals_.clear();
	strings_.clear();
	players_.clear();
	tasks_.clear();
	timelines_.clear();
	inputs_.clear();

	input_values_.clear();
	input_conditionals_.clear();
}

bool sspDomainData::verify(int& nErrors, int& nWarnings) const
{
	bool bReturn = true;

	if (!values_.verify(nErrors, nWarnings)) bReturn = false;
	if (!conditionals_.verify(nErrors, nWarnings)) bReturn = false;
	if (!strings_.verify(nErrors, nWarnings)) bReturn = false;
	if (!players_.verify(nErrors, nWarnings)) bReturn = false;
	if (!tasks_.verify(nErrors, nWarnings)) bReturn = false;
	if (!timelines_.verify(nErrors, nWarnings)) bReturn = false;
	if (!inputs_.verify(nErrors, nWarnings)) bReturn = false;

	return bReturn;
}
