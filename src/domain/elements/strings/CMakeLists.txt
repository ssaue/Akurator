# CMakeLists.txt for strings library

add_library(strings-lib
    STATIC
    sspConcatString.cpp
    sspConcatString.h
    sspFileString.cpp 
    sspFileString.h 
    sspSelectString.cpp 
    sspSelectString.h
    sspSimpleString.h
    sspStrings.cpp 
    sspStrings.h
)

target_link_libraries(strings-lib PUBLIC domain-core-lib)
