add_library(serial-port-lib 
    AsyncSerial.h
    AsyncSerial.cpp
    CallbackAsyncSerial.h
    CallbackAsyncSerial.cpp
)

find_package(Boost REQUIRED)
target_link_libraries(serial-port-lib PUBLIC Boost::boost)
target_include_directories(serial-port-lib PUBLIC .)
