/*
  ==============================================================================

    Bekkelaget.cpp
    Created: 4 May 2019 12:48:32pm
    Author:  Admin

  ==============================================================================
*/

#include "Bekkelaget.h"

#include "domain/sspDomainData.h"
#include "engine/sspPlayManager.h"
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

// If in an environment without support for input from external loggers, then comment this #define
//#define SUPPORT_INPUTS 1

namespace {
    std::string file_root = "C:/Bekkelaget/Lyder/";
}

void Bekkelaget::buildContent(sspDomainData* domain, sspPlayManager* manager)
{
    if (!domain || !manager) return;

    domain->clearContents();
    manager->clearContents();

    buildBasicContent(domain);
    buildInputContent(domain);
    buildUserInputContent(domain);

    buildTimelineHierarchy(domain);

    buildHallDraape(domain);
    buildHallKepler(domain);
    buildHallKaskade(domain);
    buildHallKonkret(domain);
    buildTunnelKaskade(domain);
    buildTunnelKonkret(domain);

    buildStartList(domain, manager);
    buildUserOutput(domain);
}

void Bekkelaget::buildBasicContent(sspDomainData* domain)
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

void Bekkelaget::buildInputContent(sspDomainData* domain)
{
    auto val = std::make_shared<sspBasicValue>();
    val->setName("Vannmengde");
    val->setValue(1.0);
    domain->getValues().push_back(val);

#ifdef SUPPORT_INPUTS

    auto ai = std::make_shared<sspICPanalogInput>();
    ai->setName("Vannmengde");
    domain->getInputs().push_back(ai);
    ai->setUpdateInterval(5.0);
    ai->setPort(1);
    ai->setChannel(0);
    ai->setAddress(2);
    ai->setValue(val);

#endif

    val.reset(new sspBasicValue());
    val->setName("Tunnel_slam");
    val->setValue(1.0);
    domain->getValues().push_back(val);

#ifdef SUPPORT_INPUTS

    ai.reset(new sspICPanalogInput());
    ai->setName("Tunnel_slam");
    domain->getInputs().push_back(ai);
    ai->setUpdateInterval(5.0);
    ai->setPort(1);
    ai->setChannel(1);
    ai->setAddress(2);
    ai->setValue(val);

#endif

    val.reset(new sspBasicValue());
    val->setName("Hall_slam");
    val->setValue(1.0);
    domain->getValues().push_back(val);

#ifdef SUPPORT_INPUTS

    ai.reset(new sspICPanalogInput());
    ai->setName("Hall_slam");
    domain->getInputs().push_back(ai);
    ai->setUpdateInterval(5.0);
    ai->setPort(1);
    ai->setChannel(2);
    ai->setAddress(2);
    ai->setValue(val);

#endif

    val.reset(new sspBasicValue());
    val->setName("Filterlevel");
    val->setValue(1.0);
    domain->getValues().push_back(val);

#ifdef SUPPORT_INPUTS

    ai.reset(new sspICPanalogInput());
    ai->setName("Filterlevel");
    domain->getInputs().push_back(ai);
    ai->setUpdateInterval(5.0);
    ai->setPort(1);
    ai->setChannel(3);
    ai->setAddress(2);
    ai->setValue(val);

#endif

    auto cond = std::make_shared<sspBoolean>();
    cond->setName("High_water");
    cond->setValue(false);
    domain->getConditionals().push_back(cond);

#ifdef SUPPORT_INPUTS

    auto di = std::make_shared<sspICPdigitalInput>();
    di->setName("High_water");
    domain->getInputs().push_back(di);
    di->setUpdateInterval(5.0);
    di->setPort(1);
    di->setChannel(0);
    di->setAddress(1);
    di->setConditional(cond);

#endif

    cond.reset(new sspBoolean());
    cond->setName("Start_pumpe");
    cond->setValue(false);
    domain->getConditionals().push_back(cond);

#ifdef SUPPORT_INPUTS

    di.reset(new sspICPdigitalInput());
    di->setName("Start_pumpe");
    domain->getInputs().push_back(di);
    di->setUpdateInterval(5.0);
    di->setPort(1);
    di->setChannel(1);
    di->setAddress(1);
    di->setConditional(cond);

#endif

    cond.reset(new sspBoolean());
    cond->setName("Start_spyling");
    cond->setValue(false);
    domain->getConditionals().push_back(cond);

#ifdef SUPPORT_INPUTS

    di.reset(new sspICPdigitalInput());
    di->setName("Start_spyling");
    domain->getInputs().push_back(di);
    di->setUpdateInterval(5.0);
    di->setPort(1);
    di->setChannel(2);
    di->setAddress(1);
    di->setConditional(cond);

#endif

    cond.reset(new sspBoolean());
    cond->setName("Start_blaasing");
    cond->setValue(false);
    domain->getConditionals().push_back(cond);

#ifdef SUPPORT_INPUTS

    di.reset(new sspICPdigitalInput());
    di->setName("Start_blaasing");
    domain->getInputs().push_back(di);
    di->setUpdateInterval(5.0);
    di->setPort(1);
    di->setChannel(3);
    di->setAddress(1);
    di->setConditional(cond);

#endif

}

