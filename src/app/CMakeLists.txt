# CMakeLists.txt for app library

target_sources(Akurator
PRIVATE
    components/MainComponent.cpp 
    components/MainComponent.h 
    components/MainWindow.cpp 
    components/MainWindow.h 
    components/sspDomainListboxModel.cpp 
    components/sspDomainListboxModel.h 
    components/sspDomainPage.cpp 
    components/sspDomainPage.h 
    components/sspRunPage.cpp 
    components/sspRunPage.h 
    components/sspSettingsPage.cpp 
    components/sspSettingsPage.h 
    components/sspTabbedComponent.cpp 
    components/sspTabbedComponent.h 
    components/sspToolbarFactory.cpp 
    components/sspToolbarFactory.h 
    main.cpp 
    sspAkuratorApplication.cpp 
    sspAkuratorApplication.h 
    sspCommandIDs.h 
    sspDefines.h 
)

target_link_libraries(Akurator PUBLIC domain-lib engine-lib access-lib project-lib)
