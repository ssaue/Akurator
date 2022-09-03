# CMakeLists.txt for domain library

add_subdirectory(core)
add_subdirectory(elements)

add_library(domain-lib
    STATIC
    sspDomainData.cpp 
    sspDomainData.h 
)

target_link_libraries(domain-lib 
    PUBLIC 
    conditionals-lib 
    inputs-lib
    message-lib 
    players-lib 
    streams-lib 
    strings-lib 
    values-lib 
)
