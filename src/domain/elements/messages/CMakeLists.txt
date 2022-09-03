# CMakeLists.txt for message library

add_library(message-lib
    STATIC
    sspConditionalMsgList.cpp
    sspConditionalMsgList.h
    sspMessage.cpp 
    sspMessage.h
    sspMessageHandler.h
    sspMessageList.cpp 
    sspMessageList.h
    sspMessageWithReceiver.cpp 
    sspMessageWithReceiver.h
    sspTimeTriggerMsgList.cpp 
    sspTimeTriggerMsgList.h
    sspTriggerMsgList.cpp 
    sspTriggerMsgList.h
)

target_link_libraries(message-lib PUBLIC domain-core-lib)
