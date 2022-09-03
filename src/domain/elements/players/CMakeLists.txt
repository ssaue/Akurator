# CMakeLists.txt for players library

add_library(players-lib
    STATIC
    sspChainPlayer.cpp
    sspChainPlayer.h
    sspConditionalPlayer.cpp 
    sspConditionalPlayer.h
    sspDistributionPlayer.cpp 
    sspDistributionPlayer.h
    sspIndexPlayer.cpp 
    sspIndexPlayer.h
    sspOSCPlayer.cpp 
    sspOSCPlayer.h 
    sspPlayers.cpp 
    sspPlayers.h 
    sspRandomPlayer.cpp 
    sspRandomPlayer.h
    sspSequentialPlayer.cpp 
    sspSequentialPlayer.h
    sspSilencePlayer.cpp 
    sspSilencePlayer.h
    sspSimultaneousPlayer.cpp 
    sspSimultaneousPlayer.h
)

target_link_libraries(players-lib PUBLIC domain-core-lib)
