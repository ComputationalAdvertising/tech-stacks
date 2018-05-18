#!/bin/bash

SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd) 
THIRD_PARTY_DIR=$SCRIPT_DIR/third_party

url=https://github.com/gflags/gflags.git 

if [ ! -d $THIRD_PARTY_DIR ]; then
  mkdir -p $THIRD_PARTY_DIR 
fi 
cd $THIRD_PARTY_DIR 

git clone $url

if [ ! -d gflags/build ]; then
  mkdir -p gflags/build 
fi
cd gflags/build && cmake .. -DCMAKE_INSTALL_PREFIX=$THIRD_PARTY_DIR/deps && make && make install

echo "======== ${BASH_SOURCE[0]} ========"
