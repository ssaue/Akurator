# CMakeLists.txt for access library

add_library(access-lib
    STATIC
    sspWatchDog.h 
    sspLogging.cpp 
    sspLogging.h 
)

add_subdirectory(midi)
add_subdirectory(osc)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(access-lib PUBLIC spdlog::spdlog)
target_link_libraries(access-lib PRIVATE osc-access-lib midi-access-lib)
