#!/bin/bash

SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd) 
THIRD_PARTY_DIR=$SCRIPT_DIR/third_party

if [ ! -d $THIRD_PARTY_DIR ]; then
  mkdir -p $THIRD_PARTY_DIR 
fi 
cd $THIRD_PARTY_DIR 

# gflags
url=https://github.com/gflags/gflags.git 
git clone $url
mkdir -p gflags/build_gflags || echo "build_gflags exists"
cd gflags/build_gflags 
export CXXFLAGS="-fPIC" && cmake .. -DCMAKE_INSTALL_PREFIX=$THIRD_PARTY_DIR/deps && make VERBOSE=1 && make install

echo "======== ${BASH_SOURCE[0]} ========"
