/*
  ==============================================================================

    Bekkelaget.h
    Created: 4 May 2019 12:48:32pm
    Author:  Admin

  ==============================================================================
*/

#pragma once

class sspDomainData;
class sspPlayManager;

// Utility class for building all Bekkelaget content

struct Bekkelaget {
	static void buildContent(sspDomainData* domain, sspPlayManager* manager);

private:
	static void buildBasicContent(sspDomainData* domain);
	static void buildInputContent(sspDomainData* domain);
	static void buildUserInputContent(sspDomainData* domain);
	static void buildTimelineHierarchy(sspDomainData* domain);

	static void buildHallDraape(sspDomainData* domain);
	static void buildHallKepler(sspDomainData* domain);
	static void buildHallKaskade(sspDomainData* domain);
	static void buildHallKonkret(sspDomainData* domain);
	static void buildTunnelKaskade(sspDomainData* domain);
	static void buildTunnelKonkret(sspDomainData* domain);

	//static void buildKulisse(sspDomainData* domain);
	//static void buildRekke(sspDomainData* domain);
	//static void buildSignaler(sspDomainData* domain);
	//static void buildAttakker(sspDomainData* domain);	// Includes Kaskader and KulisseBend
	//static void buildRens(sspDomainData* domain);
	//static void buildDunder(sspDomainData* domain);

	static void buildStartList(sspDomainData* domain, sspPlayManager* manager);
	static void buildUserOutput(sspDomainData* domain);
};
