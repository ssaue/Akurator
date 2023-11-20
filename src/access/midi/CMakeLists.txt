# CMakeLists.txt for midi-access library

add_library(midi-access-lib
    STATIC
    sspMidiConsole.cpp 
    sspMidiConsole.h 
    sspMidiConsoleImpl.cpp 
    sspMidiConsoleImpl.h 
    sspMidiDevices.cpp 
    sspMidiDevices.h 
    sspMidiSendChannel.cpp 
    sspMidiSendChannel.h 
)

# Boost serialization
find_package(Boost REQUIRED COMPONENTS serialization)
target_link_libraries(midi-access-lib PRIVATE Boost::serialization juce::juce_audio_devices)

# Juce includes
target_compile_definitions(midi-access-lib PRIVATE JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1)
target_include_directories(midi-access-lib PRIVATE "${JUCE_SOURCE_DIR}/modules")
