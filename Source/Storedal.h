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
};
