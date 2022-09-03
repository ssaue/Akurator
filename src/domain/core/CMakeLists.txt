# CMakeLists.txt for core library

add_library(domain-core-lib
    STATIC
    sspDomainElement.h
    sspDomainPool.h
    sspDomainPool.cpp
    sspDomainPrimitives.h
    sspDomainPrimitives.cpp
    sspInput.h
    sspInput.cpp
    sspPlayer.h
    sspPlayer.cpp
    sspPlayTask.h
    sspPlayTask.cpp
    sspSharedVector.h
    sspTimeline.h
    sspTimeline.cpp
)

# Boost serialization
find_package(Boost REQUIRED COMPONENTS serialization)
target_link_libraries(domain-core-lib PUBLIC Boost::serialization)

