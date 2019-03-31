/*
  ==============================================================================

    sspDomainData.cpp
    Created: 4 Jan 2019 1:27:47pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspDomainData.h"

sspDomainData::sspDomainData()
	: sspDomainElement(), values_(), conditionals_(), strings_(), players_(), tasks_(), timelines_()
{
}

void sspDomainData::createInitialContent()
{
	// Add root stream
	auto root = std::make_shared<sspTimeline>();
	root->setName("Root stream");
	timelines_.add(std::move(root));
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

	return bReturn;
}
