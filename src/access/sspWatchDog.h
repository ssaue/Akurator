/*
  ==============================================================================

    sspWatchdogInterface.h
    Created: 15 Apr 2019 2:35:59pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

class sspWatchdog
{
public:
	enum class Type : int { None };

	// TODO: Add implementations when ready
	static sspWatchdog* create(Type /*nType*/) { return nullptr; }

	sspWatchdog() = default;
	sspWatchdog(const sspWatchdog&) = delete;
	sspWatchdog& operator=(const sspWatchdog&) = delete;
	virtual ~sspWatchdog() = 0;

	virtual bool initialize(double secs) = 0;
	virtual bool enable() = 0;
	virtual void refresh() = 0;
	virtual bool disable() = 0;
	virtual bool terminate() = 0;

	virtual int counter() { return 0; }
};
