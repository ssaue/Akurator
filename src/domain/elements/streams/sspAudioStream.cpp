/*
  ==============================================================================

    sspAudioStream.cpp
    Created: 1 Feb 2019 3:37:42pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspAudioStream.h"
#include "engine/sspStreamBus.h"
#include "engine/scheduling/sspScheduler.h"
#include "access/sspLogging.h"

sspAudioStream::sspAudioStream()
    : sspStream(), volume_factor_(), bus_(), updater_(sspStreamBus::volume_time_s)
{
    updater_.initialize(false);
}

sspAudioStream::~sspAudioStream()
{
}

void sspAudioStream::start()
{
    updater_.initialize(false);
    if (auto ptr = volume_factor_.lock()) {
        master_volume_ = ptr->getValue();
        bus_->busVolume(master_volume_, sspStreamBus::volume_time_s);
    }
    sspStream::start();
}

void sspAudioStream::update(double seconds)
{
    if (updater_.update()) {
        if (auto ptr = volume_factor_.lock()) {
            double volume = ptr->getValue();
            if (abs(volume - master_volume_) > 0.001) {
                master_volume_ = volume;
                bus_->busVolume(master_volume_, sspStreamBus::volume_time_s);
            }
        }
    }
    sspStream::update(seconds);
}

void sspAudioStream::terminate()
{
    bus_.reset();
    sspStream::terminate();
}

bool sspAudioStream::verify(int& nErrors, int& /*nWarnings*/) const
{
    bool bReturn = true;

    if (volume_factor_.expired()) {
        SSP_LOG_WRAPPER_ERROR(nErrors, bReturn, "{}: Invalid volume fader", getName());
    }

    return bReturn;
}

void sspAudioStream::handleMessage(const sspMessage& msg)
{
    sspStream::handleMessage(msg);

    auto t_ptr = msg.getTime().lock();
    auto v_ptr = msg.getValue().lock();

    switch (msg.getType())
    {
    case sspMessage::Type::Solo:
        is_solostream_ = true;
        if (auto ptr = msg.getTask().lock()) {
            if (ptr->getChannelID() >= 0 && t_ptr) {
                bus_->channelSolo(ptr->getChannelID(), t_ptr->getValue());
            }
        }
        break;
    case sspMessage::Type::Unsolo:
        is_solostream_ = false;
        if (auto ptr = msg.getTask().lock()) {
            if (ptr->getChannelID() >= 0 && t_ptr) {
                bus_->channelUnSolo(ptr->getChannelID(), t_ptr->getValue());
            }
        }
        break;
    case sspMessage::Type::Mute:
        if (t_ptr) bus_->busFadeOut(t_ptr->getValue());
        break;
    case sspMessage::Type::MuteOnSolo:
        if (!is_solostream_ && t_ptr) bus_->busFadeOut(t_ptr->getValue());
        break;
    case sspMessage::Type::Unmute:
        if (t_ptr) bus_->busFadeIn(t_ptr->getValue());
        break;
    case sspMessage::Type::UnmuteOnSolo:
        if (!is_solostream_ && t_ptr) bus_->busFadeIn(t_ptr->getValue());
        break;
    case sspMessage::Type::SetVolume:
        if (t_ptr && v_ptr) {
            bus_->busVolume(v_ptr->getValue(), t_ptr->getValue(), sspStreamBus::Reference::Absolute);
        }
        break;
    case sspMessage::Type::AdjustVolume:
        if (t_ptr && v_ptr) {
            bus_->busVolume(v_ptr->getValue(), t_ptr->getValue(), sspStreamBus::Reference::Relative);
        }
        break;
    default:
        break;
    }
}

void sspAudioStream::setBus(std::unique_ptr<sspStreamBus> mixer)
{
    bus_ = std::move(mixer);
    bus_->setResponder(weak_from_this());
}

bool sspAudioStream::replace(std::weak_ptr<sspPlayTask> task, std::weak_ptr<sspPlayTask> old_task)
{
    if (bus_->play(task, old_task)) {
        sspScheduler::Instance().add(task);
        return true;
    }
    return false;
}
