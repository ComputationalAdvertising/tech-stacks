#!/bin/bash 

set -o pipefail
set -o errexit

SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)
PROJECT_DIR=$SCRIPT_DIR

source $PROJECT_DIR/conf/env_path.conf 

if [[ $PROTOBUF_HOME == "" ]]; then 
  echo "ERROR: 'PROTOBUF_HOME' is empty in conf/env_path.conf. check PROTOBUF_HOME. exit 1"
  exit 1
else
  if [[ ! -d $PROTOBUF_HOME ]]; then 
    echo "ERROR: $PROTOBUF_HOME not exists! exit 1"
    exit 1
  fi
fi 

if [[ $GRPC_HOME == "" ]]; then 
  echo "WARNING: 'GRPC_HOME' is empty in conf/env_path.conf. use default path: 'third_party/deps/grpc'"
  GRPC_HOME=$PROJECT_DIR/third_party/deps/grpc 
else
  if [[ ! -d ${GRPC_HOME} ]]; then
    echo "WARNING: $GRPC_HOME not exists! exit 1"
    exit 1
  fi
fi


# Compile IDL
if [ ! -d $SCRIPT_DIR/gen-pb/cpp ]; then
  sh $SCRIPT_DIR/compile-pb-with-grpc.sh
fi

export PROTOBUF_HOME=$PROTOBUF_HOME
export GRPC_HOME=$GRPC_HOME


mkdir -p $PROJECT_DIR/build || echo "build exist!"
cd $PROJECT_DIR/build

cmake -DCMAKE_C_COMPILER=`which gcc` -DCMAKE_CXX_COMPILER=`which g++` $PROJECT_DIR

make

echo "======== ${BASH_SOURCE[0]} ========"
