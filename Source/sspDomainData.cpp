/*
  ==============================================================================

    sspDomainData.cpp
    Created: 4 Jan 2019 1:27:47pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspDomainData.h"

#include "sspBasicValue.h"
#include "sspValueRange.h"
#include "sspBoolean.h"


sspDomainData::sspDomainData()
	: values_(), conditionals_(), strings_(), players_(), tasks_(), timelines_(), inputs_()
	, input_values_(), input_conditionals_(), output_values_(), output_conditionals_()
{
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
