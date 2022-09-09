# CMakeLists.txt for project libraries

# TODO: Find a better way to include specific projects

add_library(project-lib
    STATIC
    Bekkelaget.cpp 
    Bekkelaget.h 
    BlankProject.cpp 
    BlankProject.h 
    Storedal.cpp 
    Storedal.h 
)

target_link_libraries(project-lib PRIVATE domain-lib)
