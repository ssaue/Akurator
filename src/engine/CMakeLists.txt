# CMakeLists.txt for engine library

add_subdirectory(scheduling)

add_library(engine-lib
    STATIC
    sspExecutionState.cpp 
    sspExecutionState.h 
    sspExecutiveManager.cpp 
    sspExecutiveManager.h 
    sspFinishedResponder.h 
    sspInputManager.cpp 
    sspInputManager.h 
    sspPlayManager.cpp 
    sspPlayManager.h 
    sspResetManager.cpp 
    sspResetManager.h 
    sspSendChannel.h 
    sspStreamBus.cpp 
    sspStreamBus.h 
    sspTimeUpdater.h 
)

target_link_libraries(engine-lib PRIVATE scheduling-lib)

# Juce includes
target_compile_definitions(engine-lib PRIVATE JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1)
target_include_directories(engine-lib PRIVATE "${JUCE_SOURCE_DIR}/modules")
