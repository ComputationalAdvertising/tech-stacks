#!/bin/bash 

set -o pipefail
set -o errexit

SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)
PROJECT_DIR=$SCRIPT_DIR

# Compile IDL
sh $SCRIPT_DIR/script/compile-pb.sh
sh $SCRIPT_DIR/script/compile-thrift.sh

export THRIFT_HOME=$HOME/local
export PROTOBUF_HOME=$HOME/local


mkdir -p $PROJECT_DIR/build || echo "$PROJECT_DIR/build exists!"
cd $PROJECT_DIR/build

cmake -D CMAKE_C_COMPILER=`which gcc` -D CMAKE_CXX_COMPILER=`which g++` $PROJECT_DIR

make

echo "======== ${BASH_SOURCE[0]} ========"
