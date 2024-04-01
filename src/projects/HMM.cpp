/*
  ==============================================================================

	HMM.h
	Created: 23 Nov 2023
	Author:  Sigurd Saue

  ==============================================================================
*/

#include "HMM.h"

#include "domain/sspDomainData.h"
#include "domain/elements/streams/sspStream.h"
#include "domain/core/sspSharedVector.h"

#include "domain/elements/values/sspValues.h"
#include "domain/elements/conditionals/sspConditionals.h"
#include "domain/elements/strings/sspStrings.h"
#include "domain/elements/players/sspPlayers.h"

#include "domain/core/sspPlayTask.h"
#include "domain/elements/messages/sspConditionalMsgList.h"

namespace {
	std::string file_root = "C:/HMM/MIDI/";
}

void HMM::buildContent(sspDomainData* domain)
{
	if (!domain) return;

	domain->clearContents();

	buildBasicContent(domain);
	buildTimelineHierarchy(domain);
	buildPlayer(domain);
	buildStartList(domain);
}

void HMM::buildBasicContent(sspDomainData* domain)
{
	auto bool_true = std::make_shared<sspBoolean>();
	bool_true->setName("true");
	bool_true->setValue(true);
	domain->getConditionals().push_back(bool_true);

	auto val = std::make_shared<sspBasicValue>();
	val->setName("0.0");
	val->setValue(0.0);
	domain->getValues().push_back(val);

	val.reset(new sspBasicValue());
	val->setName("1.0");
	val->setValue(1.0);
	domain->getValues().push_back(val);
}

void HMM::buildTimelineHierarchy(sspDomainData* domain)
{
	// Root timeline
	auto root = std::make_shared<sspTimeline>();
	root->setName("Root stream");
	root->setTimeFactor(domain->getValues()[1]);
	domain->getTimelines().push_back(root);

	// MIDI stream
	auto stream = std::make_shared<sspStream>();
	stream->setName("MIDI stream");
	stream->setTimeFactor(domain->getValues()[1]);
	domain->getTimelines().push_back(stream);

	sspWeakVector<sspTimeline> root_children;
	root_children.push_back(stream);
	root->setChildren(root_children);
}

void HMM::buildPlayer(sspDomainData* domain)
{
	// Conditionals
	auto time_of_day = std::make_shared<sspTimeCompare>();
	time_of_day->setName("Before 16:00");
	time_of_day->setClock(boost::posix_time::time_duration(16, 0, 0));
	time_of_day->setRelationship(sspTimeCompare::Relation::Before);
	domain->getConditionals().push_back(time_of_day);

	// Strings
	auto day_folder = std::make_shared<sspSimpleString>();
	day_folder->setString(file_root + "Dag/");
	day_folder->setName(day_folder->getString());
	domain->getStrings().push_back(day_folder);

	auto evening_folder = std::make_shared<sspSimpleString>();
	evening_folder->setString(file_root + "Kveld/");
	evening_folder->setName(evening_folder->getString());
	domain->getStrings().push_back(evening_folder);

	sspWeakVector<sspString> folder_strings;
	folder_strings.push_back(day_folder);

	sspWeakVector<sspConditional> conds;
	conds.push_back(time_of_day);

	auto cond_str = std::make_shared<sspConditionalString>();
	cond_str->setName("Dag eller kveld");
	cond_str->setConditionals(conds);
	cond_str->setStrings(folder_strings);
	cond_str->setDefaultString(evening_folder);
	domain->getStrings().push_back(cond_str);

	auto file = std::make_shared<sspFileString>();
	file->setName("Midi path");
	file->setPath(cond_str);
	file->setAudioOnly(false);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	auto midi_player = std::make_shared<sspMidiPlayer>();
	midi_player->setName("Spill dag/kveld");
	midi_player->setFilepath(file);
	midi_player->setTempoFactor(domain->getValues()[1]);
	domain->getPlayers().push_back(midi_player);

	// Task
	auto task = std::make_shared<sspPlayTask>();
	task->setName("Spill HMM");
	task->setCondition(domain->getConditionals()[0]);
	task->setVolumeFactor(domain->getValues()[1]);
	task->setPlayer(midi_player);
	task->setPriority(sspPlayTask::Priority::Cancel);
	domain->getPlaytasks().push_back(task);
}

