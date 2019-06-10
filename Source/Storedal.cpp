/*
  ==============================================================================

    Storedal.cpp
    Created: 4 May 2019 12:48:32pm
    Author:  Admin

  ==============================================================================
*/

#include "Storedal.h"
#include "sspDomainData.h"
#include "sspSharedVector.h"
#include "sspPlayManager.h"

#include "sspValues.h"
#include "sspConditionals.h"
#include "sspStrings.h"
#include "sspPlayers.h"
#include "sspInputs.h"

#include "sspTimeline.h"
#include "sspAudioStream.h"

#include "sspPlayTask.h"
#include "sspConditionalMsgList.h"


void Storedal::buildContent(sspDomainData* domain, sspPlayManager* manager)
{
	if (!domain || !manager) return;

	domain->clearContents();
	manager->clearContents();

	buildBasicContent(domain);
	buildInputContent(domain);
	buildUserInputContent(domain);

	buildTimelineHierarchy(domain);

	buildKulisse(domain);
	buildRekke(domain);

	buildStartList(domain, manager);
	buildUserOutput(domain);
}

void Storedal::buildBasicContent(sspDomainData * domain)
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

void Storedal::buildInputContent(sspDomainData * domain)
{
	auto val = std::make_shared<sspBasicValue>();
	val->setName("Light value");
	val->setValue(4.0);
	domain->getValues().push_back(val);

	// Disable inputs when testing on laptop
	//auto ai = std::make_shared<sspICPanalogInput>();
	//ai->setName("Light input");
	//domain->getInputs().push_back(ai);
	//ai->setUpdateInterval(5.0);
	//ai->setPort(5);
	//ai->setChannel(0);
	//ai->setAddress(1);
	//ai->setValue(val);

	auto val_limit = std::make_shared<sspBasicValue>();
	val_limit->setName("Light limit 1");
	val_limit->setValue(0.3);
	domain->getValues().push_back(val_limit);

	auto light = std::make_shared<sspValueCompare>();
	light->setName("Minimum light");
	light->setRelationship(sspValueCompare::Relation::LargeEq);
	light->setThreshold(val_limit);
	light->setTest(val);
	domain->getConditionals().push_back(light);

	val_limit.reset(new sspBasicValue);
	val_limit->setName("Light limit 2");
	val_limit->setValue(1.5);
	domain->getValues().push_back(val_limit);

	light.reset(new sspValueCompare());
	light->setName("Medium light");
	light->setRelationship(sspValueCompare::Relation::LargeEq);
	light->setThreshold(val_limit);
	light->setTest(val);
	domain->getConditionals().push_back(light);

	val_limit.reset(new sspBasicValue);
	val_limit->setName("Light limit 3");
	val_limit->setValue(3.0);
	domain->getValues().push_back(val_limit);

	light.reset(new sspValueCompare());
	light->setName("Maximum light");
	light->setRelationship(sspValueCompare::Relation::LargeEq);
	light->setThreshold(val_limit);
	light->setTest(val);
	domain->getConditionals().push_back(light);
}

void Storedal::buildUserInputContent(sspDomainData * domain)
{
	auto range = std::make_shared<sspValueRange>();
	range->setName("Master");
	range->setValue(1.0);
	range->setValueRange(0.0, 1.0);
	domain->getValues().push_back(range);
	domain->getInputValues().push_back(range);

	range.reset(new sspValueRange);
	range->setName("Kulisse");
	range->setValue(1.0);
	range->setValueRange(0.0, 1.0);
	domain->getValues().push_back(range);
	domain->getInputValues().push_back(range);

	range.reset(new sspValueRange);
	range->setName("Noise");
	range->setValue(1.0);
	range->setValueRange(0.0, 1.0);
	domain->getValues().push_back(range);
	domain->getInputValues().push_back(range);
}

