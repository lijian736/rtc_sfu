#!/bin/bash
set -e

#delete the last generated gRPC files
ls ../src/grpc_gen/* | grep -v CMakeLists.txt | xargs rm -rf
ls | grep -v build.sh | grep -v build_grpc.sh | xargs rm -rf

#the gRPC install dir
export GRPC_INSTALL_DIR=/home/lijian/grpc/install

# generate gRPC C++ codes by .proto files
cmake -DCMAKE_PREFIX_PATH=$GRPC_INSTALL_DIR ../src/grpc_gen
make

#Copy files
cp -f ./rtc_services.pb.h ../src/grpc_gen/rtc_services.pb.h
cp -f ./rtc_services.pb.cc ../src/grpc_gen/rtc_services.pb.cc
cp -f ./rtc_services.grpc.pb.h ../src/grpc_gen/rtc_services.grpc.pb.h
cp -f ./rtc_services.grpc.pb.cc ../src/grpc_gen/rtc_services.grpc.pb.cc

echo "Generate gRPC C++ files successful!!!!!!!!!!!!!!!!!!!!"