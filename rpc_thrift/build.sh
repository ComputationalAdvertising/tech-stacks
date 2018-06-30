#!/bin/bash 

set -o pipefail
set -o errexit

SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)
PROJECT_DIR=$SCRIPT_DIR

# Compile IDL
if [ ! -d $SCRIPT_DIR/learning/openmit-idl/gen-cpp ]; then
  sh $SCRIPT_DIR/compile-thrift.sh 
fi
sh $SCRIPT_DIR/../tools_protobuf/compile-pb.sh

#export THRIFT_HOME=$PROJECT_DIR/third_party/deps/thrift
export THRIFT_HOME=$HOME/local
export PROTOBUF_HOME=$PROJECT_DIR/../tools_protobuf/third_party/deps/protobuf  

cp -r $SCRIPT_DIR/../tools_protobuf/gen-pb $SCRIPT_DIR

if [ ! -d ${PROJECT_DIR}/build ]; then mkdir -p $PROJECT_DIR/build; fi
cd $PROJECT_DIR/build

cmake -D CMAKE_C_COMPILER=`which gcc` -D CMAKE_CXX_COMPILER=`which g++` $PROJECT_DIR

make

echo "======== ${BASH_SOURCE[0]} ========"
