set (SRC_LIST ./main_grpc.cpp)

add_subdirectory(common)
add_subdirectory(io)
add_subdirectory(application)
add_subdirectory(grpc_service)

include_directories(
    ${PROJECT_SOURCE_DIR}/src/common
    ${PROJECT_SOURCE_DIR}/src/io
    ${PROJECT_SOURCE_DIR}/src/application
    ${PROJECT_SOURCE_DIR}/src/grpc_gen
    ${PROJECT_SOURCE_DIR}/src/grpc_service
)

add_executable(rtc_sfu ${SRC_LIST})

target_link_libraries(rtc_sfu
    common
    io
    application
    rtc_grpc_service
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
)