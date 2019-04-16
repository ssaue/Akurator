/*
  ==============================================================================

    sspInput.h
    Created: 16 Apr 2019 12:08:10pm
    Author:  Sigurd Saue

  ==============================================================================
*/

#pragma once

#include "sspDomainElement.h"
#include "sspTimeUpdater.h"

class sspInput : public sspDomainElement
{
	double update_interval_ = 1.0;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspDomainElement);
		ar & BOOST_SERIALIZATION_NVP(update_interval_);
	}

public:
	sspInput();
	sspInput(const sspInput& obj) = delete;
	sspInput& operator= (const sspInput& obj) = delete;
	virtual ~sspInput() {}

	virtual bool initialize();
	virtual bool update();
	virtual void terminate() = 0;

	virtual bool verify(int& nErrors, int& nWarnings) const override;

	void setUpdateInterval(double secs) { update_interval_ = secs; }
	double getUpdateInterval() const { return update_interval_; }

private:
	sspTimeUpdater updater_;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(sspInput)
