# add source files in sub-directories
#add_subdirectory(app)
#add_subdirectory(access)
#add_subdirectory(domain)
#add_subdirectory(engine)
#add_subdirectory(projects)

target_sources(Akurator
PRIVATE
    app/components/MainComponent.cpp 
    app/components/MainComponent.h 
    app/components/MainWindow.cpp 
    app/components/MainWindow.h 
    app/components/sspDomainListboxModel.cpp 
    app/components/sspDomainListboxModel.h 
    app/components/sspDomainPage.cpp 
    app/components/sspDomainPage.h 
    app/components/sspRunPage.cpp 
    app/components/sspRunPage.h 
    app/components/sspSettingsPage.cpp 
    app/components/sspSettingsPage.h 
    app/components/sspTabbedComponent.cpp 
    app/components/sspTabbedComponent.h 
    app/components/sspToolbarFactory.cpp 
    app/components/sspToolbarFactory.h 

    app/main.cpp 
    app/sspAkuratorApplication.cpp 
    app/sspAkuratorApplication.h 
    app/sspCommandIDs.h 
    app/sspDefines.h 

    access/sspWatchDog.h 
    access/sspLogging.h 

    access/osc/sspOscConsole.cpp 
    access/osc/sspOscConsole.h 
    access/osc/sspOscConsoleImpl.cpp 
    access/osc/sspOscConsoleImpl.h 
    access/osc/sspOscSendChannel.cpp 
    access/osc/sspOscSendChannel.h
    access/osc/sspOscSender.cpp
    access/osc/sspOscSender.h

    domain/core/sspDomainElement.h
    domain/core/sspDomainPool.h
    domain/core/sspDomainPool.cpp
    domain/core/sspDomainPrimitives.h
    domain/core/sspDomainPrimitives.cpp
    domain/core/sspInput.h
    domain/core/sspInput.cpp
    domain/core/sspPlayer.h
    domain/core/sspPlayer.cpp
    domain/core/sspPlayTask.h
    domain/core/sspPlayTask.cpp
    domain/core/sspSharedVector.h
    domain/core/sspTimeline.h
    domain/core/sspTimeline.cpp

    domain/elements/conditionals/sspAnd.cpp 
    domain/elements/conditionals/sspAnd.h
    domain/elements/conditionals/sspBoolean.h
    domain/elements/conditionals/sspConditionals.cpp 
    domain/elements/conditionals/sspConditionals.h
    domain/elements/conditionals/sspDateInterval.cpp 
    domain/elements/conditionals/sspDateInterval.h
    domain/elements/conditionals/sspDayOfWeek.cpp 
    domain/elements/conditionals/sspDayOfWeek.h
    domain/elements/conditionals/sspIsPlaying.cpp 
    domain/elements/conditionals/sspIsPlaying.h
    domain/elements/conditionals/sspMinuteCompare.cpp 
    domain/elements/conditionals/sspMinuteCompare.h
    domain/elements/conditionals/sspNot.cpp 
    domain/elements/conditionals/sspNot.h
    domain/elements/conditionals/sspOr.cpp 
    domain/elements/conditionals/sspOr.h
    domain/elements/conditionals/sspTimeCompare.cpp 
    domain/elements/conditionals/sspTimeCompare.h
    domain/elements/conditionals/sspTimeInterval.cpp 
    domain/elements/conditionals/sspTimeInterval.h
    domain/elements/conditionals/sspTrigger.cpp 
    domain/elements/conditionals/sspTrigger.h
    domain/elements/conditionals/sspValueCompare.cpp 
    domain/elements/conditionals/sspValueCompare.h
    domain/elements/conditionals/sspValueInRange.cpp 
    domain/elements/conditionals/sspValueInRange.h

    domain/elements/inputs/sspICPanalogInput.cpp
    domain/elements/inputs/sspICPanalogInput.h
    domain/elements/inputs/sspICPdigitalInput.cpp
    domain/elements/inputs/sspICPdigitalInput.h
    domain/elements/inputs/sspICPinput.cpp 
    domain/elements/inputs/sspICPinput.h
    domain/elements/inputs/sspInputs.cpp 
    domain/elements/inputs/sspInputs.h 

    domain/elements/messages/sspConditionalMsgList.cpp
    domain/elements/messages/sspConditionalMsgList.h
    domain/elements/messages/sspMessage.cpp 
    domain/elements/messages/sspMessage.h
    domain/elements/messages/sspMessageHandler.h
    domain/elements/messages/sspMessageList.cpp 
    domain/elements/messages/sspMessageList.h
    domain/elements/messages/sspMessageWithReceiver.cpp 
    domain/elements/messages/sspMessageWithReceiver.h
    domain/elements/messages/sspTimeTriggerMsgList.cpp 
    domain/elements/messages/sspTimeTriggerMsgList.h
    domain/elements/messages/sspTriggerMsgList.cpp 
    domain/elements/messages/sspTriggerMsgList.h

    domain/elements/players/sspChainPlayer.cpp
    domain/elements/players/sspChainPlayer.h
    domain/elements/players/sspConditionalPlayer.cpp 
    domain/elements/players/sspConditionalPlayer.h
    domain/elements/players/sspDistributionPlayer.cpp 
    domain/elements/players/sspDistributionPlayer.h
    domain/elements/players/sspIndexPlayer.cpp 
    domain/elements/players/sspIndexPlayer.h
    domain/elements/players/sspOSCPlayer.cpp 
    domain/elements/players/sspOSCPlayer.h 
    domain/elements/players/sspPlayers.cpp 
    domain/elements/players/sspPlayers.h 
    domain/elements/players/sspRandomPlayer.cpp 
    domain/elements/players/sspRandomPlayer.h
    domain/elements/players/sspSequentialPlayer.cpp 
    domain/elements/players/sspSequentialPlayer.h
    domain/elements/players/sspSilencePlayer.cpp 
    domain/elements/players/sspSilencePlayer.h
    domain/elements/players/sspSimultaneousPlayer.cpp 
    domain/elements/players/sspSimultaneousPlayer.h

    domain/elements/streams/sspAudioStream.cpp
    domain/elements/streams/sspAudioStream.h
    domain/elements/streams/sspStream.cpp 
    domain/elements/streams/sspStream.h

    domain/elements/strings/sspConditionalString.cpp
    domain/elements/strings/sspConditionalString.h
    domain/elements/strings/sspConcatString.cpp
    domain/elements/strings/sspConcatString.h
    domain/elements/strings/sspFileString.cpp 
    domain/elements/strings/sspFileString.h 
    domain/elements/strings/sspSelectString.cpp 
    domain/elements/strings/sspSelectString.h
    domain/elements/strings/sspSimpleString.h
    domain/elements/strings/sspStrings.cpp 
    domain/elements/strings/sspStrings.h

    domain/elements/values/sspAddValue.cpp 
    domain/elements/values/sspAddValue.h
    domain/elements/values/sspBasicValue.h
    domain/elements/values/sspConditionalValue.cpp 
    domain/elements/values/sspConditionalValue.h
    domain/elements/values/sspDateMap.cpp 
    domain/elements/values/sspDateMap.h
    domain/elements/values/sspLinearMap.cpp 
    domain/elements/values/sspLinearMap.h
    domain/elements/values/sspProductValue.cpp 
    domain/elements/values/sspProductValue.h
    domain/elements/values/sspRandomValue.cpp 
    domain/elements/values/sspRandomValue.h
    domain/elements/values/sspSecondsRun.cpp 
    domain/elements/values/sspSecondsRun.h
    domain/elements/values/sspTimeMap.cpp 
    domain/elements/values/sspTimeMap.h
    domain/elements/values/sspValueRange.cpp 
    domain/elements/values/sspValueRange.h
    domain/elements/values/sspValues.cpp 
    domain/elements/values/sspValues.h

    domain/sspDomainData.cpp 
    domain/sspDomainData.h 

    engine/sspExecutionState.cpp 
    engine/sspExecutionState.h 
    engine/sspExecutiveManager.cpp 
    engine/sspExecutiveManager.h 
    engine/sspFinishedResponder.h 
    engine/sspInputManager.cpp 
    engine/sspInputManager.h 
    engine/sspPlayManager.cpp 
    engine/sspPlayManager.h 
    engine/sspResetManager.cpp 
    engine/sspResetManager.h 
    engine/sspSendChannel.h 
    engine/sspStreamBus.cpp 
    engine/sspStreamBus.h 
    engine/sspTimeUpdater.h 

    engine/scheduling/sspSchedulePlayTask.cpp 
    engine/scheduling/sspSchedulePlayTask.h 
    engine/scheduling/sspSchedulePlayTaskList.cpp 
    engine/scheduling/sspSchedulePlayTaskList.h 
    engine/scheduling/sspScheduler.cpp 
    engine/scheduling/sspScheduler.h 
    engine/scheduling/sspScheduleTask.h 
    engine/scheduling/sspSilenceTask.cpp 
    engine/scheduling/sspSilenceTask.h 
    engine/scheduling/sspTaskQueue.cpp 
    engine/scheduling/sspTaskQueue.h 

    projects/Bekkelaget.cpp 
    projects/Bekkelaget.h 
    projects/BlankProject.cpp 
    projects/BlankProject.h 
    projects/Storedal.cpp 
    projects/Storedal.h 
)

# Boost logging
find_package(Boost REQUIRED COMPONENTS log serialization)
target_link_libraries(Akurator PRIVATE Boost::log Boost::serialization serial-port-lib)

target_compile_definitions(Akurator PRIVATE JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1)
target_include_directories(Akurator PRIVATE "${JUCE_SOURCE_DIR}/modules")
