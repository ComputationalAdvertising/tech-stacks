#!/bin/bash

SCRIPT_DIR=$(cd "$(dirname ${BASH_SOURCE[0]})" && pwd)
PROJECT_DIR=$SCRIPT_DIR

thrift_cpp_out=$PROJECT_DIR/learning

thrift="$PROJECT_DIR/third_party/deps/thrift/bin/thrift"

function compile_thrift() {
  target=$1
  if [ -d $target ]; then
    for file in `ls $target`
    do 
      if [ ${file:0-7} == ".thrift" ]; then
        $thrift -r --gen cpp -o $thrift_cpp_out $target/$file
      fi
    done
  fi
}

compile_thrift $SCRIPT_DIR/learning/thrift
