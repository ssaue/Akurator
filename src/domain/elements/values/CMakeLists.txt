# CMakeLists.txt for values library

add_library(values-lib
    STATIC
    sspAddValue.cpp 
    sspAddValue.h
    sspBasicValue.h
    sspConditionalValue.cpp 
    sspConditionalValue.h
    sspDateMap.cpp 
    sspDateMap.h
    sspLinearMap.cpp 
    sspLinearMap.h
    sspProductValue.cpp 
    sspProductValue.h
    sspRandomValue.cpp 
    sspRandomValue.h
    sspSecondsRun.cpp 
    sspSecondsRun.h
    sspTimeMap.cpp 
    sspTimeMap.h
    sspValueRange.cpp 
    sspValueRange.h
    sspValues.cpp 
    sspValues.h
)

target_link_libraries(values-lib PUBLIC domain-core-lib)
