// ----------------------------------------------------------------------------
// Copyright (C) 2023 Akurator
// All rights reserved.
// ----------------------------------------------------------------------------

#include "sspMidiDevices.h"

using namespace juce;

sspMidiDevices* sspMidiDevices::s_instance_ = nullptr;
bool sspMidiDevices::s_destroyed_ = false;

sspMidiDevices::sspMidiDevices() : error_device_(midi_device_error.data())
{
	initializeDeviceList();
}

sspMidiDevices::~sspMidiDevices()
{
}

const String& sspMidiDevices::getInputDeviceName(int index) const
{
	return (index >= 0 && index < getNumMidiInputs()) ? input_devices_[index].name : error_device_;
}

const String& sspMidiDevices::getOutputDeviceName(int index) const
{
	return (index >= 0 && index < getNumMidiOutputs()) ? output_devices_[index].name : error_device_;
}

const String& sspMidiDevices::getInputDeviceIdentifier(int index) const
{
	return (index >= 0 && index < getNumMidiInputs()) ? input_devices_[index].identifier : error_device_;
}

const String& sspMidiDevices::getOutputDeviceIdentifier(int index) const
{
	return (index >= 0 && index < getNumMidiOutputs()) ? output_devices_[index].identifier : error_device_;
}

int sspMidiDevices::getInputDeviceIndex(const String& identifier) const
{
	if (identifier.isNotEmpty() && identifier != error_device_) {
		int device_index = 0;
		for (auto& device : input_devices_) {
			if (device.identifier == identifier) return device_index;
			device_index++;
		}
	}
	return -1;	// Identifier not found
}

int sspMidiDevices::getOutputDeviceIndex(const String& identifier) const
{
	if (identifier.isNotEmpty() && identifier != error_device_) {
		int device_index = 0;
		for (auto& device : output_devices_) {
			if (device.identifier == identifier) return device_index;
			device_index++;
		}
	}
	return -1;	// Identifier not found
}

void sspMidiDevices::initializeDeviceList()
{
	for (auto& newDevice : MidiInput::getAvailableDevices()) {
		input_devices_.emplace_back(newDevice);
	}

	for (auto& newDevice : MidiOutput::getAvailableDevices()) {
		output_devices_.emplace_back(newDevice);
	}
}


/*
** Singleton stuff
*/

sspMidiDevices& sspMidiDevices::Instance()
{
	if (!s_instance_) {
		if (s_destroyed_) {
			onDeadReference();
		}
		else {
			create();
		}
	}
	return *s_instance_;
}

void sspMidiDevices::create()
{
	static sspMidiDevices theInstance;
	s_instance_ = &theInstance;
}

void sspMidiDevices::onDeadReference()
{
	throw std::runtime_error("Dead reference to sspExecutionState detected");
}