void Bekkelaget::buildUserInputContent(sspDomainData* domain)
{
    auto range = std::make_shared<sspValueRange>();
    range->setName("Master");
    range->setValue(1.0);
    range->setValueRange(0.0, 1.0);
    domain->getValues().push_back(range);
    domain->getInputValues().push_back(range);

    range.reset(new sspValueRange);
    range->setName("Hall draape");
    range->setValue(1.0);
    range->setValueRange(0.0, 1.0);
    domain->getValues().push_back(range);
    domain->getInputValues().push_back(range);

    range.reset(new sspValueRange);
    range->setName("Hall kaskade");
    range->setValue(1.0);
    range->setValueRange(0.0, 1.0);
    domain->getValues().push_back(range);
    domain->getInputValues().push_back(range);

    range.reset(new sspValueRange);
    range->setName("Hall konkret");
    range->setValue(1.0);
    range->setValueRange(0.0, 1.0);
    domain->getValues().push_back(range);
    domain->getInputValues().push_back(range);

    range.reset(new sspValueRange);
    range->setName("Tunnel kaskade");
    range->setValue(1.0);
    range->setValueRange(0.0, 1.0);
    domain->getValues().push_back(range);
    domain->getInputValues().push_back(range);

    range.reset(new sspValueRange);
    range->setName("Tunnel konkret");
    range->setValue(1.0);
    range->setValueRange(0.0, 1.0);
    domain->getValues().push_back(range);
    domain->getInputValues().push_back(range);
}

void Bekkelaget::buildTimelineHierarchy(sspDomainData* domain)
{
    // Root timeline

    // Time factor based on Vannmengde
    auto map = std::make_shared<sspLinearMap>();
    map->setName("Global tetthet");
    map->setInputRange(20, 0);
    map->setOutputRange(0.75, 1.25);
    map->setValue(domain->getValues()[2]);
    domain->getValues().push_back(map);

    auto root = std::make_shared<sspTimeline>();
    root->setName("Root stream");
    root->setTimeFactor(map);
    domain->getTimelines().push_back(root);

    sspWeakVector<sspTimeline> root_children;

    // Hall dråpe audio stream
    sspWeakVector<sspValue> factors;
    factors.push_back(domain->getValues()[6]);
    factors.push_back(domain->getValues()[7]);

    auto val = std::make_shared<sspProductValue>();
    val->setName("Dråpe volume");
    val->setFactors(factors);
    domain->getValues().push_back(val);

    auto stream = std::make_shared<sspAudioStream>();
    stream->setName("Dråpe stream");
    stream->setTimeFactor(domain->getValues()[1]);
    stream->setVolumeFactor(val);
    stream->setMaxTasks(3, 1);
    domain->getTimelines().push_back(stream);
    root_children.push_back(stream);

    // Hall kaskade audio stream
    factors[1] = domain->getValues()[8];

    val.reset(new sspProductValue);
    val->setName("Hall kaskade volume");
    val->setFactors(factors);
    domain->getValues().push_back(val);

    // Time factor based on Filternivå
    map.reset(new sspLinearMap());
    map->setName("Kaskade tetthet");
    map->setInputRange(20, 0);
    map->setOutputRange(0.75, 1.25);
    map->setValue(domain->getValues()[5]);
    domain->getValues().push_back(map);

    stream.reset(new sspAudioStream);
    stream->setName("Hall kaskade stream");
    stream->setTimeFactor(map);
    stream->setVolumeFactor(val);
    stream->setMaxTasks(1, 1);
    domain->getTimelines().push_back(stream);
    root_children.push_back(stream);

    // Hall konkret audio stream
    factors[1] = domain->getValues()[9];

    val.reset(new sspProductValue);
    val->setName("Hall konkret volume");
    val->setFactors(factors);
    domain->getValues().push_back(val);

    stream.reset(new sspAudioStream);
    stream->setName("Hall konkret stream");
    stream->setTimeFactor(domain->getValues()[1]);
    stream->setVolumeFactor(val);
    stream->setMaxTasks(2, 1);
    domain->getTimelines().push_back(stream);
    root_children.push_back(stream);

    // Tunnel kaskade audio stream
    factors[1] = domain->getValues()[10];

    val.reset(new sspProductValue);
    val->setName("Tunnel kaskade volume");
    val->setFactors(factors);
    domain->getValues().push_back(val);

    stream.reset(new sspAudioStream);
    stream->setName("Tunnel kaskade stream");
    stream->setTimeFactor(map);
    stream->setVolumeFactor(val);
    stream->setMaxTasks(1, 1);
    domain->getTimelines().push_back(stream);
    root_children.push_back(stream);

    // Tunnel konkret audio stream
    factors[1] = domain->getValues()[11];

    val.reset(new sspProductValue);
    val->setName("Tunnel konkret volume");
    val->setFactors(factors);
    domain->getValues().push_back(val);

    stream.reset(new sspAudioStream);
    stream->setName("Tunnel konkret stream");
    stream->setTimeFactor(domain->getValues()[1]);
    stream->setVolumeFactor(val);
    stream->setMaxTasks(2, 1);
    domain->getTimelines().push_back(stream);
    root_children.push_back(stream);

    // Assign all streams to the root stream
    root->setChildren(root_children);
}

