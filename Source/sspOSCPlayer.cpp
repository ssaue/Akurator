/*
  ==============================================================================

    sspOSCPlayer.cpp
    Created: 17 Jan 2019 1:38:16pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspOSCPlayer.h"
#include "sspLogging.h"

sspOSCPlayer::sspOSCPlayer()
	: sspPlayer(), address_(), path_(), arguments_()
{
}

bool sspOSCPlayer::start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder)
{
	if (isPlaying() || channel.expired() || !address_)
		return false;

	std::vector<sspSendChannel::ArgumentType> arguments;
	auto path = path_ ? path_->getString() : std::string();
 	arguments.push_back(path);

	for (auto &&arg : arguments_) {
		arguments.push_back(static_cast<float>(arg->getValue()));
	}

	if (auto ptr = channel.lock()) {
		setSendChannel(channel);
		setResponder(responder);
		ptr->setResponder(weak_from_this());
		ptr->sendMessage(address_->getString(), arguments);
	}

	return isPlaying();
}

void sspOSCPlayer::stop()
{
	setSendChannel(std::weak_ptr<sspSendChannel>());
}

bool sspOSCPlayer::update()
{
	return false;
}

bool sspOSCPlayer::isPlaying() const
{
	return !getSendChannel().expired();
}

bool sspOSCPlayer::verify(int & nErrors, int & /*nWarnings*/) const
{
	bool bReturn = true;

//	if (!duration_) {
//		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has an invalid duration";
//	}
//	if (!silence_) {
//		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has an invalid silence object";
//	}

	return bReturn;
}
