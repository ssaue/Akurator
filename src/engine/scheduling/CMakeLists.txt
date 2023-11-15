# CMakeLists.txt for scheduling library

add_library(scheduling-lib
    STATIC
    sspSchedulePlayTask.cpp 
    sspSchedulePlayTask.h 
    sspSchedulePlayTaskList.cpp 
    sspSchedulePlayTaskList.h 
    sspScheduler.cpp 
    sspScheduler.h 
    sspScheduleTask.h 
    sspSilenceTask.cpp 
    sspSilenceTask.h 
    sspTaskQueue.cpp 
    sspTaskQueue.h 
)

# Boost serialization
find_package(Boost REQUIRED COMPONENTS serialization)
target_link_libraries(scheduling-lib PUBLIC Boost::serialization)

