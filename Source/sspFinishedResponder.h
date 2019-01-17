/*
  ==============================================================================

    sspFinishedResponder.h
    Created: 17 Jan 2019 10:35:34am
    Author:  sigurds

  ==============================================================================
*/

#pragma once

class sspFinishedResponder : public std::enable_shared_from_this<sspFinishedResponder>
{
public:
	virtual void onFinished() = 0;
};