void Bekkelaget::buildHallDraape(sspDomainData* domain)
{
    auto addr = std::make_shared<sspSimpleString>();
    addr->setString("/play/draape");
    addr->setName(addr->getString());
    domain->getStrings().push_back(addr);

    auto parent_str = std::make_shared<sspSimpleString>();
    parent_str->setString(file_root + "Draape/");
    parent_str->setName(parent_str->getString());
    domain->getStrings().push_back(parent_str);

    auto norm_str = std::make_shared<sspSimpleString>();
    norm_str->setString("Normal");
    norm_str->setName(norm_str->getString());
    domain->getStrings().push_back(norm_str);

    auto mod_str = std::make_shared<sspSimpleString>();
    mod_str->setString("Modulert");
    mod_str->setName(mod_str->getString());
    domain->getStrings().push_back(mod_str);

    sspWeakVector<sspString> folder_strings;
    folder_strings.push_back(mod_str);

    sspWeakVector<sspConditional> conds;
    conds.push_back(domain->getConditionals()[1]);

    auto cond_str = std::make_shared<sspConditionalString>();
    cond_str->setName("Dråpe norm/mod");
    cond_str->setConditionals(conds);
    cond_str->setStrings(folder_strings);
    cond_str->setDefaultString(norm_str);
    domain->getStrings().push_back(cond_str);

    sspWeakVector<sspString> concat_strings;
    concat_strings.push_back(parent_str);
    concat_strings.push_back(cond_str);

    auto full_path = std::make_shared<sspConcatString>();
    full_path->setName("Dråpe folder");
    full_path->setStrings(concat_strings);
    domain->getStrings().push_back(full_path);

    auto file = std::make_shared<sspFileString>();
    file->setName("Dråpe path");
    file->setPath(full_path);
    file->setAudioOnly(true);
    file->setRecursiveSearch(false);
    domain->getStrings().push_back(file);

    auto draape = std::make_shared<sspOSCPlayer>();
    draape->setName("Dråpe");
    draape->setAddress(addr);
    draape->setPath(file);
    domain->getPlayers().push_back(draape);

    // Task
    auto task = std::make_shared<sspPlayTask>();
    task->setName("Dråpe");
    task->setCondition(domain->getConditionals()[0]);
    task->setVolumeFactor(domain->getValues()[1]);
    task->setPlayer(draape);
    task->setPriority(sspPlayTask::Priority::Wait);
    domain->getPlaytasks().push_back(task);

    // The message list is added later when the necessary task is defined
}

