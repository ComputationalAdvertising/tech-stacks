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

if [ ! -d gflags/build_gflags ]; then
  mkdir -p gflags/build_gflags || echo "build_gflags exists!"
fi
cd gflags/build_gflags && cmake .. -DCMAKE_INSTALL_PREFIX=$THIRD_PARTY_DIR/deps && make && make install

echo "======== ${BASH_SOURCE[0]} ========"
