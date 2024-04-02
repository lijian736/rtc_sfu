#ifndef _H_MEDIA_RTC_SERVER_H_
#define _H_MEDIA_RTC_SERVER_H_

#include <memory>
#include <string>

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "rtc_services.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::ServerWriter;
using grpc::ServerReader;
using grpc::ServerReaderWriter;

using mediaservice::MediaRTC;
using mediaservice::RecvAddrRequest;
using mediaservice::IPv4Addr;
using mediaservice::RecvAddrResponse;

class MediaRTCServiceImpl final : public MediaRTC::Service 
{
public:
    // Get the receive address for udp data
    virtual Status get_recv_address(ServerContext* context, const RecvAddrRequest* request, 
        RecvAddrResponse* response) override;

};
#endif