void Bekkelaget::buildHallKepler(sspDomainData* domain)
{
    // Kepler 1
    auto addr = std::make_shared<sspSimpleString>();
    addr->setString("/play/kepler");
    addr->setName(addr->getString());
    domain->getStrings().push_back(addr);

    auto path = std::make_shared<sspSimpleString>();
    path->setString(file_root + "Kepler 1.wav");
    path->setName(path->getString());
    domain->getStrings().push_back(path);

    auto file = std::make_shared<sspFileString>();
    file->setName("Kepler 1 path");
    file->setPath(path);
    file->setAudioOnly(true);
    file->setRecursiveSearch(false);
    domain->getStrings().push_back(file);

    auto kepler = std::make_shared<sspOSCPlayer>();
    kepler->setName("Kepler 1");
    kepler->setAddress(addr);
    kepler->setPath(file);
    domain->getPlayers().push_back(kepler);

    // Task
    auto task = std::make_shared<sspPlayTask>();
    task->setName("Kepler 1");
    task->setCondition(domain->getConditionals()[0]);
    task->setVolumeFactor(domain->getValues()[1]);
    task->setPlayer(kepler);
    task->setPriority(sspPlayTask::Priority::Wait);
    domain->getPlaytasks().push_back(task);

    // Random repeat at 0 to 10 seconds
    auto val = std::make_shared<sspBasicValue>();
    val->setName("10");
    val->setValue(10);
    domain->getValues().push_back(val);

    auto random = std::make_shared<sspRandomValue>();
    random->setName("0 to 10 seconds");
    random->setLow(domain->getValues()[0]);
    random->setHigh(val);
    domain->getValues().push_back(random);

    auto msg_recv = std::make_unique<sspMessageWithReceiver>();
    sspMessage& msg = msg_recv->getMessage();
    msg.setTask(task);
    msg.setTime(random);
    msg.setType(sspMessage::Type::Load);
    msg_recv->setReceiver(domain->getTimelines()[1]);

    auto msglist = std::make_shared<sspMessageList>();
    msglist->add(std::move(msg_recv));

    auto cond_msg = std::make_shared<sspConditionalMsgList>();
    cond_msg->add(domain->getConditionals()[0], msglist);

    task->setMessageList(sspPlayTask::Messages::Exit, cond_msg);

    // Kepler 2
    path.reset(new sspSimpleString());
    path->setString(file_root + "Kepler 2.wav");
    path->setName(path->getString());
    domain->getStrings().push_back(path);

    file.reset(new sspFileString());
    file->setName("Kepler 2 path");
    file->setPath(path);
    file->setAudioOnly(true);
    file->setRecursiveSearch(false);
    domain->getStrings().push_back(file);

    kepler.reset(new sspOSCPlayer());
    kepler->setName("Kepler 2");
    kepler->setAddress(addr);
    kepler->setPath(file);
    domain->getPlayers().push_back(kepler);

    // Task
    task.reset(new sspPlayTask());
    task->setName("Kepler 2");
    task->setCondition(domain->getConditionals()[0]);
    task->setVolumeFactor(domain->getValues()[1]);
    task->setPlayer(kepler);
    task->setPriority(sspPlayTask::Priority::Wait);
    domain->getPlaytasks().push_back(task);

    msg_recv.reset(new sspMessageWithReceiver());
    sspMessage& msg2 = msg_recv->getMessage();
    msg2.setTask(task);
    msg2.setTime(random);
    msg2.setType(sspMessage::Type::Load);
    msg_recv->setReceiver(domain->getTimelines()[1]);

    msglist.reset(new sspMessageList());
    msglist->add(std::move(msg_recv));

    cond_msg.reset(new sspConditionalMsgList());
    cond_msg->add(domain->getConditionals()[0], msglist);

    task->setMessageList(sspPlayTask::Messages::Exit, cond_msg);
}

