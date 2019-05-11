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
	if (!domain) return;

	auto bool_true = std::make_shared<sspBoolean>();
	bool_true->setName("true");
	bool_true->setValue(true);
	domain->getConditionals().push_back(bool_true);

	auto val_0 = std::make_shared<sspBasicValue>();
	val_0->setName("0.0");
	val_0->setValue(0.0);
	domain->getValues().push_back(val_0);

	auto val_1 = std::make_shared<sspBasicValue>();
	val_1->setName("1.0");
	val_1->setValue(1.0);
	domain->getValues().push_back(val_1);

	auto root = domain->getTimelines()[0];
	root->setTimeFactor(val_1);

	auto val = std::make_shared<sspBasicValue>();
	val->setName("Kulisse volume");
	val->setValue(1.0);
	domain->getValues().push_back(val);

	auto stream = std::make_shared<sspAudioStream>();
	stream->setName("Kulisse stream");
	stream->setTimeFactor(val_1);
	stream->setVolumeFactor(val);
	stream->setMaxTasks(2, 0);
	domain->getTimelines().push_back(stream);

	sspWeakVector<sspTimeline> root_children;
	root_children.push_back(stream);
	root->setChildren(root_children);

	auto val_ai = std::make_shared<sspBasicValue>();
	val_ai->setName("Light value");
	val_ai->setValue(4.0);
	domain->getValues().push_back(val_ai);

	// Disable inputs when testing on laptop
	auto ai = std::make_shared<sspICPanalogInput>();
	ai->setName("Light input");
	domain->getInputs().push_back(ai);
	ai->setUpdateInterval(5.0);
	ai->setPort(5);
	ai->setChannel(0);
	ai->setAddress(1);
	ai->setValue(val_ai);

	auto val_limit = std::make_shared<sspBasicValue>();
	val_limit->setName("Light limit 1");
	val_limit->setValue(0.3);
	domain->getValues().push_back(val_limit);

	auto light_1 = std::make_shared<sspValueCompare>();
	light_1->setName("Minimum light");
	light_1->setRelationship(sspValueCompare::Relation::LargeEq);
	light_1->setThreshold(val_limit);
	light_1->setTest(val_ai);
	domain->getConditionals().push_back(light_1);

	val_limit.reset(new sspBasicValue);
	val_limit->setName("Light limit 2");
	val_limit->setValue(1.5);
	domain->getValues().push_back(val_limit);

	auto light_2 = std::make_shared<sspValueCompare>();
	light_2->setName("Medium light");
	light_2->setRelationship(sspValueCompare::Relation::LargeEq);
	light_2->setThreshold(val_limit);
	light_2->setTest(val_ai);
	domain->getConditionals().push_back(light_2);

	val_limit.reset(new sspBasicValue);
	val_limit->setName("Light limit 3");
	val_limit->setValue(3.0);
	domain->getValues().push_back(val_limit);

	auto light_3 = std::make_shared<sspValueCompare>();
	light_3->setName("Maximum light");
	light_3->setRelationship(sspValueCompare::Relation::LargeEq);
	light_3->setThreshold(val_limit);
	light_3->setTest(val_ai);
	domain->getConditionals().push_back(light_3);

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

	val.reset(new sspBasicValue);
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
	args.push_back(val_ai);
	args.push_back(val_0);

	std::vector<double> const_weight{10, 1};

	auto randplay = std::make_shared<sspRandomPlayer>();
	randplay->setName("Kulisse all");
	randplay->setPlayers(players);
	randplay->setWeights(args);
	randplay->setConstantWeights(const_weight);
	domain->getPlayers().push_back(randplay);
	   
	auto task = std::make_shared<sspPlayTask>();
	task->setName("Kulisse");
	task->setCondition(light_1);
	task->setVolumeFactor(val_1);
	task->setPlayer(randplay);
	task->setPriority(sspPlayTask::Priority::Load);
	domain->getPlaytasks().push_back(task);

	auto msg_recv = std::make_unique<sspMessageWithReceiver>();
	sspMessage& msg = msg_recv->getMessage();
	msg.setTask(task);
	msg.setTime(val_0);
	msg.setType(sspMessage::Type::Load);
	msg_recv->setReceiver(stream);

	auto msglist = std::make_shared<sspMessageList>();
	msglist->add(std::move(msg_recv));

	auto cond_msg = std::make_shared<sspConditionalMsgList>();
	cond_msg->add(bool_true, msglist);

	task->setMessageList(sspPlayTask::Messages::Exit, cond_msg);

	auto& startlist = manager->getStartList();
	startlist.add(bool_true, msglist);
}