void Storedal::buildTimelineHierarchy(sspDomainData * domain)
{
	// Root timeline
	auto root = std::make_shared<sspTimeline>();
	root->setName("Root stream");
	root->setTimeFactor(domain->getValues()[1]);
	domain->getTimelines().push_back(root);

	// Kulisse audio stream
	sspWeakVector<sspValue> factors;
	factors.push_back(domain->getValues()[6]);
	factors.push_back(domain->getValues()[7]);

	auto val = std::make_shared<sspProductValue>();
	val->setName("Kulisse volume");
	val->setFactors(factors);
	domain->getValues().push_back(val);

	auto stream = std::make_shared<sspAudioStream>();
	stream->setName("Kulisse stream");
	stream->setTimeFactor(domain->getValues()[1]);
	stream->setVolumeFactor(val);
	stream->setMaxTasks(1, 0);
	domain->getTimelines().push_back(stream);

	sspWeakVector<sspTimeline> root_children;
	root_children.push_back(stream);

	// Noise audio stream
	factors[1] = domain->getValues()[8];

	val.reset(new sspProductValue);
	val->setName("Noise volume");
	val->setFactors(factors);
	domain->getValues().push_back(val);

	stream.reset(new sspAudioStream);
	stream->setName("Noise stream");
	stream->setTimeFactor(domain->getValues()[1]);
	stream->setVolumeFactor(val);
	stream->setMaxTasks(1, 1);
	domain->getTimelines().push_back(stream);

	root_children.push_back(stream);
	root->setChildren(root_children);
}