void Bekkelaget::buildHallKaskade(sspDomainData* domain)
{
    auto addr = std::make_shared<sspSimpleString>();
    addr->setString("/play/hall_kaskade");
    addr->setName(addr->getString());
    domain->getStrings().push_back(addr);

    auto parent_str = std::make_shared<sspSimpleString>();
    parent_str->setString(file_root + "Syntetisk/");
    parent_str->setName(parent_str->getString());
    domain->getStrings().push_back(parent_str);

    auto norm_str = std::make_shared<sspSimpleString>();
    norm_str->setString("Lang normal");
    norm_str->setName(norm_str->getString());
    domain->getStrings().push_back(norm_str);

    auto mod_str = std::make_shared<sspSimpleString>();
    mod_str->setString("Lang modulert");
    mod_str->setName(mod_str->getString());
    domain->getStrings().push_back(mod_str);

    sspWeakVector<sspString> folder_strings;
    folder_strings.push_back(mod_str);

    sspWeakVector<sspConditional> conds;
    conds.push_back(domain->getConditionals()[1]);

    auto cond_str = std::make_shared<sspConditionalString>();
    cond_str->setName("Kaskade norm/mod");
    cond_str->setConditionals(conds);
    cond_str->setStrings(folder_strings);
    cond_str->setDefaultString(norm_str);
    domain->getStrings().push_back(cond_str);

    sspWeakVector<sspString> concat_strings;
    concat_strings.push_back(parent_str);
    concat_strings.push_back(cond_str);

    auto full_path = std::make_shared<sspConcatString>();
    full_path->setName("Kaskade folder");
    full_path->setStrings(concat_strings);
    domain->getStrings().push_back(full_path);

    auto file = std::make_shared<sspFileString>();
    file->setName("Kaskade path");
    file->setPath(full_path);
    file->setAudioOnly(true);
    file->setRecursiveSearch(false);
    domain->getStrings().push_back(file);

    // Speed factor based on "Hall_slam"
    auto map = std::make_shared<sspLinearMap>();
    map->setName("Hastighet hall");
    map->setInputRange(20, 0);
    map->setOutputRange(0.85, 1.15);
    map->setValue(domain->getValues()[4]);
    domain->getValues().push_back(map);

    sspWeakVector<sspValue> args;
    args.push_back(map);

    auto kaskade = std::make_shared<sspOSCPlayer>();
    kaskade->setName("Hall kaskade");
    kaskade->setAddress(addr);
    kaskade->setPath(file);
    kaskade->setArguments(args);
    domain->getPlayers().push_back(kaskade);

    // Random repeat at 10 to 20 seconds    
    auto val = std::make_shared<sspBasicValue>();
    val->setName("20");
    val->setValue(20);
    domain->getValues().push_back(val);

    auto random = std::make_shared<sspRandomValue>();
    random->setName("10 to 20 seconds");
    random->setLow(domain->getValues()[19]);
    random->setHigh(val);
    domain->getValues().push_back(random);

    // Double count if not "Start spyling"
    auto val2 = std::make_shared<sspBasicValue>();
    val2->setName("2");
    val2->setValue(2);
    domain->getValues().push_back(val2);

    auto val4 = std::make_shared<sspBasicValue>();
    val4->setName("4");
    val4->setValue(4);
    domain->getValues().push_back(val4);

    sspWeakVector<sspValue> cond_values;
    cond_values.push_back(val2);

    sspWeakVector<sspConditional> val_conds;
    val_conds.push_back(domain->getConditionals()[3]);

    auto cond_val = std::make_shared<sspConditionalValue>();
    cond_val->setName("Start spyling ? 2 : 4");
    cond_val->setConditionals(val_conds);
    cond_val->setValues(cond_values);
    cond_val->setDefaultValue(val4);
    domain->getValues().push_back(cond_val);

    auto dist = std::make_shared<sspDistributionPlayer>();
    dist->setName("Hall kaskade distro");
    dist->setPlayer(kaskade);
    dist->setLoopMode(sspDistributionPlayer::LoopMode::Count);
    dist->setStartTime(random);
    dist->setCondition(domain->getConditionals()[0]);
    dist->setDuration(cond_val);
    domain->getPlayers().push_back(dist);

    // Task
    auto task = std::make_shared<sspPlayTask>();
    task->setName("Hall kaskade");
    task->setCondition(domain->getConditionals()[0]);
    task->setVolumeFactor(domain->getValues()[1]);
    task->setPlayer(dist);
    task->setPriority(sspPlayTask::Priority::Wait);
    domain->getPlaytasks().push_back(task);

    auto msg_recv = std::make_unique<sspMessageWithReceiver>();
    sspMessage& msg = msg_recv->getMessage();
    msg.setTask(domain->getPlaytasks()[0]);
    msg.setTime(val);
    msg.setType(sspMessage::Type::Load);
    msg_recv->setReceiver(domain->getTimelines()[1]);

    auto msglist = std::make_shared<sspMessageList>();
    msglist->add(std::move(msg_recv));

    auto cond_msg = std::make_shared<sspConditionalMsgList>();
    cond_msg->add(domain->getConditionals()[0], msglist);

    task->setMessageList(sspPlayTask::Messages::Exit, cond_msg);

    // Add msg list for draape, now that the hall kaskade task is defined
    // Random repeat at 1 to 5 seconds    
    val.reset(new sspBasicValue());
    val->setName("5");
    val->setValue(5);
    domain->getValues().push_back(val);

    random.reset(new sspRandomValue());
    random->setName("1 to 5 seconds");
    random->setLow(domain->getValues()[1]);
    random->setHigh(val);
    domain->getValues().push_back(random);

    msg_recv.reset(new sspMessageWithReceiver());
    sspMessage& msg2 = msg_recv->getMessage();
    msg2.setTask(task);
    msg2.setTime(random);
    msg2.setType(sspMessage::Type::Load);
    msg_recv->setReceiver(domain->getTimelines()[2]);

    msglist.reset(new sspMessageList());
    msglist->add(std::move(msg_recv));

    cond_msg.reset(new sspConditionalMsgList());
    cond_msg->add(domain->getConditionals()[0], msglist);

    domain->getPlaytasks()[0]->setMessageList(sspPlayTask::Messages::Exit, cond_msg);
}

