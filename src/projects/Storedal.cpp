/*
  ==============================================================================

    Storedal.cpp
    Created: 4 May 2019 12:48:32pm
    Author:  Admin

  ==============================================================================
*/

#include "Storedal.h"

#include "domain/sspDomainData.h"
#include "domain/core/sspTimeline.h"
#include "domain/core/sspSharedVector.h"

#include "domain/elements/values/sspValues.h"
#include "domain/elements/conditionals/sspConditionals.h"
#include "domain/elements/strings/sspStrings.h"
#include "domain/elements/players/sspPlayers.h"
#include "domain/elements/inputs/sspInputs.h"

#include "domain/elements/streams/sspAudioStream.h"

#include "domain/core/sspPlayTask.h"
#include "domain/elements/messages/sspConditionalMsgList.h"


void Storedal::buildContent(sspDomainData* domain)
{
	if (!domain) return;

	domain->clearContents();

	buildBasicContent(domain);
	buildInputContent(domain);
	buildUserInputContent(domain);

	buildTimelineHierarchy(domain);

	buildKulisse(domain);
	buildRekke(domain);
	buildSignaler(domain);
	buildAttakker(domain);
	buildRens(domain);
	buildDunder(domain);

	buildStartList(domain);
	buildTriggerList(domain);
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

	range.reset(new sspValueRange);
	range->setName("Signal");
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
	stream->setMaxTasks(1, 1);
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
	stream->setMaxTasks(2, 1);
	domain->getTimelines().push_back(stream);

	root_children.push_back(stream);

	// Signal audio stream
	factors[1] = domain->getValues()[9];

	val.reset(new sspProductValue);
	val->setName("Signal volume");
	val->setFactors(factors);
	domain->getValues().push_back(val);

	stream.reset(new sspAudioStream);
	stream->setName("Signal stream");
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
	task->setPriority(sspPlayTask::Priority::Wait);
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
	random->setHigh(domain->getValues()[14]);
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

void Storedal::buildSignaler(sspDomainData * domain)
{
	sspWeakVector<sspValue> args;
	args.push_back(domain->getValues()[19]);	// Reuse reverb rekke

	sspWeakVector<sspPlayer> players;

	auto addr = std::make_shared<sspSimpleString>();
	addr->setString("/play/signaler");
	addr->setName(addr->getString());
	domain->getStrings().push_back(addr);

	// Jegerpling1
	auto str = std::make_shared<sspSimpleString>();
	str->setString("c:/Storedal/Lyder/Signaler/Jegerpling1.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	auto file = std::make_shared<sspFileString>();
	file->setName("Jegerpling1 path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	auto signal = std::make_shared<sspOSCPlayer>();
	signal->setName("Jegerpling1");
	signal->setAddress(addr);
	signal->setPath(file);
	signal->setArguments(args);
	domain->getPlayers().push_back(signal);
	players.push_back(signal);

	// Jegerpling2
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Signaler/Jegerpling2.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Jegerpling2 path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	signal.reset(new sspOSCPlayer);
	signal->setName("Jegerpling2");
	signal->setAddress(addr);
	signal->setPath(file);
	signal->setArguments(args);
	domain->getPlayers().push_back(signal);
	players.push_back(signal);

	// Jegerpling3
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Signaler/Jegerpling3.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Jegerpling3 path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	signal.reset(new sspOSCPlayer);
	signal->setName("Jegerpling3");
	signal->setAddress(addr);
	signal->setPath(file);
	signal->setArguments(args);
	domain->getPlayers().push_back(signal);
	players.push_back(signal);

	// Hardkort1
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Signaler/Hardkort1.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Hardkort1 path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	signal.reset(new sspOSCPlayer);
	signal->setName("Hardkort1");
	signal->setAddress(addr);
	signal->setPath(file);
	signal->setArguments(args);
	domain->getPlayers().push_back(signal);
	players.push_back(signal);

	// Hardkort2
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Signaler/Hardkort2.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Hardkort2 path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	signal.reset(new sspOSCPlayer);
	signal->setName("Hardkort2");
	signal->setAddress(addr);
	signal->setPath(file);
	signal->setArguments(args);
	domain->getPlayers().push_back(signal);
	players.push_back(signal);

	// Hardkort3
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Signaler/Hardkort3.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Hardkort3 path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	signal.reset(new sspOSCPlayer);
	signal->setName("Hardkort3");
	signal->setAddress(addr);
	signal->setPath(file);
	signal->setArguments(args);
	domain->getPlayers().push_back(signal);
	players.push_back(signal);

	// Klokkesignal1
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Signaler/Klokkesignal1.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Klokkesignal1 path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	signal.reset(new sspOSCPlayer);
	signal->setName("Klokkesignal1");
	signal->setAddress(addr);
	signal->setPath(file);
	signal->setArguments(args);
	domain->getPlayers().push_back(signal);
	players.push_back(signal);

	// Klokkesignal2
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Signaler/Klokkesignal2.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Klokkesignal2 path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	signal.reset(new sspOSCPlayer);
	signal->setName("Klokkesignal2");
	signal->setAddress(addr);
	signal->setPath(file);
	signal->setArguments(args);
	domain->getPlayers().push_back(signal);
	players.push_back(signal);

	// Klokkesignal3
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Signaler/Klokkesignal3.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Klokkesignal3 path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	signal.reset(new sspOSCPlayer);
	signal->setName("Klokkesignal3");
	signal->setAddress(addr);
	signal->setPath(file);
	signal->setArguments(args);
	domain->getPlayers().push_back(signal);
	players.push_back(signal);

	// Chainplayer
	auto chain = std::make_shared<sspChainPlayer>();
	chain->setName("Signalkjede");
	chain->setPlayers(players);
	chain->setChainHop(3);
	chain->setChainLength(3);
	domain->getPlayers().push_back(chain);

	// Distributionplayer
	auto low = std::make_shared<sspBasicValue>();
	low->setName("3.0");
	low->setValue(3.0);
	domain->getValues().push_back(low);

	auto high = std::make_shared<sspBasicValue>();
	high->setName("5.0");
	high->setValue(5.0);
	domain->getValues().push_back(high);

	auto random = std::make_shared<sspRandomValue>();
	random->setName("3 to 5 seconds");
	random->setLow(low);
	random->setHigh(high);
	domain->getValues().push_back(random);

	auto distro = std::make_shared<sspDistributionPlayer>();
	distro->setName("Signaler");
	distro->setPlayer(chain);
	distro->setCondition(domain->getConditionals()[2]);
	distro->setStartTime(random);
	distro->setDuration(low);
	distro->setLoopMode(sspDistributionPlayer::LoopMode::Count);
	domain->getPlayers().push_back(distro);

	// Task
	auto task = std::make_shared<sspPlayTask>();
	task->setName("Signaler");
	task->setCondition(domain->getConditionals()[2]);
	task->setVolumeFactor(domain->getValues()[1]);
	task->setPlayer(distro);
	task->setPriority(sspPlayTask::Priority::Load);
	domain->getPlaytasks().push_back(task);

	auto msg_recv = std::make_unique<sspMessageWithReceiver>();
	sspMessage& msg = msg_recv->getMessage();
	msg.setTask(task);
	msg.setTime(domain->getValues()[22]);
	msg.setType(sspMessage::Type::Load);
	msg_recv->setReceiver(domain->getTimelines()[3]);

	auto msglist = std::make_shared<sspMessageList>();
	msglist->add(std::move(msg_recv));

	auto cond_msg = std::make_shared<sspConditionalMsgList>();
	cond_msg->add(domain->getConditionals()[0], msglist);

	task->setMessageList(sspPlayTask::Messages::Enter, cond_msg);
}

void Storedal::buildAttakker(sspDomainData * domain)
{
	sspWeakVector<sspPlayer> players;
	players.push_back(domain->getPlayers()[4]);	// 15 seconds silence

	auto random = std::make_shared<sspRandomValue>();
	random->setName("Reverb attakk");
	random->setLow(domain->getValues()[16]);
	random->setHigh(domain->getValues()[18]);
	domain->getValues().push_back(random);

	sspWeakVector<sspValue> args;
	args.push_back(random);

	auto addr = std::make_shared<sspSimpleString>();
	addr->setString("/play/attakker");
	addr->setName(addr->getString());
	domain->getStrings().push_back(addr);

	// Metallstuff
	auto str = std::make_shared<sspSimpleString>();
	str->setString("c:/Storedal/Lyder/Attakker/Metallstuff/");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	auto file = std::make_shared<sspFileString>();
	file->setName("Metallstuff path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	auto stuff = std::make_shared<sspOSCPlayer>();
	stuff->setName("Metallstuff");
	stuff->setAddress(addr);
	stuff->setPath(file);
	stuff->setArguments(args);
	domain->getPlayers().push_back(stuff);

	// The rest
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Attakker/");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Attakker path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	args[0] = domain->getValues()[13];	// Very little reverb on the rest
	auto attakk = std::make_shared<sspOSCPlayer>();
	attakk->setName("Attakk");
	attakk->setAddress(addr);
	attakk->setPath(file);
	attakk->setArguments(args);
	domain->getPlayers().push_back(attakk);

	// Random select attakker
	sspWeakVector<sspPlayer> attakker;
	attakker.push_back(attakk);
	attakker.push_back(stuff);

	args.clear();
	args.push_back(domain->getValues()[0]);
	args.push_back(domain->getValues()[0]);

	std::vector<double> const_weight{ 2, 1 };

	auto randplay = std::make_shared<sspRandomPlayer>();
	randplay->setName("Attakker");
	randplay->setPlayers(attakker);
	randplay->setWeights(args);
	randplay->setConstantWeights(const_weight);
	domain->getPlayers().push_back(randplay);

	players.push_back(randplay);
	players.push_back(domain->getPlayers()[4]);	// 15 seconds silence

	// Kaskader (always follow attakker)
	sspWeakVector<sspPlayer> kaskader;

	args.clear();
	args.push_back(domain->getValues()[19]);
	
	addr.reset(new sspSimpleString);
	addr->setString("/play/kaskader");
	addr->setName(addr->getString());
	domain->getStrings().push_back(addr);

	// Kaskade01
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Kaskader/Kaskade01.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Kaskade01 path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	auto kaskade = std::make_shared<sspOSCPlayer>();
	kaskade->setName("Kaskade01");
	kaskade->setAddress(addr);
	kaskade->setPath(file);
	kaskade->setArguments(args);
	domain->getPlayers().push_back(kaskade);
	kaskader.push_back(kaskade);

	// Kaskade02
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Kaskader/Kaskade02.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Kaskade02 path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	kaskade.reset(new sspOSCPlayer);
	kaskade->setName("Kaskade02");
	kaskade->setAddress(addr);
	kaskade->setPath(file);
	kaskade->setArguments(args);
	domain->getPlayers().push_back(kaskade);
	kaskader.push_back(kaskade);

	// Kaskade03
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Kaskader/Kaskade03.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Kaskade03 path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	kaskade.reset(new sspOSCPlayer);
	kaskade->setName("Kaskade03");
	kaskade->setAddress(addr);
	kaskade->setPath(file);
	kaskade->setArguments(args);
	domain->getPlayers().push_back(kaskade);
	kaskader.push_back(kaskade);

	// Kaskade04
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Kaskader/Kaskade04.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Kaskade04 path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	kaskade.reset(new sspOSCPlayer);
	kaskade->setName("Kaskade04");
	kaskade->setAddress(addr);
	kaskade->setPath(file);
	kaskade->setArguments(args);
	domain->getPlayers().push_back(kaskade);
	kaskader.push_back(kaskade);

	// Kaskade05
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Kaskader/Kaskade05.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Kaskade05 path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	kaskade.reset(new sspOSCPlayer);
	kaskade->setName("Kaskade05");
	kaskade->setAddress(addr);
	kaskade->setPath(file);
	kaskade->setArguments(args);
	domain->getPlayers().push_back(kaskade);
	kaskader.push_back(kaskade);

	// Kaskade06
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Kaskader/Kaskade06.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Kaskade06 path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	kaskade.reset(new sspOSCPlayer);
	kaskade->setName("Kaskade06");
	kaskade->setAddress(addr);
	kaskade->setPath(file);
	kaskade->setArguments(args);
	domain->getPlayers().push_back(kaskade);
	kaskader.push_back(kaskade);

	// Kaskade07
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Kaskader/Kaskade07.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Kaskade07 path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	kaskade.reset(new sspOSCPlayer);
	kaskade->setName("Kaskade07");
	kaskade->setAddress(addr);
	kaskade->setPath(file);
	kaskade->setArguments(args);
	domain->getPlayers().push_back(kaskade);
	kaskader.push_back(kaskade);

	// Kaskade08
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Kaskader/Kaskade08.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Kaskade08 path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	kaskade.reset(new sspOSCPlayer);
	kaskade->setName("Kaskade08");
	kaskade->setAddress(addr);
	kaskade->setPath(file);
	kaskade->setArguments(args);
	domain->getPlayers().push_back(kaskade);
	kaskader.push_back(kaskade);

	// Kaskade09
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Kaskader/Kaskade09.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Kaskade09 path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	kaskade.reset(new sspOSCPlayer);
	kaskade->setName("Kaskade09");
	kaskade->setAddress(addr);
	kaskade->setPath(file);
	kaskade->setArguments(args);
	domain->getPlayers().push_back(kaskade);
	kaskader.push_back(kaskade);

	// Kaskade10
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Kaskader/Kaskade10.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Kaskade10 path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	kaskade.reset(new sspOSCPlayer);
	kaskade->setName("Kaskade10");
	kaskade->setAddress(addr);
	kaskade->setPath(file);
	kaskade->setArguments(args);
	domain->getPlayers().push_back(kaskade);
	kaskader.push_back(kaskade);

	// Kaskade11
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Kaskader/Kaskade11.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Kaskade11 path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	kaskade.reset(new sspOSCPlayer);
	kaskade->setName("Kaskade11");
	kaskade->setAddress(addr);
	kaskade->setPath(file);
	kaskade->setArguments(args);
	domain->getPlayers().push_back(kaskade);
	kaskader.push_back(kaskade);

	// Kaskade12
	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Kaskader/Kaskade12.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Kaskade12 path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	kaskade.reset(new sspOSCPlayer);
	kaskade->setName("Kaskade12");
	kaskade->setAddress(addr);
	kaskade->setPath(file);
	kaskade->setArguments(args);
	domain->getPlayers().push_back(kaskade);
	kaskader.push_back(kaskade);	

	// Chainplayer
	auto chain = std::make_shared<sspChainPlayer>();
	chain->setName("Kaskade chain");
	chain->setPlayers(kaskader);
	chain->setChainHop(2);
	chain->setChainLength(3);
	domain->getPlayers().push_back(chain);

	// Distributionplayer
	auto interval = std::make_shared<sspRandomValue>();
	interval->setName("1 to 3 seconds");
	interval->setLow(domain->getValues()[1]);
	interval->setHigh(domain->getValues()[23]);
	domain->getValues().push_back(interval);

	auto distro = std::make_shared<sspDistributionPlayer>();
	distro->setName("Kaskade distro");
	distro->setPlayer(chain);
	distro->setCondition(domain->getConditionals()[3]);
	distro->setStartTime(interval);
	distro->setDuration(domain->getValues()[23]);
	distro->setLoopMode(sspDistributionPlayer::LoopMode::Count);
	domain->getPlayers().push_back(distro);

	players.push_back(distro);

	// Kulisse bend
	args[0] = domain->getValues()[15];
	args.push_back(domain->getValues()[13]);

	addr.reset(new sspSimpleString);
	addr->setString("/play/kulisse");
	addr->setName(addr->getString());
	domain->getStrings().push_back(addr);

	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/Kulisser/Bend/");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("Kulissebend path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	auto bend = std::make_shared<sspOSCPlayer>();
	bend->setName("Kulissebend");
	bend->setAddress(addr);
	bend->setPath(file);
	bend->setArguments(args);
	domain->getPlayers().push_back(bend);
	players.push_back(bend);

	auto all = std::make_shared<sspSequentialPlayer>();
	all->setName("Attakk komplett");
	all->setPlayers(players);
	domain->getPlayers().push_back(all);

	// Task
	auto task = std::make_shared<sspPlayTask>();
	task->setName("Attakker");
	task->setCondition(domain->getConditionals()[3]);
	task->setVolumeFactor(domain->getValues()[1]);
	task->setPlayer(all);
	task->setPriority(sspPlayTask::Priority::Load);
	domain->getPlaytasks().push_back(task);

	// Message at Exit
	auto msg_recv = std::make_unique<sspMessageWithReceiver>();
	sspMessage& msg = msg_recv->getMessage();
	msg.setTask(task);
	msg.setTime(domain->getValues()[22]);
	msg.setType(sspMessage::Type::Load);
	msg_recv->setReceiver(domain->getTimelines()[2]);

	auto msglist = std::make_shared<sspMessageList>();
	msglist->add(std::move(msg_recv));

	auto cond_msg = std::make_shared<sspConditionalMsgList>();
	cond_msg->add(domain->getConditionals()[0], msglist);

	task->setMessageList(sspPlayTask::Messages::Exit, cond_msg);

	// Message at Start
	msg_recv = std::make_unique<sspMessageWithReceiver>();
	sspMessage& msg2 = msg_recv->getMessage();
	msg2.setTask(task);
	msg2.setTime(domain->getValues()[24]);
	msg2.setType(sspMessage::Type::Solo);
	msg_recv->setReceiver(domain->getTimelines()[2]);

	msglist.reset(new sspMessageList);
	msglist->add(std::move(msg_recv));

	msg_recv = std::make_unique<sspMessageWithReceiver>();
	sspMessage& msg3 = msg_recv->getMessage();
	msg3.setType(sspMessage::Type::MuteOnSolo);
	msg3.setTime(domain->getValues()[18]);
	msg_recv->setReceiver(domain->getTimelines()[0]);

	msglist->add(std::move(msg_recv));

	cond_msg.reset(new sspConditionalMsgList);
	cond_msg->add(domain->getConditionals()[0], msglist);

	task->setMessageList(sspPlayTask::Messages::Start, cond_msg);

	// Message at End
	msg_recv = std::make_unique<sspMessageWithReceiver>();
	sspMessage& msg5 = msg_recv->getMessage();
	msg5.setType(sspMessage::Type::UnmuteOnSolo);
	msg5.setTime(domain->getValues()[18]);
	msg_recv->setReceiver(domain->getTimelines()[0]);

	msglist.reset(new sspMessageList);
	msglist->add(std::move(msg_recv));

	msg_recv = std::make_unique<sspMessageWithReceiver>();
	sspMessage& msg4 = msg_recv->getMessage();
	msg4.setTask(task);
	msg4.setTime(domain->getValues()[18]);
	msg4.setType(sspMessage::Type::Unsolo);
	msg_recv->setReceiver(domain->getTimelines()[2]);

	msglist->add(std::move(msg_recv));

	cond_msg.reset(new sspConditionalMsgList);
	cond_msg->add(domain->getConditionals()[0], msglist);

	task->setMessageList(sspPlayTask::Messages::End, cond_msg);
}

void Storedal::buildRens(sspDomainData * domain)
{
	sspWeakVector<sspValue> args;
	args.push_back(domain->getValues()[15]);

	auto addr = std::make_shared<sspSimpleString>();
	addr->setString("/play/rens");
	addr->setName(addr->getString());
	domain->getStrings().push_back(addr);

	auto str = std::make_shared<sspSimpleString>();
	str->setString("c:/Storedal/Lyder/Sildrerens.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	auto file = std::make_shared<sspFileString>();
	file->setName("Rens path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	auto rens = std::make_shared<sspOSCPlayer>();
	rens->setName("Sildrerens");
	rens->setAddress(addr);
	rens->setPath(file);
	rens->setArguments(args);
	domain->getPlayers().push_back(rens);

	// Task
	auto task = std::make_shared<sspPlayTask>();
	task->setName("Rens");
	task->setCondition(domain->getConditionals()[1]);
	task->setVolumeFactor(domain->getValues()[1]);
	task->setPlayer(rens);
	task->setPriority(sspPlayTask::Priority::LoadAlways);
	domain->getPlaytasks().push_back(task);

	// Message at Start
	auto msg_recv = std::make_unique<sspMessageWithReceiver>();
	sspMessage& msg2 = msg_recv->getMessage();
	msg2.setTask(task);
	msg2.setTime(domain->getValues()[24]);
	msg2.setType(sspMessage::Type::Solo);
	msg_recv->setReceiver(domain->getTimelines()[1]);

	auto msglist = std::make_shared<sspMessageList>();
	msglist->add(std::move(msg_recv));

	msg_recv = std::make_unique<sspMessageWithReceiver>();
	sspMessage& msg3 = msg_recv->getMessage();
	msg3.setTime(domain->getValues()[18]);
	msg3.setType(sspMessage::Type::MuteOnSolo);
	msg_recv->setReceiver(domain->getTimelines()[0]);

	msglist->add(std::move(msg_recv));

	auto cond_msg = std::make_shared<sspConditionalMsgList>();
	cond_msg->add(domain->getConditionals()[0], msglist);

	task->setMessageList(sspPlayTask::Messages::Start, cond_msg);

	// Message at End
	msg_recv = std::make_unique<sspMessageWithReceiver>();
	sspMessage& msg5 = msg_recv->getMessage();
	msg5.setTime(domain->getValues()[18]);
	msg5.setType(sspMessage::Type::UnmuteOnSolo);
	msg_recv->setReceiver(domain->getTimelines()[0]);

	msglist.reset(new sspMessageList);
	msglist->add(std::move(msg_recv));

	msg_recv = std::make_unique<sspMessageWithReceiver>();
	sspMessage& msg4 = msg_recv->getMessage();
	msg4.setTask(task);
	msg4.setTime(domain->getValues()[18]);
	msg4.setType(sspMessage::Type::Unsolo);
	msg_recv->setReceiver(domain->getTimelines()[1]);

	msglist->add(std::move(msg_recv));

	cond_msg.reset(new sspConditionalMsgList);
	cond_msg->add(domain->getConditionals()[0], msglist);

	task->setMessageList(sspPlayTask::Messages::End, cond_msg);
}

void Storedal::buildDunder(sspDomainData * domain)
{
	sspWeakVector<sspValue> args;
	args.push_back(domain->getValues()[15]);

	auto addr = std::make_shared<sspSimpleString>();
	addr->setString("/play/dunder");
	addr->setName(addr->getString());
	domain->getStrings().push_back(addr);

	auto str = std::make_shared<sspSimpleString>();
	str->setString("c:/Storedal/Lyder/DunderKort.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	auto file = std::make_shared<sspFileString>();
	file->setName("DunderKort path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	auto kort = std::make_shared<sspOSCPlayer>();
	kort->setName("DunderKort");
	kort->setAddress(addr);
	kort->setPath(file);
	kort->setArguments(args);
	domain->getPlayers().push_back(kort);

	str.reset(new sspSimpleString);
	str->setString("c:/Storedal/Lyder/DunderLang.wav");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	file.reset(new sspFileString);
	file->setName("DunderLang path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	auto lang = std::make_shared<sspOSCPlayer>();
	lang->setName("DunderLang");
	lang->setAddress(addr);
	lang->setPath(file);
	lang->setArguments(args);
	domain->getPlayers().push_back(lang);

	sspWeakVector<sspPlayer> players;
	players.push_back(kort);
	players.push_back(lang);

	args.clear();
	args.push_back(domain->getValues()[0]);
	args.push_back(domain->getValues()[2]);

	std::vector<double> const_weight{ 3, 1 };

	auto randplay = std::make_shared<sspRandomPlayer>();
	randplay->setName("Dunder lys");
	randplay->setPlayers(players);
	randplay->setWeights(args);
	randplay->setConstantWeights(const_weight);
	domain->getPlayers().push_back(randplay);

	players.clear();
	players.push_back(randplay);

	sspWeakVector<sspConditional> conds;
	conds.push_back(domain->getConditionals()[2]);

	auto condplay = std::make_shared<sspConditionalPlayer>();
	condplay->setName("Dunder all");
	condplay->setPlayers(players);
	condplay->setConditionals(conds);
	condplay->setDefaultPlayer(kort);
	domain->getPlayers().push_back(condplay);

	// Task
	auto task = std::make_shared<sspPlayTask>();
	task->setName("Dunder");
	task->setCondition(domain->getConditionals()[1]);
	task->setVolumeFactor(domain->getValues()[1]);
	task->setPlayer(condplay);
	task->setPriority(sspPlayTask::Priority::Load);
	domain->getPlaytasks().push_back(task);

	auto msg_recv = std::make_unique<sspMessageWithReceiver>();
	sspMessage& msg = msg_recv->getMessage();
	msg.setTask(task);
	msg.setTime(domain->getValues()[22]);
	msg.setType(sspMessage::Type::Load);
	msg_recv->setReceiver(domain->getTimelines()[2]);

	auto msglist = std::make_shared<sspMessageList>();
	msglist->add(std::move(msg_recv));

	auto cond_msg = std::make_shared<sspConditionalMsgList>();
	cond_msg->add(domain->getConditionals()[0], msglist);

	task->setMessageList(sspPlayTask::Messages::Exit, cond_msg);
}

void Storedal::buildStartList(sspDomainData * domain)
{
	auto msglist = std::make_shared<sspMessageList>();

	// Kulisser
	auto val = std::make_shared<sspBasicValue>();
	val->setName("60");
	val->setValue(60);
	domain->getValues().push_back(val);

	auto msg_recv = std::make_unique<sspMessageWithReceiver>();
	sspMessage& msg1 = msg_recv->getMessage();
	msg1.setTask(domain->getPlaytasks()[0]);
	msg1.setTime(domain->getValues()[24]);
	msg1.setType(sspMessage::Type::Load);
	msg_recv->setReceiver(domain->getTimelines()[1]);
	msglist->add(std::move(msg_recv));

	// Rekker
	msg_recv.reset(new sspMessageWithReceiver);
	sspMessage& msg2 = msg_recv->getMessage();
	msg2.setTask(domain->getPlaytasks()[1]);
	msg2.setTime(domain->getValues()[22]);
	msg2.setType(sspMessage::Type::Load);
	msg_recv->setReceiver(domain->getTimelines()[2]);
	msglist->add(std::move(msg_recv));

	// Signaler
	val.reset(new sspBasicValue);
	val->setName("180");
	val->setValue(180);
	domain->getValues().push_back(val);

	auto randval = std::make_shared<sspRandomValue>();
	randval->setName("3 to 9 minutes");
	randval->setLow(val);
	randval->setHigh(domain->getValues()[21]);
	domain->getValues().push_back(randval);

	msg_recv.reset(new sspMessageWithReceiver);
	sspMessage& msg3 = msg_recv->getMessage();
	msg3.setTask(domain->getPlaytasks()[2]);
	msg3.setTime(randval);
	msg3.setType(sspMessage::Type::Load);
	msg_recv->setReceiver(domain->getTimelines()[3]);
	msglist->add(std::move(msg_recv));

	// Attakker
	msg_recv.reset(new sspMessageWithReceiver);
	sspMessage& msg4 = msg_recv->getMessage();
	msg4.setTask(domain->getPlaytasks()[3]);
	msg4.setTime(domain->getValues()[22]);
	msg4.setType(sspMessage::Type::Load);
	msg_recv->setReceiver(domain->getTimelines()[2]);
	msglist->add(std::move(msg_recv));

	// Rens
	msg_recv.reset(new sspMessageWithReceiver);
	sspMessage& msg5 = msg_recv->getMessage();
	msg5.setTask(domain->getPlaytasks()[4]);
	msg5.setTime(domain->getValues()[0]);
	msg5.setType(sspMessage::Type::Load);
	msg_recv->setReceiver(domain->getTimelines()[1]);
	msglist->add(std::move(msg_recv));

	// Dunder
	msg_recv.reset(new sspMessageWithReceiver);
	sspMessage& msg6 = msg_recv->getMessage();
	msg6.setTask(domain->getPlaytasks()[5]);
	msg6.setTime(randval);
	msg6.setType(sspMessage::Type::Load);
	msg_recv->setReceiver(domain->getTimelines()[2]);
	msglist->add(std::move(msg_recv));

	auto startlist = domain->getStartList();
	startlist->add(domain->getConditionals()[0], msglist);
}

void Storedal::buildTriggerList(sspDomainData * domain)
{
	auto msglist = std::make_shared<sspMessageList>();

	// Rens should appear every hour
	auto msg_recv = std::make_unique<sspMessageWithReceiver>();
	sspMessage& msg1 = msg_recv->getMessage();
	msg1.setTask(domain->getPlaytasks()[4]);
	msg1.setTime(domain->getValues()[0]);
	msg1.setType(sspMessage::Type::Load);
	msg_recv->setReceiver(domain->getTimelines()[1]);
	msglist->add(std::move(msg_recv));

	// The conditional message list
	// Should not play if it is already playing
	sspWeakVector<sspPlayer> players;
	players.push_back(domain->getPlayers()[40]);

	auto playing = std::make_shared<sspIsPlaying>();
	playing->setName("Rens is playing");
	playing->setPlayers(players);
	domain->getConditionals().push_back(playing);

	auto not_playing = std::make_shared<sspNot>();
	not_playing->setName("Rens is not playing");
	not_playing->setOperand(playing);
	domain->getConditionals().push_back(not_playing);

	auto cond_msglist = std::make_shared<sspConditionalMsgList>();
	cond_msglist->add(not_playing, msglist);

	// Finally, the triggered message list in sspPlayManager
	auto hour = std::make_shared<sspMinuteCompare>();
	hour->setName("0 minutes passed the hour");
	hour->setMinutes(0);
	hour->setRelationship(sspMinuteCompare::Relation::Equal);
	domain->getConditionals().push_back(hour);

	auto trigger = std::make_shared<sspTrigger>();
	trigger->setName("Trigger on the hour");
	trigger->setConditional(hour);
	trigger->setChange(sspTrigger::Trigger::True);
	domain->getConditionals().push_back(trigger);

	auto trigger_list = domain->getTriggerList();
	trigger_list->add(trigger, cond_msglist);
}

void Storedal::buildUserOutput(sspDomainData * domain)
{
	domain->getOutputValues().push_back(domain->getValues()[2]);
}
