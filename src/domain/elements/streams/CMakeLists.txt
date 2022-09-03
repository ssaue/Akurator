# CMakeLists.txt for streams library

add_library(streams-lib
    STATIC
    sspAudioStream.cpp
    sspAudioStream.h
    sspStream.cpp 
    sspStream.h
)

target_link_libraries(streams-lib PUBLIC domain-core-lib)
