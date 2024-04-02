set (DIR_LIB_SRCS 
    ../grpc_gen/rtc_services.pb.cc
    ../grpc_gen/rtc_services.grpc.pb.cc
    ./media_rtc_server.cpp
)

#gRPC的通用配置信息
include(../../thirdparty/cmake/grpc_common.cmake)

include_directories(
    ${PROJECT_SOURCE_DIR}/src/grpc_gen
)

add_library(rtc_grpc_service ${DIR_LIB_SRCS})

target_link_libraries(rtc_grpc_service
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
)