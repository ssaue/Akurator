/*
  ==============================================================================

    sspDomainData.h
    Created: 4 Jan 2019 1:27:47pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspDomainPrimitives.h"
#include "sspPlayer.h"
#include "sspPlayTask.h"
#include "sspTimeline.h"
#include "sspInput.h"

#include "sspValueRange.h"
#include "sspBoolean.h"

#include "sspDomainPool.h"

class sspDomainData
{
	sspDomainPool<sspValue>			values_;
	sspDomainPool<sspConditional>	conditionals_;
	sspDomainPool<sspString>		strings_;
	sspDomainPool<sspPlayer>		players_;
	sspDomainPool<sspPlayTask>		tasks_;
	sspDomainPool<sspTimeline>		timelines_;
	sspDomainPool<sspInput>			inputs_;

	sspDomainVector<sspValueRange>	input_values_;
	sspDomainVector<sspBoolean>		input_conditionals_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_NVP(values_);
		ar & BOOST_SERIALIZATION_NVP(conditionals_);
		ar & BOOST_SERIALIZATION_NVP(strings_);
		ar & BOOST_SERIALIZATION_NVP(players_);
		ar & BOOST_SERIALIZATION_NVP(tasks_);
		ar & BOOST_SERIALIZATION_NVP(timelines_);
		ar & BOOST_SERIALIZATION_NVP(input_values_);
		ar & BOOST_SERIALIZATION_NVP(input_conditionals_);
	}

public:
	sspDomainData();
	sspDomainData(const sspDomainData&) = delete;
	sspDomainData& operator=(const sspDomainData&) = delete;
	~sspDomainData() {}

	sspDomainPool<sspValue>&		getValues() { return values_; }
	sspDomainPool<sspConditional>&	getConditionals() { return conditionals_; }
	sspDomainPool<sspString>&		getStrings() { return strings_; }
	sspDomainPool<sspPlayer>&		getPlayers() { return players_; }
	sspDomainPool<sspPlayTask>&		getPlaytasks() { return tasks_; }
	sspDomainPool<sspTimeline>&		getTimelines() { return timelines_; }
	sspDomainPool<sspInput>&		getInputs() { return inputs_; }

	// These values and conditionals are available for input (e.g. from external inputs or from GUI)
	sspDomainVector<sspValueRange>&	getInputValues() { return input_values_; }
	sspDomainVector<sspBoolean>&	getInputConditionals() { return input_conditionals_; }

	sspDomainVector<sspValueRange>	getAllPossibleInputValues();
	sspDomainVector<sspBoolean>		getAllPossibleInputConditionals();

	void createInitialContent();
	void clearContents();
	
	bool verify(int& nErrors, int& nWarnings) const;
};
