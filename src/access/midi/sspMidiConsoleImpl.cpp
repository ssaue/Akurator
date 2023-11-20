/*
  ==============================================================================

    sspMidiConsoleImpl.cpp
    Created: 02 Sep 2022
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "sspMidiConsole.h"
#include "sspMidiConsoleImpl.h"
#include "sspMidiSendChannel.h"

using namespace juce;

sspMidiConsoleImpl::sspMidiConsoleImpl()
{
}

sspMidiConsoleImpl::~sspMidiConsoleImpl()
{
	closeInputDevice();
	closeOutputDevice();
}

bool sspMidiConsoleImpl::openInputDevice(const juce::String& identifier)
{
	closeInputDevice();
	in_device_ = MidiInput::openDevice(identifier, this);

	if (in_device_.get() == nullptr) {
		DBG("sspMidiConsole: open input device " << identifier << " failed!");
		return false;
	}

	in_device_->start();
	return true;
}

bool sspMidiConsoleImpl::openOutputDevice(const juce::String& identifier)
{
	closeOutputDevice();
	out_device_ = MidiOutput::openDevice(identifier);

	if (out_device_.get() == nullptr) {
		DBG("sspMidiConsole: open output device " << identifier << " failed!");
		return false;
	}
	return true;
}

void sspMidiConsoleImpl::closeInputDevice()
{
	if (in_device_ != nullptr) in_device_->stop();
	in_device_.reset();
}

void sspMidiConsoleImpl::closeOutputDevice()
{
	out_device_.reset();
}

std::shared_ptr<sspSendChannel> sspMidiConsoleImpl::getSendChannel()
{
	return std::make_shared<sspMidiSendChannel>(out_device_.get());
}

void sspMidiConsoleImpl::handleIncomingMidiMessage(juce::MidiInput* , const juce::MidiMessage& )
{
	// Not prioritized for now
}

//
//std::map<unsigned int, std::shared_ptr<sspSendChannel>> sspMidiConsoleImpl::getBusChannels(unsigned int num)
//{
//	std::map<unsigned int, std::shared_ptr<sspSendChannel>> bus_channels;
//
//	unsigned int id = static_cast<unsigned int>(channels_.size());
//	for (unsigned int i = 0; i < num; ++i) {
//		auto channel = std::make_shared<sspOscSendChannel>();
//		channel->setBusID(buses_);
//		channel->setChannelID(id + i);
//		channels_.push_back(channel);
//		bus_channels[id + i] = channel;
//	}
//	buses_++;
//	
//	return std::move(bus_channels);
//}
//
//
//void sspMidiConsoleImpl::oscMessageReceived(const OSCMessage & message)
//{
//	static float old_amp = 0.0f;
//	const OSCAddressPattern& address = message.getAddressPattern();
//	if (address == amplitude_) {
//		if (message.size() == 1 && message[0].isFloat32()) {
//			auto amp = message[0].getFloat32();
//			if (amp != old_amp) amp_change_ = true;
//			old_amp = amp;
//		}
//	}
//	else if (address == finished_) {
//		if (message.size() == 1 && message[0].isInt32()) {
//			auto channel = message[0].getInt32();
//			if (channel < channels_.size()) {
//				channels_[channel]->setFinished();
//			}
//		}
//	}
//}
