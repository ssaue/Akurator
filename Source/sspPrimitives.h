/*
  ==============================================================================

    sspPrimitives.h
    Created: 3 Jan 2019 11:00:02pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspObject.h"

class sspValue : public sspObject
{
public:
	sspValue() = default;
	sspValue(const sspValue& obj) = delete;
	sspValue& operator= (const sspValue& obj) = delete;
	virtual ~sspValue() {}

	virtual float getValue() const = 0;
	explicit operator float() const { return getValue(); }
};

class sspConditional : public sspObject
{
public:
	sspConditional() = default;
	sspConditional(const sspConditional& obj) = delete;
	sspConditional& operator= (const sspConditional& obj) = delete;
	virtual ~sspConditional() {}

	virtual bool isTrue() const = 0;
	explicit operator bool() const { return isTrue(); }
};

class sspString : public sspObject
{
public:
	sspString() = default;
	sspString(const sspString& obj) = delete;
	sspString& operator= (const sspString& obj) = delete;
	virtual ~sspString() {}

	virtual std::string_view getString() const = 0;
};
