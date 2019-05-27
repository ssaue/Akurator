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

	buildBasicContent(domain);
	buildInputContent(domain);
	buildUserInputContent(domain);

	buildTimelineHierarchy(domain);

	buildKulisse(domain);

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
	auto ai = std::make_shared<sspICPanalogInput>();
	ai->setName("Light input");
	domain->getInputs().push_back(ai);
	ai->setUpdateInterval(5.0);
	ai->setPort(5);
	ai->setChannel(0);
	ai->setAddress(1);
	ai->setValue(val);

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
	range->setName("Master volume control");
	range->setValue(1.0);
	range->setValueRange(0.0, 1.0);
	domain->getValues().push_back(range);
	domain->getInputValues().push_back(range);

	range.reset(new sspValueRange);
	range->setName("Kulisse volume control");
	range->setValue(1.0);
	range->setValueRange(0.0, 1.0);
	domain->getValues().push_back(range);
	domain->getInputValues().push_back(range);
}

void Storedal::buildTimelineHierarchy(sspDomainData * domain)
{
	auto root = domain->getTimelines()[0];
	root->setTimeFactor(domain->getValues()[1]);

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
	stream->setMaxTasks(2, 0);
	domain->getTimelines().push_back(stream);

	sspWeakVector<sspTimeline> root_children;
	root_children.push_back(domain->getTimelines()[1]);
	root->setChildren(root_children);
}

void Storedal::buildKulisse(sspDomainData * domain)
{
	auto str = std::make_shared<sspSimpleString>();
	str->setString("c:/Storedal/Lyder/Kulisser/");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	auto file = std::make_shared<sspFileString>();
	file->setName("Kulisse path");
	file->setPath(str);
	file->setAudioOnly(true);
	file->setRecursiveSearch(false);
	domain->getStrings().push_back(file);

	str.reset(new sspSimpleString);
	str->setString("/play/kulisse");
	str->setName(str->getString());
	domain->getStrings().push_back(str);

	auto val = std::make_shared<sspBasicValue>();
	val->setName("0.5");
	val->setValue(0.5);
	domain->getValues().push_back(val);

	auto val2 = std::make_shared<sspBasicValue>();
	val2->setName("2.5");
	val2->setValue(2.5);
	domain->getValues().push_back(val2);

	auto random = std::make_shared<sspRandomValue>();
	random->setName("Reverb");
	random->setLow(val);
	random->setHigh(val2);
	domain->getValues().push_back(random);

	sspWeakVector<sspValue> args;
	args.push_back(random);

	auto osc = std::make_shared<sspOSCPlayer>();
	osc->setName("Kulisse sounds");
	osc->setAddress(str);
	osc->setPath(file);
	osc->setArguments(args);
	domain->getPlayers().push_back(osc);

	val.reset(new sspBasicValue);
	val->setName("15");
	val->setValue(15);
	domain->getValues().push_back(val);

	auto silent = std::make_shared<sspSilencePlayer>();
	silent->setName("Kulisse silence");
	silent->setDuration(val);
	domain->getPlayers().push_back(silent);

	sspWeakVector<sspPlayer> players;
	players.push_back(osc);
	players.push_back(silent);

	args.clear();
	args.push_back(domain->getValues()[2]);
	args.push_back(domain->getValues()[0]);

	std::vector<double> const_weight{ 10, 1 };

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

void Storedal::buildStartList(sspDomainData * domain, sspPlayManager * manager)
{
	auto msg_recv = std::make_unique<sspMessageWithReceiver>();
	sspMessage& msg = msg_recv->getMessage();
	msg.setTask(domain->getPlaytasks()[0]);
	msg.setTime(domain->getValues()[0]);
	msg.setType(sspMessage::Type::Load);
	msg_recv->setReceiver(domain->getTimelines()[1]);

	auto msglist = std::make_shared<sspMessageList>();
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
