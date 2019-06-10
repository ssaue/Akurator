/*
  ==============================================================================

    sspTimeline.h
    Created: 31 Jan 2019 3:30:06pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspMessageHandler.h"
#include "sspSharedVector.h"
#include "sspDomainPrimitives.h"
#include "sspFinishedResponder.h"

#include <memory>
#include <atomic>

class sspTimeline : public sspMessageHandler, public sspFinishedResponder
{
	sspWeakVector<sspTimeline> children_;
	std::weak_ptr<sspValue> time_factor_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspMessageHandler);
		ar & BOOST_SERIALIZATION_NVP(children_);
		ar & BOOST_SERIALIZATION_NVP(time_factor_);
	}

public:
	sspTimeline();
	sspTimeline(const sspTimeline& obj) = delete;
	sspTimeline& operator= (const sspTimeline& obj) = delete;
	virtual ~sspTimeline() {}

	virtual void start();
	virtual void update(double seconds);
	virtual void stop();
	virtual void terminate();

	virtual bool empty() const;

	virtual void onFinished() override {}
	virtual bool verify(int& nErrors, int& nWarnings) const override;
	virtual void handleMessage(const sspMessage&) override;

	// Accessors
	void setChildren(const sspWeakVector<sspTimeline>& children) { children_ = children; }
	void setTimeFactor(std::weak_ptr<sspValue> factor) { time_factor_ = factor; }

	const sspWeakVector<sspTimeline>& getChildren() const { return children_; }
	std::weak_ptr<sspValue> getTimeFactor() const { return time_factor_; }

protected:
	double getTimeStep(double seconds);
	std::atomic_bool running_ = true;
};
