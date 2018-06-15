#!/bin/bash -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

source $SCRIPT_DIR/conf/env_path.conf

# protobuf
if [[ $PROTOBUF_HOME == "" ]]; then 
  echo "ERROR: 'PROTOBUF_HOME' is empty in conf/env_path.conf. check PROTOBUF_HOME. exit 1"
  exit 1
else
  if [[ ! -d $PROTOBUF_HOME ]]; then 
    echo "ERROR: $PROTOBUF_HOME not exists! exit 1"
    exit 1
  fi
fi 
export PATH=$PROTOBUF_HOME/bin:$PATH 
export LD_LIBRARY_PATH=$PROTOBUF_HOME/lib:$LD_LIBRARY_PATH 
export DYLD_LIBRARY_PATH=$PROTOBUF_HOME/lib:$DYLD_LIBRARY_PATH 
protoc=`which protoc`

# grpc cpp plugin
if [[ $GRPC_HOME == "" ]]; then 
  echo "WARNING: 'GRPC_HOME' is empty in conf/env_path.conf. use default path: 'third_party/deps/grpc'"
  GRPC_HOME=$SCRIPT_DIR/third_party/deps/grpc 
else
  if [[ ! -d ${GRPC_HOME} ]]; then
    echo "WARNING: $GRPC_HOME not exists! exit 1"
    exit 1
  fi
fi
export PATH=$GRPC_HOME/bin:$PATH 
export LD_LIBRARY_PATH=$GRPC_HOME/lib:$LD_LIBRARY_PATH 
export DYLD_LIBRARY_PATH=$GRPC_HOME/lib:$DYLD_LIBRARY_PATH 
grpc_cpp_plugin=`which grpc_cpp_plugin` 

# install target
pb_prefix=$SCRIPT_DIR/gen-pb/cpp 
mkdir -p $pb_prefix || echo "$pb_prefix exists!"

# compile proto recursive
function compile_pb_with_grpc_recursive() {
  if [ $# -lt 1 ]; then
    echo "You need to specify 'dir' args."
    exit 1
  fi
  for elem in `ls $1`
  do 
    dir_or_file=$1/$elem 
    postfix=".proto"
    if [ -d $dir_or_file ]; then
      compile_pb_with_grpc_recursive $dir_or_file
    fi
    
    if [[ "${dir_or_file: -6}" == "$postfix" ]]; then 
      $protoc -I=$1 --cpp_out=$pb_prefix --grpc_out=$pb_prefix --plugin=protoc-gen-grpc=$grpc_cpp_plugin $dir_or_file
    fi
  done
}

# compile
compile_pb_with_grpc_recursive $SCRIPT_DIR/proto

echo "======== ${BASH_SOURCE[0]} ========"
