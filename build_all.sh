#!/bin/bash 

#set -o pipefail
#set -o errexit

{
sh cpp_boost/install-dependencies.sh &
sh tools_gflags/install-dependencies.sh &
sh tools_glog/install-dependencies.sh &
sh tools_gtest/install-dependencies.sh &
sh tools_protobuf/install-dependencies.sh  & 
} 
wait 

{
sh rpc_grpc/install-dependencies.sh &
sh rpc_thrift/install-dependencies.sh &
} 
wait

sh rpc_muduo/install-dependencies.sh &
