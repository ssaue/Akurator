/*
  ==============================================================================

	sspDomainData.h
	Created: 4 Jan 2019 1:27:47pm
	Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "domain/core/sspDomainPrimitives.h"
#include "domain/core/sspPlayer.h"
#include "domain/core/sspPlayTask.h"
#include "domain/core/sspTimeline.h"
#include "domain/core/sspInput.h"

#include "domain/core/sspDomainPool.h"
#include "domain/core/sspSharedVector.h"

#include "domain/elements/messages/sspConditionalMsgList.h"
#include "domain/elements/messages/sspTriggerMsgList.h"
#include "domain/elements/messages/sspTimeTriggerMsgList.h"


class sspDomainData
{
	sspDomainPool<sspValue>			values_;
	sspDomainPool<sspConditional>	conditionals_;
	sspDomainPool<sspString>		strings_;
	sspDomainPool<sspPlayer>		players_;
	sspDomainPool<sspPlayTask>		tasks_;
	sspDomainPool<sspTimeline>		timelines_;
	sspDomainPool<sspInput>			inputs_;

	// Message lists
	std::shared_ptr<sspConditionalMsgList>	start_messages_;
	std::shared_ptr<sspTriggerMsgList>		trigger_messages_;
	std::shared_ptr<sspTimeTriggerMsgList>	clock_messages_;

	// These vectors represent selections of values and conditionals
	// that could serve as input or output through GUI
	sspWeakVector<sspValue>			input_values_;
	sspWeakVector<sspValue>			output_values_;
	sspWeakVector<sspConditional>	input_conditionals_;
	sspWeakVector<sspConditional>	output_conditionals_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int /*version*/) {
		ar& BOOST_SERIALIZATION_NVP(values_);
		ar& BOOST_SERIALIZATION_NVP(conditionals_);
		ar& BOOST_SERIALIZATION_NVP(strings_);
		ar& BOOST_SERIALIZATION_NVP(players_);
		ar& BOOST_SERIALIZATION_NVP(timelines_);
		ar& BOOST_SERIALIZATION_NVP(tasks_);
		ar& BOOST_SERIALIZATION_NVP(inputs_);
		ar& BOOST_SERIALIZATION_NVP(start_messages_);
		ar& BOOST_SERIALIZATION_NVP(trigger_messages_);
		ar& BOOST_SERIALIZATION_NVP(clock_messages_);
		ar& BOOST_SERIALIZATION_NVP(input_values_);
		ar& BOOST_SERIALIZATION_NVP(output_values_);
		ar& BOOST_SERIALIZATION_NVP(input_conditionals_);
		ar& BOOST_SERIALIZATION_NVP(output_conditionals_);
	}

public:
	sspDomainData();
	sspDomainData(const sspDomainData&) = delete;
	sspDomainData& operator=(const sspDomainData&) = delete;
	~sspDomainData() {}

	sspDomainPool<sspValue>& getValues() { return values_; }
	sspDomainPool<sspConditional>& getConditionals() { return conditionals_; }
	sspDomainPool<sspString>& getStrings() { return strings_; }
	sspDomainPool<sspPlayer>& getPlayers() { return players_; }
	sspDomainPool<sspPlayTask>& getPlaytasks() { return tasks_; }
	sspDomainPool<sspTimeline>& getTimelines() { return timelines_; }
	sspDomainPool<sspInput>& getInputs() { return inputs_; }

	std::shared_ptr<sspConditionalMsgList> getStartList() { return start_messages_; }
	std::shared_ptr<sspTriggerMsgList> getTriggerList() { return trigger_messages_; }
	std::shared_ptr<sspTimeTriggerMsgList> getClockList() { return clock_messages_; }

	// These values and conditionals are available for input (e.g. from external inputs or from GUI)
	sspWeakVector<sspValue>& getInputValues() { return input_values_; }
	sspWeakVector<sspValue>& getOutputValues() { return output_values_; }
	sspWeakVector<sspConditional>& getInputConditionals() { return input_conditionals_; }
	sspWeakVector<sspConditional>& getOutputConditionals() { return output_conditionals_; }

	// Input values are stored as application properties
	static std::vector<double>		value_properties_s;
	void loadValuePropertiesToInputs();
	void saveValuePropertiesFromInputs();

	// Get all values of a specified type
	template <typename T>
	sspWeakVector<sspValue>			getAllPossibleValues();

	// Get all conditionals of a specified type
	template <typename T>
	sspWeakVector<sspConditional>	getAllPossibleConditionals();

	void clearContents();

	bool verify(int& nErrors, int& nWarnings) const;

	static void loadAll(const std::string& file, sspDomainData* data);
	static void saveAll(const std::string& file, sspDomainData* data);

private:
};

template<typename T>
inline sspWeakVector<sspValue> sspDomainData::getAllPossibleValues()
{
	sspWeakVector<sspValue> vals;
	for (auto value : values_) {
		if (std::dynamic_pointer_cast<T>(value)) vals.push_back(value);
	}
	return std::move(vals);
}

template<typename T>
inline sspWeakVector<sspConditional> sspDomainData::getAllPossibleConditionals()
{
	sspWeakVector<sspConditional> conds;
	for (auto cond : conditionals_) {
		if (std::dynamic_pointer_cast<T>(cond)) conds.push_back(cond);
	}
	return std::move(conds);
}
