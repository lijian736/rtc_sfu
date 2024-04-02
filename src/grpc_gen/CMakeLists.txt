#cmake最低版本
cmake_minimum_required (VERSION 3.5.1)

#gRPC的通用配置信息
include(../../thirdparty/cmake/grpc_common.cmake)

# Protocol文件，本项目使用的gRPC服务接口定义
# proto文件
get_filename_component(rtc_proto "../../resources/protos/rtc_services.proto" ABSOLUTE)
# proto文件路径
get_filename_component(rtc_proto_path "${rtc_proto}" PATH)

message(STATUS "------The rtc_proto is ${rtc_proto}")
message(STATUS "------The rtc_proto_path is ${rtc_proto_path}")

# 设置gRPC自动生成的C++文件的名称
set(rtc_proto_srcs "rtc_services.pb.cc")
set(rtc_proto_hdrs "rtc_services.pb.h")
set(rtc_grpc_srcs "rtc_services.grpc.pb.cc")
set(rtc_grpc_hdrs "rtc_services.grpc.pb.h")

message(STATUS "------The _PROTOBUF_PROTOC: ${_PROTOBUF_PROTOC}")
message(STATUS "------The _GRPC_CPP_PLUGIN_EXECUTABLE: ${_GRPC_CPP_PLUGIN_EXECUTABLE}")

#生成gRPC文件
add_custom_command(
      OUTPUT "${rtc_proto_srcs}" "${rtc_proto_hdrs}" "${rtc_grpc_srcs}" "${rtc_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "./"
        --cpp_out "./"
        -I "${rtc_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${rtc_proto}"
      DEPENDS "${rtc_proto}")

# 生成rtc_sfu_grpc库
add_library(rtc_sfu_grpc
  ${rtc_grpc_srcs}
  ${rtc_grpc_hdrs}
  ${rtc_proto_srcs}
  ${rtc_proto_hdrs})

target_link_libraries(rtc_sfu_grpc
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})