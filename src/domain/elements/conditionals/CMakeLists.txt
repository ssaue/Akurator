# CMakeLists.txt for conditionals library

add_library(conditionals-lib
    STATIC
    sspAnd.cpp 
    sspAnd.h
    sspBoolean.h
    sspConditionals.cpp 
    sspConditionals.h
    sspDateInterval.cpp 
    sspDateInterval.h
    sspDayOfWeek.cpp 
    sspDayOfWeek.h
    sspIsPlaying.cpp 
    sspIsPlaying.h
    sspMinuteCompare.cpp 
    sspMinuteCompare.h
    sspNot.cpp 
    sspNot.h
    sspOr.cpp 
    sspOr.h
    sspTimeCompare.cpp 
    sspTimeCompare.h
    sspTimeInterval.cpp 
    sspTimeInterval.h
    sspTrigger.cpp 
    sspTrigger.h
    sspValueCompare.cpp 
    sspValueCompare.h
    sspValueInRange.cpp 
    sspValueInRange.h
)

target_link_libraries(conditionals-lib PUBLIC domain-core-lib)
