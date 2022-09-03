/*
  ==============================================================================

    sspStrings.cpp
    Created: 14 Jan 2019 2:28:47pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspStrings.h"

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT(sspConcatString);
BOOST_CLASS_EXPORT(sspFileString);
BOOST_CLASS_EXPORT(sspSelectString);
BOOST_CLASS_EXPORT(sspSimpleString);
