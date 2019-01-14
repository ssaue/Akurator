/*
  ==============================================================================

    sspValues.cpp
    Created: 14 Jan 2019 2:28:11pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspValues.h"

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT(sspBasicValue);
BOOST_CLASS_EXPORT(sspAddValue);
BOOST_CLASS_EXPORT(sspConditionalValue);
BOOST_CLASS_EXPORT(sspDateMap);
BOOST_CLASS_EXPORT(sspLinearMap);
BOOST_CLASS_EXPORT(sspProductValue);
BOOST_CLASS_EXPORT(sspRandomValue);
BOOST_CLASS_EXPORT(sspSecondsRun);
BOOST_CLASS_EXPORT(sspTimeMap);
BOOST_CLASS_EXPORT(sspValueRange);
