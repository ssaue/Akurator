# CMakeLists.txt for inputs library

add_library(inputs-lib
    STATIC
    sspICPanalogInput.cpp
    sspICPanalogInput.h
    sspICPinput.cpp 
    sspICPinput.h
    sspInputs.cpp 
    sspInputs.h 
)

target_link_libraries(inputs-lib PRIVATE domain-core-lib pacsdk)
