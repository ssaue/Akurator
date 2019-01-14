/*
  ==============================================================================

    sspConditionals.cpp
    Created: 14 Jan 2019 2:28:33pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspConditionals.h"

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT(sspAnd);
BOOST_CLASS_EXPORT(sspBoolean);
BOOST_CLASS_EXPORT(sspDateInterval);
BOOST_CLASS_EXPORT(sspDayOfWeek);
BOOST_CLASS_EXPORT(sspIsPlaying);
BOOST_CLASS_EXPORT(sspMinuteCompare);
BOOST_CLASS_EXPORT(sspNot);
BOOST_CLASS_EXPORT(sspOr);
BOOST_CLASS_EXPORT(sspTimeCompare);
BOOST_CLASS_EXPORT(sspTimeInterval);
BOOST_CLASS_EXPORT(sspTrigger);
BOOST_CLASS_EXPORT(sspValueCompare);
BOOST_CLASS_EXPORT(sspValueInRange);
