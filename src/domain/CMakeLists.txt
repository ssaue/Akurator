# CMakeLists.txt for domain library

# add_subdirectory(core)
# add_subdirectory(elements)

add_library(domain-lib
    STATIC
    core/sspDomainElement.h
    core/sspDomainPool.h
    core/sspDomainPool.cpp
    core/sspDomainPrimitives.h
    core/sspDomainPrimitives.cpp
    core/sspInput.h
    core/sspInput.cpp
    core/sspPlayer.h
    core/sspPlayer.cpp
    core/sspPlayTask.h
    core/sspPlayTask.cpp
    core/sspSharedVector.h
    core/sspTimeline.h
    core/sspTimeline.cpp

    elements/conditionals/sspAnd.cpp 
    elements/conditionals/sspAnd.h
    elements/conditionals/sspBoolean.h
    elements/conditionals/sspConditionals.cpp 
    elements/conditionals/sspConditionals.h
    elements/conditionals/sspDateInterval.cpp 
    elements/conditionals/sspDateInterval.h
    elements/conditionals/sspDayOfWeek.cpp 
    elements/conditionals/sspDayOfWeek.h
    elements/conditionals/sspIsPlaying.cpp 
    elements/conditionals/sspIsPlaying.h
    elements/conditionals/sspMinuteCompare.cpp 
    elements/conditionals/sspMinuteCompare.h
    elements/conditionals/sspNot.cpp 
    elements/conditionals/sspNot.h
    elements/conditionals/sspOr.cpp 
    elements/conditionals/sspOr.h
    elements/conditionals/sspTimeCompare.cpp 
    elements/conditionals/sspTimeCompare.h
    elements/conditionals/sspTimeInterval.cpp 
    elements/conditionals/sspTimeInterval.h
    elements/conditionals/sspTrigger.cpp 
    elements/conditionals/sspTrigger.h
    elements/conditionals/sspValueCompare.cpp 
    elements/conditionals/sspValueCompare.h
    elements/conditionals/sspValueInRange.cpp 
    elements/conditionals/sspValueInRange.h

    elements/inputs/sspICPanalogInput.cpp
    elements/inputs/sspICPanalogInput.h
    elements/inputs/sspICPdigitalInput.cpp
    elements/inputs/sspICPdigitalInput.h
    elements/inputs/sspICPinput.cpp 
    elements/inputs/sspICPinput.h
    elements/inputs/sspInputs.cpp 
    elements/inputs/sspInputs.h 

    elements/messages/sspConditionalMsgList.cpp
    elements/messages/sspConditionalMsgList.h
    elements/messages/sspMessage.cpp 
    elements/messages/sspMessage.h
    elements/messages/sspMessageHandler.h
    elements/messages/sspMessageList.cpp 
    elements/messages/sspMessageList.h
    elements/messages/sspMessageWithReceiver.cpp 
    elements/messages/sspMessageWithReceiver.h
    elements/messages/sspTimeTriggerMsgList.cpp 
    elements/messages/sspTimeTriggerMsgList.h
    elements/messages/sspTriggerMsgList.cpp 
    elements/messages/sspTriggerMsgList.h

    elements/players/sspChainPlayer.cpp
    elements/players/sspChainPlayer.h
    elements/players/sspConditionalPlayer.cpp 
    elements/players/sspConditionalPlayer.h
    elements/players/sspDistributionPlayer.cpp 
    elements/players/sspDistributionPlayer.h
    elements/players/sspIndexPlayer.cpp 
    elements/players/sspIndexPlayer.h
    elements/players/sspOSCPlayer.cpp 
    elements/players/sspOSCPlayer.h 
    elements/players/sspPlayers.cpp 
    elements/players/sspPlayers.h 
    elements/players/sspRandomPlayer.cpp 
    elements/players/sspRandomPlayer.h
    elements/players/sspSequentialPlayer.cpp 
    elements/players/sspSequentialPlayer.h
    elements/players/sspSilencePlayer.cpp 
    elements/players/sspSilencePlayer.h
    elements/players/sspSimultaneousPlayer.cpp 
    elements/players/sspSimultaneousPlayer.h

    elements/streams/sspAudioStream.cpp
    elements/streams/sspAudioStream.h
    elements/streams/sspStream.cpp 
    elements/streams/sspStream.h

    elements/strings/sspConditionalString.cpp
    elements/strings/sspConditionalString.h
    elements/strings/sspConcatString.cpp
    elements/strings/sspConcatString.h
    elements/strings/sspFileString.cpp 
    elements/strings/sspFileString.h 
    elements/strings/sspSelectString.cpp 
    elements/strings/sspSelectString.h
    elements/strings/sspSimpleString.h
    elements/strings/sspStrings.cpp 
    elements/strings/sspStrings.h

    elements/values/sspAddValue.cpp 
    elements/values/sspAddValue.h
    elements/values/sspBasicValue.h
    elements/values/sspConditionalValue.cpp 
    elements/values/sspConditionalValue.h
    elements/values/sspDateMap.cpp 
    elements/values/sspDateMap.h
    elements/values/sspLinearMap.cpp 
    elements/values/sspLinearMap.h
    elements/values/sspProductValue.cpp 
    elements/values/sspProductValue.h
    elements/values/sspRandomValue.cpp 
    elements/values/sspRandomValue.h
    elements/values/sspSecondsRun.cpp 
    elements/values/sspSecondsRun.h
    elements/values/sspTimeMap.cpp 
    elements/values/sspTimeMap.h
    elements/values/sspValueRange.cpp 
    elements/values/sspValueRange.h
    elements/values/sspValues.cpp 
    elements/values/sspValues.h

    sspDomainData.cpp 
    sspDomainData.h 
)

#target_link_libraries(domain-lib 
#    PUBLIC 
#    conditionals-lib 
#    inputs-lib
#    message-lib 
#    players-lib 
#    streams-lib 
#    strings-lib 
#    values-lib 
#)

# Boost serialization
find_package(Boost REQUIRED COMPONENTS serialization)
target_link_libraries(domain-lib PUBLIC Boost::serialization pacsdk)

