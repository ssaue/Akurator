# CMakeLists.txt for access library

add_library(access-lib
    STATIC
    sspWatchDog.h 
    sspLogging.cpp 
    sspLogging.h 
)

add_subdirectory(osc)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(access-lib PRIVATE spdlog::spdlog_header_only osc-access-lib)
