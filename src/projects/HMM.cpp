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

//#define BUILD_HMM_TEST 1

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
	stream->setMaxTasks(1, 1);
	domain->getTimelines().push_back(stream);

	sspWeakVector<sspTimeline> root_children;
	root_children.push_back(stream);
	root->setChildren(root_children);
}

void HMM::buildPlayer(sspDomainData* domain)
{

#ifdef BUILD_HMM_TEST

	auto midi_path_str = std::make_shared<sspSimpleString>();
	midi_path_str->setString(file_root + "Test/");
	midi_path_str->setName(midi_path_str->getString());
	domain->getStrings().push_back(midi_path_str);

#else

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

	auto midi_path_str = std::make_shared<sspConditionalString>();
	midi_path_str->setName("Dag eller kveld");
	midi_path_str->setConditionals(conds);
	midi_path_str->setStrings(folder_strings);
	midi_path_str->setDefaultString(evening_folder);
	domain->getStrings().push_back(midi_path_str);

#endif

	auto file = std::make_shared<sspFileString>();
	file->setName("Midi path");
	file->setPath(midi_path_str);
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

#ifdef BUILD_HMM_TEST

	// Play on average every second hour
	auto play_interval = std::make_shared<sspBasicValue>();
	play_interval->setName("10 seconds");
	play_interval->setValue(10);
	domain->getValues().push_back(play_interval);

#else

	// Play on average every second hour
	auto val_hour = std::make_shared<sspBasicValue>();
	val_hour->setName("1 hour");
	val_hour->setValue(3600);
	domain->getValues().push_back(val_hour);

	auto val_3hour = std::make_shared<sspBasicValue>();
	val_3hour->setName("3 hours");
	val_3hour->setValue(10800);
	domain->getValues().push_back(val_3hour);

	auto play_interval = std::make_shared<sspRandomValue>();
	play_interval->setName("1 to 3 hours");
	play_interval->setLow(val_hour);
	play_interval->setHigh(val_3hour);
	domain->getValues().push_back(play_interval);

#endif

	// Add recurring load event 
	auto msg_recv = std::make_unique<sspMessageWithReceiver>();
	sspMessage& msg = msg_recv->getMessage();
	msg.setTask(task);
	msg.setTime(play_interval);
	msg.setType(sspMessage::Type::Load);
	msg_recv->setReceiver(domain->getTimelines()[1]);

	auto msglist = std::make_shared<sspMessageList>();
	msglist->add(std::move(msg_recv));

	auto cond_msg = std::make_shared<sspConditionalMsgList>();
	cond_msg->add(domain->getConditionals()[0], msglist);

#ifdef BUILD_HMM_TEST

	task->setMessageList(sspPlayTask::Messages::Exit, cond_msg);

#else

	task->setMessageList(sspPlayTask::Messages::Enter, cond_msg);

#endif
}

void HMM::buildStartList(sspDomainData* domain)
{
	// Start after 10 seconds
	auto val_10 = std::make_shared<sspBasicValue>();
	val_10->setName("10 seconds");
	val_10->setValue(10);
	domain->getValues().push_back(val_10);

	auto msglist = std::make_shared<sspMessageList>();

	auto msg_recv = std::make_unique<sspMessageWithReceiver>();
	sspMessage& msg = msg_recv->getMessage();
	msg.setTask(domain->getPlaytasks()[0]);
	msg.setTime(val_10);
	msg.setType(sspMessage::Type::Load);
	msg_recv->setReceiver(domain->getTimelines()[1]);
	msglist->add(std::move(msg_recv));

	auto startlist = domain->getStartList();
	startlist->add(domain->getConditionals()[0], msglist);
}
