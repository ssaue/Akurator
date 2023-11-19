/*
  ==============================================================================

    sspOscConsole.h
    Created: 28 Mar 2019 11:07:16pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

#include "engine/sspSendChannel.h"

#include <map>
#include <memory>
#include <string>

class sspOscConsole
{
public:
    static std::string	send_address_s;
    static int		    send_port_s;
    static int		    receive_port_s;

    sspOscConsole();
    sspOscConsole(const sspOscConsole& obj) = delete;
    sspOscConsole& operator= (const sspOscConsole& obj) = delete;
    virtual ~sspOscConsole();

    void connectAll();
    void disconnectAll();
    void initializeChannels();

    bool isSendConnected() const;
    bool isReceiveConnected() const;
    bool verifyPlaying();

    std::map<unsigned int, std::shared_ptr<sspSendChannel>> getBusChannels(unsigned int num);
    void clearChannels();

private:
    std::unique_ptr<class sspOscConsoleImpl> impl_;
};
