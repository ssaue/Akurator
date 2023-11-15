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
	static void buildContent(sspDomainData* domain);

private:
	static void buildBasicContent(sspDomainData* domain);
	static void buildInputContent(sspDomainData* domain);
	static void buildUserInputContent(sspDomainData* domain);
	static void buildTimelineHierarchy(sspDomainData* domain);

	static void buildKulisse(sspDomainData* domain);
	static void buildRekke(sspDomainData* domain);
	static void buildSignaler(sspDomainData* domain);
	static void buildAttakker(sspDomainData* domain);	// Includes Kaskader and KulisseBend
	static void buildRens(sspDomainData* domain);
	static void buildDunder(sspDomainData* domain);

	static void buildStartList(sspDomainData* domain);
	static void buildTriggerList(sspDomainData* domain);
	static void buildUserOutput(sspDomainData* domain);
};
