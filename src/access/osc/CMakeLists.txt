# CMakeLists.txt for osc-access library

add_library(osc-access-lib
    STATIC
    sspOscConsole.cpp 
    sspOscConsole.h 
    sspOscConsoleImpl.cpp 
    sspOscConsoleImpl.h 
    sspOscSendChannel.cpp 
    sspOscSendChannel.h
    sspOscSender.cpp
    sspOscSender.h
)

# Juce includes
target_compile_definitions(osc-access-lib PRIVATE JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1)
target_include_directories(osc-access-lib PRIVATE "${JUCE_SOURCE_DIR}/modules")

# Boost serialization
find_package(Boost REQUIRED COMPONENTS serialization)
target_link_libraries(osc-access-lib PRIVATE Boost::serialization juce::juce_osc)
