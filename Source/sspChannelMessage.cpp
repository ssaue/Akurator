/*
  ==============================================================================

    sspChannelMessage.cpp
    Created: 24 Jan 2019 4:50:58pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspChannelMessage.h"
#include "sspLogging.h"

sspChannelMessage::sspChannelMessage()
	: receiver_(), message_()
{
}

  bool sspChannelMessage::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (!receiver_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << "Channel message has an invalid receiver";
	}
	if (!message_.verify(nErrors, nWarnings)) {
		bReturn = false;
	}

	return bReturn;
}

void sspChannelMessage::send() const
{
	if (receiver_) {
		receiver_->handleMessage(message_);
	}
}
