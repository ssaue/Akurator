/*
  ==============================================================================

    sspMessageWithReceiver.cpp
    Created: 24 Jan 2019 4:50:58pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspMessageWithReceiver.h"
#include "access/sspLogging.h"

sspMessageWithReceiver::sspMessageWithReceiver()
	: receiver_(), message_()
{
}

  bool sspMessageWithReceiver::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (receiver_.expired()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << "Channel message has an invalid receiver";
	}
	if (!message_.verify(nErrors, nWarnings)) {
		bReturn = false;
	}

	return bReturn;
}

void sspMessageWithReceiver::send() const
{
	if (auto ptr = receiver_.lock()) {
		ptr->handleMessage(message_);
	}
}