void Bekkelaget::buildHallKonkret(sspDomainData* domain)
{
    auto addr = std::make_shared<sspSimpleString>();
    addr->setString("/play/hall4_konkret");
    addr->setName(addr->getString());
    domain->getStrings().push_back(addr);

    auto parent_str = std::make_shared<sspSimpleString>();
    parent_str->setString(file_root);
    parent_str->setName(parent_str->getString());
    domain->getStrings().push_back(parent_str);

    auto norm_str = std::make_shared<sspSimpleString>();
    norm_str->setString("Konkret/Kort/");
    norm_str->setName(norm_str->getString());
    domain->getStrings().push_back(norm_str);

    auto mod_str = std::make_shared<sspSimpleString>();
    mod_str->setString("Syntetisk/Kort");
    mod_str->setName(mod_str->getString());
    domain->getStrings().push_back(mod_str);

    sspWeakVector<sspString> folder_strings;
    folder_strings.push_back(mod_str);

    sspWeakVector<sspConditional> conds;
    conds.push_back(domain->getConditionals()[4]);

    auto cond_str = std::make_shared<sspConditionalString>();
    cond_str->setName("Konkret konkret/syntetisk");
    cond_str->setConditionals(conds);
    cond_str->setStrings(folder_strings);
    cond_str->setDefaultString(norm_str);
    domain->getStrings().push_back(cond_str);

    sspWeakVector<sspString> concat_strings;
    concat_strings.push_back(parent_str);
    concat_strings.push_back(cond_str);

    auto full_path = std::make_shared<sspConcatString>();
    full_path->setName("Kort konkret folder");
    full_path->setStrings(concat_strings);
    domain->getStrings().push_back(full_path);

    auto file = std::make_shared<sspFileString>();
    file->setName("Kort konkret path");
    file->setPath(full_path);
    file->setAudioOnly(true);
    file->setRecursiveSearch(false);
    domain->getStrings().push_back(file);

    auto hall4 = std::make_shared<sspOSCPlayer>();
    hall4->setName("Hall 4 konkret");
    hall4->setAddress(addr);
    hall4->setPath(file);
    domain->getPlayers().push_back(hall4);

    // Hall konkret 1 - 3
    addr.reset(new sspSimpleString());
    addr->setString("/play/hallene_konkret");
    addr->setName(addr->getString());
    domain->getStrings().push_back(addr);

    auto path_str = std::make_shared<sspSimpleString>();
    path_str->setString(file_root + "Konkret/Lang");
    path_str->setName(path_str->getString());
    domain->getStrings().push_back(path_str);

    file.reset(new sspFileString());
    file->setName("Hallene konkret path");
    file->setPath(path_str);
    file->setAudioOnly(true);
    file->setRecursiveSearch(false);
    domain->getStrings().push_back(file);

    auto hallene = std::make_shared<sspOSCPlayer>();
    hallene->setName("Hallene konkret");
    hallene->setAddress(addr);
    hallene->setPath(file);
    domain->getPlayers().push_back(hallene);

    sspWeakVector<sspValue> zeros;
    zeros.push_back(domain->getValues()[0]);
    zeros.push_back(domain->getValues()[0]);

    sspWeakVector<sspPlayer> players;
    players.push_back(hall4);
    players.push_back(hallene);

    auto random_player = std::make_shared<sspRandomPlayer>();
    random_player->setName("Hall konkret");
    random_player->setConstantWeights({ 1,2 });
    random_player->setWeights(zeros);
    random_player->setPlayers(players);
    domain->getPlayers().push_back(random_player);

    // Task
    auto task = std::make_shared<sspPlayTask>();
    task->setName("Hall konkret");
    task->setCondition(domain->getConditionals()[0]);
    task->setVolumeFactor(domain->getValues()[1]);
    task->setPlayer(random_player);
    task->setPriority(sspPlayTask::Priority::Wait);
    domain->getPlaytasks().push_back(task);

    auto msg_recv = std::make_unique<sspMessageWithReceiver>();
    sspMessage& msg = msg_recv->getMessage();
    msg.setTask(task);
    msg.setTime(domain->getValues()[23]);
    msg.setType(sspMessage::Type::Load);
    msg_recv->setReceiver(domain->getTimelines()[3]);

    auto msglist = std::make_shared<sspMessageList>();
    msglist->add(std::move(msg_recv));

    auto cond_msg = std::make_shared<sspConditionalMsgList>();
    cond_msg->add(domain->getConditionals()[0], msglist);

    task->setMessageList(sspPlayTask::Messages::Exit, cond_msg);
}