void Storedal::buildKulisse(sspDomainData * domain)
{
	// Common for all Kulisse
	auto val = std::make_shared<sspBasicValue>();
	val->setName("0.5");
	val->setValue(0.5);
	domain->getValues().push_back(val);

	auto val2 = std::make_shared<sspBasicValue>();
	val2->setName("2.5");
	val2->setValue(2.5);
	domain->getValues().push_back(val2);

	auto random = std::make_shared<sspRandomValue>();
	random->setName("Reverb kulisse");
	random->setLow(val);
	random->setHigh(val2);
	domain->getValues().push_back(random);

	auto speed = std::make_shared<sspBasicValue>();
	speed->setName("0.5");
	speed->setValue(0.5);
	domain->getValues().push_back(speed);

	sspWeakVector<sspValue> args;
	args.push_back(random);
	args.push_back(speed);

	auto addr = std::make_shared<sspSimpleString>();
	addr->setString("/play/kulisse");
	addr->setName(addr->getString());
	domain->getStrings().push_back(addr);

	// Sildring
	auto str = std::make_shared<sspSimpleString>();
	str->setString("c:/Storedal/Lyder/Kulisser/Sildring/");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	auto file = std::make_shared<sspFileString>();
	file->setName("Sildring path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	auto sildring = std::make_shared<sspOSCPlayer>();
	sildring->setName("Sildring");
	sildring->setAddress(addr);
	sildring->setPath(file);
	sildring->setArguments(args);
	domain->getPlayers().push_back(sildring);

	// Klokker
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Kulisser/Klokker/");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Klokker path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	args[1] = domain->getValues()[0];
	auto klokker = std::make_shared<sspOSCPlayer>();
	klokker->setName("Klokker");
	klokker->setAddress(addr);
	klokker->setPath(file);
	klokker->setArguments(args);
	domain->getPlayers().push_back(klokker);

	// Drypping1
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Kulisser/Drypping1/");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Drypping1 path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	args[1] = domain->getValues()[1];
	auto drypping1 = std::make_shared<sspOSCPlayer>();
	drypping1->setName("Drypping1");
	drypping1->setAddress(addr);
	drypping1->setPath(file);
	drypping1->setArguments(args);
	domain->getPlayers().push_back(drypping1);

	// Drypping2
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Kulisser/Drypping2/");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Drypping2 path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	auto drypping2 = std::make_shared<sspOSCPlayer>();
	drypping2->setName("Drypping2");
	drypping2->setAddress(addr);
	drypping2->setPath(file);
	drypping2->setArguments(args);
	domain->getPlayers().push_back(drypping2);

	// Silence
	val.reset(new sspBasicValue);
	val->setName("15");
	val->setValue(15);
	domain->getValues().push_back(val);

	auto silent = std::make_shared<sspSilencePlayer>();
	silent->setName("Kulisse silence");
	silent->setDuration(val);
	domain->getPlayers().push_back(silent);

	sspWeakVector<sspPlayer> players;
	players.push_back(sildring);
	players.push_back(klokker);
	players.push_back(drypping1);
	players.push_back(drypping2);
	players.push_back(silent);

	args.clear();
	args.push_back(domain->getValues()[2]);
	args.push_back(domain->getValues()[2]);
	args.push_back(domain->getValues()[2]);
	args.push_back(domain->getValues()[2]);
	args.push_back(domain->getValues()[0]);

	std::vector<double> const_weight{ 2, 2, 2, 2, 1 };

	auto randplay = std::make_shared<sspRandomPlayer>();
	randplay->setName("Kulisse all");
	randplay->setPlayers(players);
	randplay->setWeights(args);
	randplay->setConstantWeights(const_weight);
	domain->getPlayers().push_back(randplay);

	// Task
	auto task = std::make_shared<sspPlayTask>();
	task->setName("Kulisse");
	task->setCondition(domain->getConditionals()[1]);
	task->setVolumeFactor(domain->getValues()[1]);
	task->setPlayer(randplay);
	task->setPriority(sspPlayTask::Priority::Load);
	domain->getPlaytasks().push_back(task);

	auto msg_recv = std::make_unique<sspMessageWithReceiver>();
	sspMessage& msg = msg_recv->getMessage();
	msg.setTask(task);
	msg.setTime(domain->getValues()[0]);
	msg.setType(sspMessage::Type::Load);
	msg_recv->setReceiver(domain->getTimelines()[1]);

	auto msglist = std::make_shared<sspMessageList>();
	msglist->add(std::move(msg_recv));

	auto cond_msg = std::make_shared<sspConditionalMsgList>();
	cond_msg->add(domain->getConditionals()[0], msglist);

	task->setMessageList(sspPlayTask::Messages::Exit, cond_msg);
}

void Storedal::buildRekke(sspDomainData * domain)
{
	auto val = std::make_shared<sspBasicValue>();
	val->setName("1.5");
	val->setValue(1.5);
	domain->getValues().push_back(val);

	auto random = std::make_shared<sspRandomValue>();
	random->setName("Reverb rekke");
	random->setLow(val);
	random->setHigh(domain->getValues()[12]);
	domain->getValues().push_back(random);

	sspWeakVector<sspValue> args;
	args.push_back(random);

	auto addr = std::make_shared<sspSimpleString>();
	addr->setString("/play/rekke");
	addr->setName(addr->getString());
	domain->getStrings().push_back(addr);

	// Smalbånd
	auto str = std::make_shared<sspSimpleString>();
	str->setString("c:/Storedal/Lyder/Rekker/Smalband.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	auto file = std::make_shared<sspFileString>();
	file->setName("Smalbånd path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	auto smalband = std::make_shared<sspOSCPlayer>();
	smalband->setName("Smalbåndrekke");
	smalband->setAddress(addr);
	smalband->setPath(file);
	smalband->setArguments(args);
	domain->getPlayers().push_back(smalband);

	// Bellrekke
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Rekker/Bellrekke.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Bellrekke path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	auto bellrekke = std::make_shared<sspOSCPlayer>();
	bellrekke->setName("Bellrekke");
	bellrekke->setAddress(addr);
	bellrekke->setPath(file);
	bellrekke->setArguments(args);
	domain->getPlayers().push_back(bellrekke);

	// Bredbånd
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Rekker/Bredbandskjerne.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Bredbånd path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	args[0] = domain->getValues()[0];
	auto wideband = std::make_shared<sspOSCPlayer>();
	wideband->setName("Bredbåndsrekke");
	wideband->setAddress(addr);
	wideband->setPath(file);
	wideband->setArguments(args);
	domain->getPlayers().push_back(wideband);

	sspWeakVector<sspPlayer> players;
	players.push_back(smalband);
	players.push_back(bellrekke);
	players.push_back(wideband);

	args.clear();
	args.push_back(domain->getValues()[0]);
	args.push_back(domain->getValues()[0]);
	args.push_back(domain->getValues()[0]);

	std::vector<double> const_weight{ 1, 1, 1 };

	auto randplay = std::make_shared<sspRandomPlayer>();
	randplay->setName("Rekker all");
	randplay->setPlayers(players);
	randplay->setWeights(args);
	randplay->setConstantWeights(const_weight);
	domain->getPlayers().push_back(randplay);

	// Task
	auto task = std::make_shared<sspPlayTask>();
	task->setName("Rekker");
	task->setCondition(domain->getConditionals()[2]);
	task->setVolumeFactor(domain->getValues()[1]);
	task->setPlayer(randplay);
	task->setPriority(sspPlayTask::Priority::Load);
	domain->getPlaytasks().push_back(task);

	// Random repeat at 6 to 9 minutes
	val.reset(new sspBasicValue);
	val->setName("360");
	val->setValue(360);
	domain->getValues().push_back(val);

	auto val2 = std::make_shared<sspBasicValue>();
	val2->setName("540");
	val2->setValue(540);
	domain->getValues().push_back(val2);

	random.reset(new sspRandomValue);
	random->setName("6 to 9 minutes");
	random->setLow(val);
	random->setHigh(val2);
	domain->getValues().push_back(random);

	auto msg_recv = std::make_unique<sspMessageWithReceiver>();
	sspMessage& msg = msg_recv->getMessage();
	msg.setTask(task);
	msg.setTime(random);
	msg.setType(sspMessage::Type::Load);
	msg_recv->setReceiver(domain->getTimelines()[2]);

	auto msglist = std::make_shared<sspMessageList>();
	msglist->add(std::move(msg_recv));

	auto cond_msg = std::make_shared<sspConditionalMsgList>();
	cond_msg->add(domain->getConditionals()[0], msglist);

	task->setMessageList(sspPlayTask::Messages::Exit, cond_msg);

}

void Storedal::buildStartList(sspDomainData * domain, sspPlayManager * manager)
{
	auto msglist = std::make_shared<sspMessageList>();

	// Kulisser
	auto msg_recv = std::make_unique<sspMessageWithReceiver>();
	sspMessage& msg1 = msg_recv->getMessage();
	msg1.setTask(domain->getPlaytasks()[0]);
	msg1.setTime(domain->getValues()[0]);
	msg1.setType(sspMessage::Type::Load);
	msg_recv->setReceiver(domain->getTimelines()[1]);
	msglist->add(std::move(msg_recv));

	// Rekker
	msg_recv.reset(new sspMessageWithReceiver);
	sspMessage& msg2 = msg_recv->getMessage();
	msg2.setTask(domain->getPlaytasks()[1]);
	msg2.setTime(domain->getValues()[20]);
	msg2.setType(sspMessage::Type::Load);
	msg_recv->setReceiver(domain->getTimelines()[2]);
	msglist->add(std::move(msg_recv));

	auto cond_msg = std::make_shared<sspConditionalMsgList>();
	cond_msg->add(domain->getConditionals()[0], msglist);

	auto& startlist = manager->getStartList();
	startlist.add(domain->getConditionals()[0], msglist);
}

void Storedal::buildUserOutput(sspDomainData * domain)
{
	domain->getOutputValues().push_back(domain->getValues()[2]);
}
