/*
  ==============================================================================

    sspPlayers.cpp
    Created: 4 May 2019 4:35:05pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "sspPlayers.h"

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT(sspChainPlayer);
BOOST_CLASS_EXPORT(sspConditionalPlayer);
BOOST_CLASS_EXPORT(sspDistributionPlayer);
BOOST_CLASS_EXPORT(sspIndexPlayer);
BOOST_CLASS_EXPORT(sspMidiPlayer);
BOOST_CLASS_EXPORT(sspOSCPlayer);
BOOST_CLASS_EXPORT(sspRandomPlayer);
BOOST_CLASS_EXPORT(sspSequentialPlayer);
BOOST_CLASS_EXPORT(sspSimultaneousPlayer);
BOOST_CLASS_EXPORT(sspSilencePlayer);
