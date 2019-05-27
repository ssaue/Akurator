/*
  ==============================================================================

    Storedal.h
    Created: 4 May 2019 12:48:32pm
    Author:  Admin

  ==============================================================================
*/

#pragma once

class sspDomainData;
class sspPlayManager;

// Utility class for building all Storedal content

struct Storedal {
	static void buildContent(sspDomainData* domain, sspPlayManager* manager);

private:
	static void buildBasicContent(sspDomainData* domain);
	static void buildInputContent(sspDomainData* domain);
	static void buildUserInputContent(sspDomainData* domain);
	static void buildTimelineHierarchy(sspDomainData* domain);

	static void buildKulisse(sspDomainData* domain);

	static void buildStartList(sspDomainData* domain, sspPlayManager* manager);
	static void buildUserOutput(sspDomainData* domain);
};