void Bekkelaget::buildTunnelKaskade(sspDomainData* domain)
{
    auto addr = std::make_shared<sspSimpleString>();
    addr->setString("/play/tunnel_kaskade");
    addr->setName(addr->getString());
    domain->getStrings().push_back(addr);

    // Speed factor based on "Hall_slam"
    auto map = std::make_shared<sspLinearMap>();
    map->setName("Hastighet tunnel");
    map->setInputRange(20, 0);
    map->setOutputRange(0.85, 1.15);
    map->setValue(domain->getValues()[3]);
    domain->getValues().push_back(map);

    sspWeakVector<sspValue> args;
    args.push_back(map);

    auto kaskade = std::make_shared<sspOSCPlayer>();
    kaskade->setName("Tunnel kaskade");
    kaskade->setAddress(addr);
    kaskade->setPath(domain->getStrings()[18]);
    kaskade->setArguments(args);
    domain->getPlayers().push_back(kaskade);

    // Task
    auto task = std::make_shared<sspPlayTask>();
    task->setName("Tunnel kaskade");
    task->setCondition(domain->getConditionals()[0]);
    task->setVolumeFactor(domain->getValues()[1]);
    task->setPlayer(kaskade);
    task->setPriority(sspPlayTask::Priority::Wait);
    domain->getPlaytasks().push_back(task);

    auto msg_recv = std::make_unique<sspMessageWithReceiver>();
    sspMessage& msg = msg_recv->getMessage();
    msg.setTask(task);
    msg.setTime(domain->getValues()[26]);
    msg.setType(sspMessage::Type::Load);
    msg_recv->setReceiver(domain->getTimelines()[4]);

    auto msglist = std::make_shared<sspMessageList>();
    msglist->add(std::move(msg_recv));

    auto cond_msg = std::make_shared<sspConditionalMsgList>();
    cond_msg->add(domain->getConditionals()[0], msglist);

    task->setMessageList(sspPlayTask::Messages::Exit, cond_msg);
}

void Bekkelaget::buildTunnelKonkret(sspDomainData* domain)
{
    auto addr = std::make_shared<sspSimpleString>();
    addr->setString("/play/tunnel_konkret");
    addr->setName(addr->getString());
    domain->getStrings().push_back(addr);

    auto tunnel = std::make_shared<sspOSCPlayer>();
    tunnel->setName("Tunnel konkret");
    tunnel->setAddress(addr);
    tunnel->setPath(domain->getStrings()[25]);
    domain->getPlayers().push_back(tunnel);

    // Task
    auto task = std::make_shared<sspPlayTask>();
    task->setName("Tunnel konkret");
    task->setCondition(domain->getConditionals()[0]);
    task->setVolumeFactor(domain->getValues()[1]);
    task->setPlayer(tunnel);
    task->setPriority(sspPlayTask::Priority::Wait);
    domain->getPlaytasks().push_back(task);

    auto msg_recv = std::make_unique<sspMessageWithReceiver>();
    sspMessage& msg = msg_recv->getMessage();
    msg.setTask(task);
    msg.setTime(domain->getValues()[20]);
    msg.setType(sspMessage::Type::Load);
    msg_recv->setReceiver(domain->getTimelines()[5]);

    auto msglist = std::make_shared<sspMessageList>();
    msglist->add(std::move(msg_recv));

    auto cond_msg = std::make_shared<sspConditionalMsgList>();
    cond_msg->add(domain->getConditionals()[0], msglist);

    task->setMessageList(sspPlayTask::Messages::Exit, cond_msg);
}

