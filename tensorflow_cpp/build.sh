#!/bin/bash 

SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)
PROJECT_DIR=$SCRIPT_DIR

if [ ! -d ${PROJECT_DIR}/build ]; then 
  mkdir -p $PROJECT_DIR/build
fi

source $PROJECT_DIR/conf/tensorflow.conf
echo "TENSORFLOW_HOME: $TENSORFLOW_HOME"
export TENSORFLOW_HOME

cd $PROJECT_DIR/build
cmake -D CMAKE_C_COMPILER=`which gcc` -D CMAKE_CXX_COMPILER=`which g++` $PROJECT_DIR

make

echo "======== ${BASH_SOURCE[0]} ========"
