// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: rtc_services.proto

#include "rtc_services.pb.h"
#include "rtc_services.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace mediaservice {

static const char* MediaRTC_method_names[] = {
  "/mediaservice.MediaRTC/get_recv_address",
};

std::unique_ptr< MediaRTC::Stub> MediaRTC::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< MediaRTC::Stub> stub(new MediaRTC::Stub(channel, options));
  return stub;
}

MediaRTC::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_get_recv_address_(MediaRTC_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status MediaRTC::Stub::get_recv_address(::grpc::ClientContext* context, const ::mediaservice::RecvAddrRequest& request, ::mediaservice::RecvAddrResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::mediaservice::RecvAddrRequest, ::mediaservice::RecvAddrResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_get_recv_address_, context, request, response);
}

void MediaRTC::Stub::async::get_recv_address(::grpc::ClientContext* context, const ::mediaservice::RecvAddrRequest* request, ::mediaservice::RecvAddrResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::mediaservice::RecvAddrRequest, ::mediaservice::RecvAddrResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_get_recv_address_, context, request, response, std::move(f));
}

void MediaRTC::Stub::async::get_recv_address(::grpc::ClientContext* context, const ::mediaservice::RecvAddrRequest* request, ::mediaservice::RecvAddrResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_get_recv_address_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::mediaservice::RecvAddrResponse>* MediaRTC::Stub::PrepareAsyncget_recv_addressRaw(::grpc::ClientContext* context, const ::mediaservice::RecvAddrRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::mediaservice::RecvAddrResponse, ::mediaservice::RecvAddrRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_get_recv_address_, context, request);
}

::grpc::ClientAsyncResponseReader< ::mediaservice::RecvAddrResponse>* MediaRTC::Stub::Asyncget_recv_addressRaw(::grpc::ClientContext* context, const ::mediaservice::RecvAddrRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncget_recv_addressRaw(context, request, cq);
  result->StartCall();
  return result;
}

MediaRTC::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MediaRTC_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< MediaRTC::Service, ::mediaservice::RecvAddrRequest, ::mediaservice::RecvAddrResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](MediaRTC::Service* service,
             ::grpc::ServerContext* ctx,
             const ::mediaservice::RecvAddrRequest* req,
             ::mediaservice::RecvAddrResponse* resp) {
               return service->get_recv_address(ctx, req, resp);
             }, this)));
}

MediaRTC::Service::~Service() {
}

::grpc::Status MediaRTC::Service::get_recv_address(::grpc::ServerContext* context, const ::mediaservice::RecvAddrRequest* request, ::mediaservice::RecvAddrResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace mediaservice

