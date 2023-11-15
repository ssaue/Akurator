/*
  ==============================================================================

    BlankProject.cpp
    Created: 9 Jun 2019 10:01:58pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "BlankProject.h"

#include "domain/sspDomainData.h"
#include "domain/core/sspTimeline.h"


void BlankProject::buildContent(sspDomainData* domain)
{
	if (!domain) return;

	domain->clearContents();

	// As a minimum there has to be a root timeline
	auto root = std::make_shared<sspTimeline>();
	root->setName("Root stream");
	domain->getTimelines().push_back(std::move(root));
}
