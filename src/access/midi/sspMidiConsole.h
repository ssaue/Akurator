/*
  ==============================================================================

    sspMidiConsole.h
    Created: 28 Mar 2019 11:07:16pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

#include "juce_core/juce_core.h"
#include "engine/sspSendChannel.h"

#include <map>
#include <memory>
#include <string>

class sspMidiConsole
{
public:
    static juce::String	out_device_s;
    static juce::String in_device_s;

    sspMidiConsole();
    sspMidiConsole(const sspMidiConsole& obj) = delete;
    sspMidiConsole& operator= (const sspMidiConsole& obj) = delete;
    virtual ~sspMidiConsole();

    bool openDevices();
    void closeDevices();

    std::shared_ptr<sspSendChannel> getSendChannel();

private:
    std::unique_ptr<class sspMidiConsoleImpl> impl_;
};
