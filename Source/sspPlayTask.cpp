/*
  ==============================================================================

    sspPlayTask.cpp
    Created: 28 Jan 2019 9:54:08am
    Author:  sigurds

  ==============================================================================
*/

#include "sspPlayTask.h"
#include "sspLogging.h"

sspPlayTask::sspPlayTask()
	: sspPlayer(), player_(), condition_(), volume_factor_(), messages_()
{
}

bool sspPlayTask::start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder)
{
	setResponder(responder);
	setSendChannel(channel);
	return true;
}

void sspPlayTask::stop()
{
	if (is_playing_) {
		is_playing_ = false;
		player_->stop();
		messages_[Messages::End]->send();
		messages_[Messages::Exit]->send();
	}
}

void sspPlayTask::onFinished()
{
	sspPlayer::onFinished();
	messages_[Messages::End]->send();
	messages_[Messages::Exit]->send();
}

bool sspPlayTask::isPlaying() const
{
	return is_playing_;
}

bool sspPlayTask::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (!player_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid player";
	}
	if (!condition_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid conditional";
	}
	if (!volume_factor_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid volume factor";
	}
	for (auto&& list : messages_) {
		if (!list->verify(nErrors, nWarnings)) {
			BOOST_LOG_TRIVIAL(info) << "Error found in message lists";
		}
	}
	if (messages_[Messages::Start]->size() != messages_[Messages::End]->size()) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << ": Start and end messages do not match";
	}
	if (messages_[Messages::Enter]->empty() && messages_[Messages::Exit]->empty()) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << " has no enter or exit messages";
	}

	return bReturn;
}

void sspPlayTask::setScheduleTime(double seconds)
{
	next_time_ = (seconds <= 0.0) ? 0UL : static_cast<unsigned long>(1000UL * seconds);
}

bool sspPlayTask::run()
{
	messages_[Messages::Enter]->send();
	is_playing_ = condition_->isTrue() && player_->start(getSendChannel(), weak_from_this());
	if (is_playing_) {
		messages_[Messages::Start]->send();
	}
	else {
		sspPlayer::onFinished();
		messages_[Messages::Exit]->send();
	}
	next_time_ = 0;
	return false;
}

void sspPlayTask::setMessageList(Messages type, std::shared_ptr<sspConditionalMsgList> list)
{
	messages_[type] = list;
}

std::shared_ptr<sspConditionalMsgList> sspPlayTask::getMessageList(Messages type)
{
	return messages_[type];
}

bool sspPlayTask::update()
{
	is_playing_ = false;
	return false;
}
