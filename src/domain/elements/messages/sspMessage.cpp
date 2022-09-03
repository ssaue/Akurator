/*
  ==============================================================================

    sspMessage.cpp
    Created: 24 Jan 2019 3:59:00pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspMessage.h"
#include "access/sspLogging.h"

sspMessage::sspMessage()
	: time_(), task_(), value_()
{
}

  bool sspMessage::verify(int & nErrors, int & /*nWarnings*/) const
{
	bool bReturn = true;

	if (time_.expired()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << "Message has an invalid time";
	}
	switch (type_) {
	case Type::Load:
	case Type::Solo:
	case Type::Unsolo:
		if (task_.expired()) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << "Message has an invalid task";
		}
		break;
	case Type::SetVolume:
	case Type::AdjustVolume:
		if (value_.expired()) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << "Message has an invalid volume value";
		}
		break;
	default:
		break;
	}

	return bReturn;
}
