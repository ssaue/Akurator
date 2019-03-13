/*
  ==============================================================================

    sspMessage.h
    Created: 24 Jan 2019 3:59:00pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspDomainPrimitives.h"

#include <memory>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/weak_ptr.hpp>

class sspPlayTask;

class sspMessage
{
public:
	enum class Type {Load, Solo, Mute, Unsolo, Unmute, SetVolume, AdjustVolume, Start, Stop, None};

private:
	Type type_ = Type::None;
	std::shared_ptr<sspValue> time_;
	std::weak_ptr<sspPlayTask> task_;
	std::shared_ptr<sspValue> value_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_NVP(type_);
		ar & BOOST_SERIALIZATION_NVP(time_);
		ar & BOOST_SERIALIZATION_NVP(task_);
		ar & BOOST_SERIALIZATION_NVP(value_);
	}

public:
	sspMessage();
	sspMessage(const sspMessage& obj) = delete;
	sspMessage& operator= (const sspMessage& obj) = delete;
	virtual ~sspMessage() {}

	bool verify(int& nErrors, int& nWarnings) const;

	// Accessors
	void setType(Type type) { type_ = type; }
	void setTime(std::shared_ptr<sspValue> time) { time_ = time; }
	void setTask(std::weak_ptr<sspPlayTask> task) { task_ = task; }
	void setValue(std::shared_ptr<sspValue> value) { value_ = value; }

	Type getType() const { return type_; }
	std::shared_ptr<sspValue> getTime() const { return time_; }
	std::weak_ptr<sspPlayTask> getTask() const { return task_; }
	std::shared_ptr<sspValue> getValue() const { return value_; }
};
