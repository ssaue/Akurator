/*
  ==============================================================================

    sspLogging.h
    Created: 7 Jan 2019 6:58:19pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include <boost/log/trivial.hpp>

#define SSP_LOG_WRAPPER_WARNING(nWarnings, bOK)\
    nWarnings++; BOOST_LOG_TRIVIAL(warning)
#define SSP_LOG_WRAPPER_ERROR(nErrors, bOK)\
    nErrors++; bOK = false; BOOST_LOG_TRIVIAL(error)
