add_library(pacsdk INTERFACE)
target_include_directories(pacsdk INTERFACE .)

set(PACSDK_LIBPATH "${CMAKE_CURRENT_SOURCE_DIR}")

if (WIN32)
    set(PACSDK_LIBRARY "${PACSDK_LIBPATH}/pacsdk.lib")
    set_property(GLOBAL APPEND PROPERTY DLLS_TO_COPY "${PACSDK_LIBPATH}/pacsdk.dll")
else()
#    set(ONNXRUNTIME_LIBRARY "${ONNXRUNTIME_LIBPATH}/${CMAKE_SYSTEM_PROCESSOR}/libonnxruntime.so.1.11.1")
#    install(FILES ${ONNXRUNTIME_LIBRARY} TYPE LIB)
endif()

target_link_libraries(pacsdk INTERFACE ${PACSDK_LIBRARY})
