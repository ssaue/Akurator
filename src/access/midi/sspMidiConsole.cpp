/*
  ==============================================================================

    sspMidiConsole.cpp
    Created: 28 Mar 2019 11:07:16pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#include "sspMidiConsole.h"
#include "sspMidiConsoleImpl.h"

#include "sspMidiDevices.h"

juce::String sspMidiConsole::out_device_s = sspMidiDevices::error_device_;
juce::String sspMidiConsole::in_device_s = sspMidiDevices::error_device_;

sspMidiConsole::sspMidiConsole() : impl_(std::make_unique<sspMidiConsoleImpl>())
{
}

sspMidiConsole::~sspMidiConsole()
{
}

bool sspMidiConsole::openDevices()
{
	if (in_device_s != sspMidiDevices::error_device_) {
		if (not impl_->openInputDevice(in_device_s)) return false;
	}

	if (out_device_s != sspMidiDevices::error_device_) {
		if (not impl_->openOutputDevice(out_device_s)) return false;
	}

	return true;
}

void sspMidiConsole::closeDevices()
{
	impl_->closeInputDevice();
	impl_->closeOutputDevice();
}

std::shared_ptr<sspSendChannel> sspMidiConsole::getSendChannel()
{
	return impl_->getSendChannel();
}
