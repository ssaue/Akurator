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

	std::string addr = address_->getString() + "/start";

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
		ptr->sendMessage(addr, arguments);
	}

	return isPlaying();
}

void sspOSCPlayer::stop()
{
	auto ptr = getSendChannel().lock();
	if (ptr && address_) {
		std::string addr = address_->getString() + "/stop";
		ptr->sendMessage(addr, std::vector<sspSendChannel::ArgumentType>());
	}
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

bool sspOSCPlayer::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (!address_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has no address";
	}
	if (!path_) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << " has no file path";
	}
	if (arguments_.empty()) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << " has no arguments";
	}

	return bReturn;
}
