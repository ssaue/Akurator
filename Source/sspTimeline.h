/*
  ==============================================================================

    sspTimeline.h
    Created: 31 Jan 2019 3:30:06pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspMessageHandler.h"
#include "sspDomainVector.h"
#include "sspDomainPrimitives.h"

#include <memory>
#include <atomic>

class sspTimeline : public sspMessageHandler
{
	sspDomainVector<sspTimeline> children_;
	std::shared_ptr<sspValue> time_factor_;

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
	
	virtual bool verify(int& nErrors, int& nWarnings) const override;
	virtual void handleMessage(const sspMessage&) override {}

	// Accessors
	void setChildren(const sspDomainVector<sspTimeline>& children) { children_ = children; }
	void setTimeFactor(std::shared_ptr<sspValue> factor) { time_factor_ = factor; }

	const sspDomainVector<sspTimeline>& getChildren() const { return children_; }
	std::shared_ptr<sspValue> getTimeFactor() const { return time_factor_; }

protected:
	double getTimeStep(double seconds);
	std::atomic_bool running_ = true;
};
