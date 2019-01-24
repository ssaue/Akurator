/*
  ==============================================================================

    sspTrigger.h
    Created: 10 Jan 2019 12:01:11pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPrimitives.h"
#include <boost/serialization/shared_ptr.hpp>

class sspTrigger : public sspConditional
{
public:
	enum class Trigger : unsigned int { False, True, Both };

private:
	std::shared_ptr<sspConditional> conditional_;
	Trigger change_;

	mutable bool old_state_ = false;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspConditional);
		ar & BOOST_SERIALIZATION_NVP(conditional_);
		ar & BOOST_SERIALIZATION_NVP(change_);
	}

public:
	sspTrigger() = default;
	sspTrigger(const sspTrigger& cond) = delete;
	sspTrigger& operator= (const sspTrigger& cond) = delete;
	virtual ~sspTrigger() {}

	// Virtual methods
	virtual bool isTrue() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setConditional(std::shared_ptr<sspConditional> cond) { conditional_ = std::move(cond); }
	void setChange(Trigger change) { change_ = change; }

	std::shared_ptr<sspConditional> getConditional() const { return conditional_; }
	Trigger getChange() const { return change_; }

	void reset();
};
