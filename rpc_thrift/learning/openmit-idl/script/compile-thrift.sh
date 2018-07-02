#!/bin/bash

SCRIPT_DIR=$(cd "$(dirname ${BASH_SOURCE[0]})" && pwd)
PROJECT_DIR=$SCRIPT_DIR/..

thrift_out_dir=$PROJECT_DIR/gen-thrift
mkdir -p $thrift_out_dir || echo "$thrift_out_dir exists!"

thrift=`which thrift`
if [[ "" == $thrift ]]; then
  thrift="$PROJECT_DIR/third_party/deps/thrift/bin/thrift"
fi

function compile_thrift() {
  target=$1
  if [ -d $target ]; then
    for file in `ls $target`
    do 
      if [ ${file:0-7} == ".thrift" ]; then
        #$thrift -r --gen cpp -o $thrift_out_dir $target/$file
        $thrift -r --gen cpp --gen py --gen java -o $thrift_out_dir $target/$file
      fi
    done
  fi
}

compile_thrift $PROJECT_DIR/thrift
