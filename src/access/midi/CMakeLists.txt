# CMakeLists.txt for midi-access library

add_library(midi-access-lib
    STATIC
    sspMidiConsole.cpp 
    sspMidiConsole.h 
    sspMidiConsoleImpl.cpp 
    sspMidiConsoleImpl.h 
    sspMidiDevices.cpp 
    sspMidiDevices.h 
    sspStreamChannel.cpp 
    sspStreamChannel.h 
)

# Juce includes
target_compile_definitions(midi-access-lib PRIVATE JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1)
target_include_directories(midi-access-lib PRIVATE "${JUCE_SOURCE_DIR}/modules")

target_link_libraries(midi-access-lib PRIVATE juce::juce_audio_devices)
