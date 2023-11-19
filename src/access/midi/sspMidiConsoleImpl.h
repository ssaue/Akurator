/*
  ==============================================================================

    sspMidiConsoleImpl.h
    Created: 28 Mar 2019 11:07:16pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

#include <juce_audio_devices/juce_audio_devices.h>

#include "engine/sspSendChannel.h"

#include <vector>
#include <map>
#include <atomic>

class sspMidiConsoleImpl : private juce::MidiInputCallback
{
public:
	sspMidiConsoleImpl();
	sspMidiConsoleImpl(const sspMidiConsoleImpl& obj) = delete;
	sspMidiConsoleImpl& operator= (const sspMidiConsoleImpl& obj) = delete;
	virtual ~sspMidiConsoleImpl();

	bool openInputDevice(const juce::String& identifier);
	bool openOutputDevice(const juce::String& identifier);

	void closeInputDevice();
	void closeOutputDevice();

	std::shared_ptr<sspSendChannel> getSendChannel();

private:
	void handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message) override;

	std::unique_ptr<juce::MidiInput> in_device_;
	std::unique_ptr<juce::MidiOutput> out_device_;
};
