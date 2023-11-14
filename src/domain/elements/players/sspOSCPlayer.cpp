/*
  ==============================================================================

    sspOSCPlayer.cpp
    Created: 17 Jan 2019 1:38:16pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspOSCPlayer.h"
#include "access/sspLogging.h"

sspOSCPlayer::sspOSCPlayer()
	: sspPlayer(), address_(), path_(), arguments_()
{
}

bool sspOSCPlayer::start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder)
{
	auto addr_ptr = address_.lock();
	if (isPlaying() || channel.expired() || !addr_ptr)
		return false;

	std::string addr = addr_ptr->getString();

	std::vector<sspSendChannel::ArgumentType> arguments;
	auto path_ptr = path_.lock();
	auto path = path_ptr ? path_ptr->getString() : std::string();
 	arguments.push_back(path);

	for (auto &&arg : arguments_) {
		if (auto ptr = arg.lock()) 
			arguments.push_back(static_cast<float>(ptr->getValue()));
	}

	if (auto chan_ptr = channel.lock()) {
		setSendChannel(channel);
		setResponder(responder);
		chan_ptr->setResponder(weak_from_this());
		chan_ptr->sendMessage(addr, arguments);
	}

	return isPlaying();
}

void sspOSCPlayer::stop()
{
	if (auto channel = getSendChannel().lock()) {
		channel->clearResponder();
		channel->stop();
	}
	clearSendChannel();
}

bool sspOSCPlayer::update()
{
	if (auto channel = getSendChannel().lock()) {
		channel->clearResponder();
	}
	return false;
}

bool sspOSCPlayer::isPlaying() const
{
	return !getSendChannel().expired();
}

bool sspOSCPlayer::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (address_.expired()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: No address", getName());
	}
	if (path_.expired()) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn, "{}: No file path", getName());
	}
	if (arguments_.empty()) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn, "{}: No arguments", getName());
	}

	return bReturn;
}
