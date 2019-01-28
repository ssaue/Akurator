/*
  ==============================================================================

    sspTimeCompare.cpp
    Created: 10 Jan 2019 11:58:53am
    Author:  sigurds

  ==============================================================================
*/

#include "sspTimeCompare.h"
#include "sspLogging.h"

using namespace boost::posix_time;

  sspTimeCompare::sspTimeCompare()
	  : sspConditional(), clock_()
  {
  }

  bool sspTimeCompare::isTrue() const
{
	auto now = second_clock::local_time().time_of_day();
	switch (relation_) {
	case Relation::Before:
		return now < clock_;
	case Relation::After:
		return now > clock_;
	default:
		return false;
	}
}

bool sspTimeCompare::verify(int & /*nErrors*/, int & /*nWarnings*/) const
{
	return true;
}
