/*
  ==============================================================================

    HMM.h
    Created: 23 Nov 2023
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

class sspDomainData;

// Utility class for building all Bekkelaget content

struct HMM {
	static void buildContent(sspDomainData* domain);

private:
	static void buildBasicContent(sspDomainData* domain);
	static void buildTimelineHierarchy(sspDomainData* domain);
	static void buildPlayer(sspDomainData* domain);
	static void buildStartList(sspDomainData* domain);
};
