add_library(pacsdk INTERFACE)
target_include_directories(pacsdk INTERFACE .)

#set(ONNXRUNTIME_LIBPATH "${CMAKE_CURRENT_SOURCE_DIR}/lib")

#if (WIN32)
#    set(ONNXRUNTIME_LIBRARY "${ONNXRUNTIME_LIBPATH}/win-x64/onnxruntime.lib")
#    set_property(GLOBAL APPEND PROPERTY DLLS_TO_COPY "${ONNXRUNTIME_LIBPATH}/win-x64/onnxruntime.dll")
#else()
#    set(ONNXRUNTIME_LIBRARY "${ONNXRUNTIME_LIBPATH}/${CMAKE_SYSTEM_PROCESSOR}/libonnxruntime.so.1.11.1")
#    install(FILES ${ONNXRUNTIME_LIBRARY} TYPE LIB)
#endif()

#target_link_libraries(onnxruntime INTERFACE ${ONNXRUNTIME_LIBRARY})
