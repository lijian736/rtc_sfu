#include <iostream>
#include <memory>
#include <string>
#include <time.h>

#include "media_rtc_server.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

int main(int argc, char** argv)
{
    std::string server_address("0.0.0.0:30002");

    MediaRTCServiceImpl service;

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

    builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_TIME_MS, 1000 * 10);
    builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_TIMEOUT_MS, 1000 * 25);
    builder.AddChannelArgument(GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS, 1);

    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);


    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    // the Wait() is blocked.
    server->Wait();

    std::cout << "Now start to shutdown the server" << std::endl;
    server->Shutdown();
    
    return 0;
}