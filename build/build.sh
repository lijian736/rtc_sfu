#!/bin/bash
set -e

#delete the last generated files
ls | grep -v build.sh | grep -v build_grpc.sh | xargs rm -rf
rm -rf ../bin/*

#gRPC install dir
export GRPC_INSTALL_DIR=/home/lijian/grpc/install

#compile
cmake -DCMAKE_PREFIX_PATH=$GRPC_INSTALL_DIR ..
make

#copy files
cp -f ./src/rtc_sfu ../bin/rtc_sfu
#copy config files
cp -f ../resources/config.cfg ../bin/config.cfg

#chmod files
chmod +744 ../bin/rtc_sfu

echo "compile successful!!!!!!!!!!!!!!!!!!!!"