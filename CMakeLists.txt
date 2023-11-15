# global options and variables
cmake_minimum_required(VERSION 3.20)

set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Default build type: Release")

# set the name of the project
project(akurator VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(Boost_NO_WARN_NEW_VERSIONS 1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (WIN32)
    add_compile_definitions(_WIN32_WINNT=0X0A00)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /permissive-")
endif()

#add_subdirectory(vendor EXCLUDE_FROM_ALL)
add_subdirectory(vendor)

juce_add_gui_app(Akurator
    # VERSION ...                       # Set this if the app version is different to the project version
    # ICON_BIG ...                      # ICON_* arguments specify a path to an image file to use as an icon
    # ICON_SMALL ...
    # DOCUMENT_EXTENSIONS ...           # Specify file extensions that should be associated with this app
    # COMPANY_NAME ...                  # Specify the name of the app's author
    PRODUCT_NAME "Akurator")     # The name of the final executable, which can differ from the target name


juce_generate_juce_header(Akurator)

# Include paths needed by both src and test files
include_directories(src)

target_compile_definitions(Akurator
    PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
	  JUCE_MODAL_LOOPS_PERMITTED=1
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:Akurator,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:Akurator,JUCE_VERSION>")

juce_add_binary_data(AkuratorData
	SOURCES 
	assets/document-new.svg
	assets/document-save.svg
	assets/document-save-as.svg
	assets/edit-settings.svg
	assets/run-initialize.svg
	assets/run-start.svg
	assets/run-stop.svg
	assets/run-verify.svg
)


target_link_libraries(Akurator
    PRIVATE
        AkuratorData
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)


add_subdirectory(src)

