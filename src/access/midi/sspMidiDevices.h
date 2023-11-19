// ----------------------------------------------------------------------------
// Copyright (C) 2023 Akurator
// All rights reserved.
// ----------------------------------------------------------------------------

#pragma once

#include <juce_audio_devices/juce_audio_devices.h>
#include <vector>
#include <string_view>

inline constexpr std::string_view midi_device_error = "Invalid device";

class sspMidiDevices
{
public:
	static sspMidiDevices& Instance();

	size_t getNumMidiInputs() const { return input_devices_.size(); }
	size_t getNumMidiOutputs() const { return output_devices_.size(); }

	const juce::String& getInputDeviceName(int index) const;
	const juce::String& getOutputDeviceName(int index) const;

	const juce::String& getInputDeviceIdentifier(int index) const;
	const juce::String& getOutputDeviceIdentifier(int index) const;

	// Search for identifier in device liste, returns -1 if not found
	int getInputDeviceIndex(const juce::String& identifier) const;
	int getOutputDeviceIndex(const juce::String& identifier) const;

	const juce::String error_device_;

private:
	sspMidiDevices();
	sspMidiDevices(const sspMidiDevices&) = delete;
	sspMidiDevices& operator=(const sspMidiDevices&) = delete;
	~sspMidiDevices();

	void initializeDeviceList();

	// Device lists
	std::vector<juce::MidiDeviceInfo> input_devices_;
	std::vector<juce::MidiDeviceInfo> output_devices_;

	// Singleton implementation
	static sspMidiDevices* s_instance_;
	static bool s_destroyed_;

	static void create();
	static void onDeadReference();
};

