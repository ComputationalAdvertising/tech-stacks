#!/bin/bash

SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd) 
THIRD_PARTY_DIR=$SCRIPT_DIR/third_party

if [ ! -d $THIRD_PARTY_DIR ]; then
  mkdir -p $THIRD_PARTY_DIR 
fi 
cd $THIRD_PARTY_DIR 

# googletest
url=https://github.com/google/googletest.git
git clone $url

if [ ! -d googletest/build ]; then
  mkdir -p googletest/build 
fi
cd googletest/build 
cmake -D CMAKE_INSTALL_PREFIX=$THIRD_PARTY_DIR/deps -D CMAKE_C_COMPILER=`which gcc` -D CMAKE_CXX_COMPILER=`which g++` ..
make && make install

echo "======== ${BASH_SOURCE[0]} ========"
