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
	for (auto& list : messages_) {
		list.reset(new sspConditionalMsgList);
	}
}

bool sspPlayTask::start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder)
{
	if (auto ptr = channel.lock()) {
		ptr->setAssigned(true);
	}
	setResponder(responder);
	setSendChannel(channel);
	return true;
}

void sspPlayTask::stop()
{
	if (is_playing_) {
		is_playing_ = false;
		if (auto ptr = player_.lock()) ptr->stop();
		messages_[Messages::End]->send();
		messages_[Messages::Exit]->send();
	}
}

void sspPlayTask::onFinished()
{
	messages_[Messages::End]->send();
	if (auto ptr = getSendChannel().lock()) {
		ptr->setAssigned(false);
	}
	sspPlayer::onFinished();
	messages_[Messages::Exit]->send();
}

bool sspPlayTask::isPlaying() const
{
	return is_playing_;
}

bool sspPlayTask::verify(int & nErrors, int & nWarnings) const
{
	bool bReturn = true;

	if (player_.expired()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid player";
	}
	if (condition_.expired()) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid conditional";
	}
	if (volume_factor_.expired()) {
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
	return execute(true);
}

bool sspPlayTask::execute(bool run_now)
{
	messages_[Messages::Enter]->send();

	if (run_now) {
		if (auto c_ptr = condition_.lock()) {
			if (c_ptr->isTrue()) {
				if (auto p_ptr = player_.lock()) {
					is_playing_ = p_ptr->start(getSendChannel(), weak_from_this());
				}
			}
		}
	}

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

int sspPlayTask::getID() const
{
	if (auto sender = getSendChannel().lock()) {
		return sender->getID();
	}
	return -1;
}

bool sspPlayTask::update()
{
	is_playing_ = false;
	return false;
}
