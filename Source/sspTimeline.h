/*
  ==============================================================================

    sspTimeline.h
    Created: 31 Jan 2019 3:30:06pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspMessageHandler.h"
#include "sspObjectVector.h"
#include "sspPrimitives.h"

#include <memory>

class sspTimeline : public sspMessageHandler
{
	sspObjectVector<sspTimeline> children_;
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

	virtual bool empty() const;
	
	virtual bool verify(int& nErrors, int& nWarnings) const override;
	virtual void handleMessage(const sspMessage&) override {}

	// Accessors
	void setChildren(const sspObjectVector<sspTimeline>& children) { children_ = children; }
	void setTimeFactor(std::shared_ptr<sspValue> factor) { time_factor_ = factor; }

	const sspObjectVector<sspTimeline>& getChildren() const { return children_; }
	std::shared_ptr<sspValue> getTimeFactor() const { return time_factor_; }

protected:
	double getTimeStep(double seconds);
	bool running_ = true;
};