void HMM::buildStartList(sspDomainData* domain)
{
	// Is this a weekday or a weekend?
	auto weekdays = std::make_shared<sspDayOfWeek>();
	weekdays->setName("Weekdays");
	std::vector<boost::date_time::weekdays> days{ boost::date_time::Monday, 
		boost::date_time::Tuesday ,boost::date_time::Wednesday ,boost::date_time::Thursday ,boost::date_time::Friday };
	weekdays->setDays(days);
	domain->getConditionals().push_back(weekdays);

	auto weekend = std::make_shared<sspNot>();
	weekend->setName("Weekend");
	weekend->setOperand(weekdays);
	domain->getConditionals().push_back(weekend);

	//Define allowed weekday time interval
	auto weekday_interval = std::make_shared<sspTimeInterval>();
	weekday_interval->setName("Weekday interval");
	weekday_interval->setInputRange(boost::posix_time::time_duration(6, 30, 0), boost::posix_time::time_duration(21, 30, 0));
	domain->getConditionals().push_back(weekday_interval);

	sspWeakVector<sspConditional> conds;
	conds.push_back(weekdays);
	conds.push_back(weekday_interval);

	auto allow_weekdays = std::make_shared<sspAnd>();
	allow_weekdays->setName("Allowed to play weekdays");
	allow_weekdays->setOperands(conds);
	domain->getConditionals().push_back(allow_weekdays);

	//Define allowed weekend time interval
	auto weekend_interval = std::make_shared<sspTimeInterval>();
	weekend_interval->setName("Weekend interval");
	weekend_interval->setInputRange(boost::posix_time::time_duration(9, 30, 0), boost::posix_time::time_duration(21, 30, 0));
	domain->getConditionals().push_back(weekend_interval);

	conds.clear();
	conds.push_back(weekend);
	conds.push_back(weekend_interval);

	auto allow_weekend = std::make_shared<sspAnd>();
	allow_weekend->setName("Allowed to play weekend");
	allow_weekend->setOperands(conds);
	domain->getConditionals().push_back(allow_weekend);

	// Start playing in a random 4 minute interval around the full hour
	auto val_min4 = std::make_shared<sspBasicValue>();
	val_min4->setName("4 minutes");
	val_min4->setValue(240);
	domain->getValues().push_back(val_min4);

	auto random = std::make_shared<sspRandomValue>();
	random->setName("0 to 4 minutes");
	random->setLow(domain->getValues()[0]);
	random->setHigh(val_min4);
	domain->getValues().push_back(random);

	auto minute_cond = std::make_shared<sspMinuteCompare>();
	minute_cond->setName(":58");
	minute_cond->setMinutes(58);
	minute_cond->setRelationship(sspMinuteCompare::Relation::Equal);
	domain->getConditionals().push_back(minute_cond);

	// Define trigger that triggers an event at :58 each hour
	auto trigger = std::make_shared<sspTrigger>();
	trigger->setName("Trigger around the hour");
	trigger->setConditional(minute_cond);
	trigger->setChange(sspTrigger::Trigger::True);
	domain->getConditionals().push_back(trigger);

	// Conditional message list
	auto msglist = std::make_shared<sspMessageList>();
	auto msg_recv = std::make_unique<sspMessageWithReceiver>();
	sspMessage& msg1 = msg_recv->getMessage();
	msg1.setTask(domain->getPlaytasks()[0]);
	msg1.setTime(random);
	msg1.setType(sspMessage::Type::Load);
	msg_recv->setReceiver(domain->getTimelines()[1]);
	msglist->add(std::move(msg_recv));

	auto condlist = std::make_shared<sspConditionalMsgList>();
	condlist->add(allow_weekdays, msglist);
	condlist->add(allow_weekend, msglist);

	// Triggered message list
	auto triggerlist = domain->getTriggerList();
	triggerlist->add(trigger, condlist);
}
