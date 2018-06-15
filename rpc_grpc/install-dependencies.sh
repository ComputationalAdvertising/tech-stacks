#!/bin/bash -e

#=================================#
# 1. grpc-master
#=================================#

set -o pipefail
set -o errexit

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

mkdir -p third_party || echo "third_party has exists!"

##################################
# https://github.com/grpc/grpc/blob/master/INSTALL.md
function install_grpc() {
  cd $SCRIPT_DIR/third_party 
  git clone -b $(curl -L https://grpc.io/release) https://github.com/grpc/grpc 
  cd grpc 
  git submodule update --init
  
  install_dir=$SCRIPT_DIR/third_party/deps/grpc 
  mkdir -p $install_dir || echo "deps/grpc exists!"
  make && make install prefix=$install_dir 

  # drop 
  if [ $? -eq 0 ]; then 
    echo "success to build grpc. drop raw package."
    rm -rf $SCRIPT_DIR/third_party/grpc 
  else
    echo "failed to build grpc."
  fi
}

##################################
# 1. grpc
install_grpc

echo "======== ${BASH_SOURCE[0]} ========"
