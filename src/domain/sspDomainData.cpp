/*
  ==============================================================================

    sspDomainData.cpp
    Created: 4 Jan 2019 1:27:47pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspDomainData.h"

#include "domain/elements/values/sspBasicValue.h"
#include "domain/elements/values/sspValueRange.h"
#include "domain/elements/conditionals/sspBoolean.h"

#include <fstream>
#include <boost/archive/xml_oarchive.hpp> 
#include <boost/archive/xml_iarchive.hpp> 

std::vector<double> sspDomainData::value_properties_s;

sspDomainData::sspDomainData()
	: values_(), conditionals_(), strings_(), players_(), tasks_(), timelines_(), inputs_()
	, start_messages_(std::make_shared<sspConditionalMsgList>())
	, trigger_messages_(std::make_shared<sspTriggerMsgList>())
	, clock_messages_(std::make_shared<sspTimeTriggerMsgList>())
	, input_values_(), input_conditionals_(), output_values_(), output_conditionals_()
{
}

void sspDomainData::loadValuePropertiesToInputs()
{
	auto input_values = getInputValues();
	if (input_values.size() > value_properties_s.size()) {
		value_properties_s.resize(input_values.size(), 0.0);
	}

	for (int i = 0; i < input_values.size(); ++i) {
		if (auto s_ptr = std::dynamic_pointer_cast<sspValueRange>(input_values[i].lock())) {
			s_ptr->setValue(value_properties_s[i]);
		}
		else if (auto b_ptr = std::dynamic_pointer_cast<sspBasicValue>(input_values[i].lock())) {
			b_ptr->setValue(value_properties_s[i]);
		}
	}
}

void sspDomainData::saveValuePropertiesFromInputs()
{
	auto input_values = getInputValues();
	if (input_values.size() > value_properties_s.size()) {
		value_properties_s.resize(input_values.size(), 0.0);
	}

	for (int i = 0; i < input_values.size(); ++i) {
		if (auto ptr = input_values[i].lock()) {
			value_properties_s[i] = ptr->getValue();
		}
	}
}

void sspDomainData::clearContents()
{
	values_.clear();
	conditionals_.clear();
	strings_.clear();
	players_.clear();
	tasks_.clear();
	timelines_.clear();
	inputs_.clear();

	start_messages_->removeAll();
	trigger_messages_->removeAll();
	clock_messages_->removeAll();

	input_values_.clear();
	input_conditionals_.clear();
}

bool sspDomainData::verify(int& nErrors, int& nWarnings) const
{
	bool bReturn = true;

	if (!values_.verify(nErrors, nWarnings)) bReturn = false;
	if (!conditionals_.verify(nErrors, nWarnings)) bReturn = false;
	if (!strings_.verify(nErrors, nWarnings)) bReturn = false;
	if (!players_.verify(nErrors, nWarnings)) bReturn = false;
	if (!tasks_.verify(nErrors, nWarnings)) bReturn = false;
	if (!timelines_.verify(nErrors, nWarnings)) bReturn = false;
	if (!inputs_.verify(nErrors, nWarnings)) bReturn = false;

	if (!start_messages_->verify(nErrors, nWarnings)) bReturn = false;
	if (!trigger_messages_->verify(nErrors, nWarnings)) bReturn = false;
	if (!clock_messages_->verify(nErrors, nWarnings)) bReturn = false;

	return bReturn;
}

void sspDomainData::loadAll(const std::string& file, sspDomainData* data)
{
	std::ifstream is(file);
	boost::archive::xml_iarchive ia(is);
	data->clearContents();
	ia >> boost::serialization::make_nvp("sspDomainData",*data);
	data->loadValuePropertiesToInputs();
}

void sspDomainData::saveAll(const std::string& file, sspDomainData* data)
{
	std::ofstream os(file);
	boost::archive::xml_oarchive oa(os);
	oa << boost::serialization::make_nvp("sspDomainData", *data);
}
