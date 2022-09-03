# CMakeLists.txt for access library

add_library(access-lib
    INTERFACE
    sspWatchDog.h 
    sspLogging.h 
)

add_subdirectory(osc)

# Boost serialization
find_package(Boost REQUIRED COMPONENTS log)
target_link_libraries(access-lib INTERFACE Boost::log osc-access-lib)