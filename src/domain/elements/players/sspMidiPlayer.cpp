/*
  ==============================================================================

    sspMidiPlayer.cpp
    Created: 14 Nov 2023
    Author:  sigurds

  ==============================================================================
*/

#include "sspMidiPlayer.h"
#include "access/sspLogging.h"

sspMidiPlayer::sspMidiPlayer()
	: sspPlayer(), file_path_(), tempo_factor_()
{
}

bool sspMidiPlayer::start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder)
{
	auto path_ptr = file_path_.lock();
	if (isPlaying() || channel.expired() || not path_ptr)
		return false;

	auto value_ptr = tempo_factor_.lock();
	auto tempo_fac = value_ptr ? value_ptr->getValue() : 1.0;

	if (auto chan_ptr = channel.lock()) {
		setSendChannel(channel);
		setResponder(responder);
		chan_ptr->setResponder(weak_from_this());
		if (not chan_ptr->play(path_ptr->getString(), tempo_fac)) {
			return false;
		}
	}

	return isPlaying();
}

void sspMidiPlayer::stop()
{
	if (auto channel = getSendChannel().lock()) {
		channel->clearResponder();
		channel->stop();
	}
	clearSendChannel();
}

bool sspMidiPlayer::update()
{
	if (auto channel = getSendChannel().lock()) {
		channel->clearResponder();
	}
	return false;
}

bool sspMidiPlayer::isPlaying() const
{
	return not getSendChannel().expired();
}

bool sspMidiPlayer::verify(int & nErrors, int & ) const
{
	bool bReturn = true;

	if (file_path_.expired()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: No Midi file path", getName());
	}
	if (tempo_factor_.expired()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid tempo factor value", getName());
	}

	return bReturn;
}
