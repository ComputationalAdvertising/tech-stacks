#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

PROTOBUF_HOME=$SCRIPT_DIR/third_party/deps/protobuf 
if [ ! -d $PROTOBUF_HOME ]; then
  echo "$PROTOBUF_HOME not exist. install it."
  sh $SCRIPT_DIR/tools_protobuf/install-dependencies.sh
fi

protoc=$PROTOBUF_HOME/bin/protoc
export LD_LIBRARY_PATH=$PROTOBUF_HOME/lib
export DYLD_LIBRARY_PATH=$PROTOBUF_HOME/lib

cpp_out=$SCRIPT_DIR/gen-pb/cpp
java_out=$SCRIPT_DIR/gen-pb/java
python_out=$SCRIPT_DIR/gen-pb/python

mkdir -p $cpp_out || true
mkdir -p $java_out || true
mkdir -p $python_out || true

# compile proto recursive
function compile_proto_recursive() {
  if [ $# -lt 1 ]; then
    echo "You need to specify 'dir' args."
    exit 1
  fi
  for elem in `ls $1`
  do 
    dir_or_file=$1/$elem 
    postfix=".proto"
    if [ -d $dir_or_file ]; then
      compile_proto_recursive $dir_or_file
    fi
    
    if [[ "${dir_or_file:0-6}" == "$postfix" ]]; then 
      $protoc -I=$1 --cpp_out=$cpp_out --java_out=$java_out --python_out=$python_out $dir_or_file
    fi
  done
}

compile_proto_recursive $SCRIPT_DIR/proto

echo "======== ${BASH_SOURCE[0]} ========"