void Bekkelaget::buildStartList(sspDomainData* domain, sspPlayManager* manager)
{
    auto msglist = std::make_shared<sspMessageList>();

    // Dråpe
    auto val2 = std::make_shared<sspBasicValue>();
    val2->setName("40");
    val2->setValue(40);
    domain->getValues().push_back(val2);

    auto randval = std::make_shared<sspRandomValue>();
    randval->setName("20 to 40 seconds");
    randval->setLow(domain->getValues()[22]);
    randval->setHigh(val2);
    domain->getValues().push_back(randval);

    auto msg_recv = std::make_unique<sspMessageWithReceiver>();
    sspMessage& msg1 = msg_recv->getMessage();
    msg1.setTask(domain->getPlaytasks()[0]);
    msg1.setTime(randval);
    msg1.setType(sspMessage::Type::Load);
    msg_recv->setReceiver(domain->getTimelines()[1]);
    msglist->add(std::move(msg_recv));

    // Kepler 1
    msg_recv.reset(new sspMessageWithReceiver);
    sspMessage& msg2 = msg_recv->getMessage();
    msg2.setTask(domain->getPlaytasks()[1]);
    msg2.setTime(domain->getValues()[1]);
    msg2.setType(sspMessage::Type::Load);
    msg_recv->setReceiver(domain->getTimelines()[1]);
    msglist->add(std::move(msg_recv));

    // Kepler 2
    msg_recv.reset(new sspMessageWithReceiver);
    sspMessage& msg3 = msg_recv->getMessage();
    msg3.setTask(domain->getPlaytasks()[2]);
    msg3.setTime(domain->getValues()[24]);
    msg3.setType(sspMessage::Type::Load);
    msg_recv->setReceiver(domain->getTimelines()[1]);
    msglist->add(std::move(msg_recv));

    // Hall konkret
    randval.reset(new sspRandomValue());
    randval->setName("10 to 20 seconds");
    randval->setLow(domain->getValues()[19]);
    randval->setHigh(domain->getValues()[22]);
    domain->getValues().push_back(randval);

    msg_recv.reset(new sspMessageWithReceiver);
    sspMessage& msg4 = msg_recv->getMessage();
    msg4.setTask(domain->getPlaytasks()[4]);
    msg4.setTime(randval);
    msg4.setType(sspMessage::Type::Load);
    msg_recv->setReceiver(domain->getTimelines()[3]);
    msglist->add(std::move(msg_recv));

    // Tunnel kaskade
    auto val1 = std::make_shared<sspBasicValue>();
    val1->setName("30");
    val1->setValue(30);
    domain->getValues().push_back(val1);

    randval.reset(new sspRandomValue());
    randval->setName("10 to 30 seconds");
    randval->setLow(domain->getValues()[19]);
    randval->setHigh(val1);
    domain->getValues().push_back(randval);

    msg_recv.reset(new sspMessageWithReceiver);
    sspMessage& msg5 = msg_recv->getMessage();
    msg5.setTask(domain->getPlaytasks()[5]);
    msg5.setTime(randval);
    msg5.setType(sspMessage::Type::Load);
    msg_recv->setReceiver(domain->getTimelines()[4]);
    msglist->add(std::move(msg_recv));

    // Tunnel konkret
    msg_recv.reset(new sspMessageWithReceiver);
    sspMessage& msg6 = msg_recv->getMessage();
    msg6.setTask(domain->getPlaytasks()[6]);
    msg6.setTime(randval);
    msg6.setType(sspMessage::Type::Load);
    msg_recv->setReceiver(domain->getTimelines()[5]);
    msglist->add(std::move(msg_recv));

    auto& startlist = manager->getStartList();
    startlist.add(domain->getConditionals()[0], msglist);
}

void Bekkelaget::buildUserOutput(sspDomainData* domain)
{
    domain->getOutputValues().push_back(domain->getValues()[2]);
    domain->getOutputValues().push_back(domain->getValues()[3]);
    domain->getOutputValues().push_back(domain->getValues()[4]);
    domain->getOutputValues().push_back(domain->getValues()[5]);
}
