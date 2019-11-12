#!/bin/bash -e

#=================================#
# 1. muduo-1.1.0 
# 2. gperftools-2.7
#=================================#

set -o pipefail
set -o errexit

export LD_LIBRARY_PATH="${HOME}/.openmit_deps/lib:$LD_LIBRARY_PATH"
export CPLUS_INCLUDE_PATH="$HOME/.openmit_deps/include:$CPLUS_INCLUDE_PATH"
export PATH=$HOME/.openmit_deps/bin:$PATH 
export Protobuf_LIBRARIES=$HOME/.openmi_deps/lib
export Protobuf_INCLUDE_DIR=$HOME/.openmi_deps/include

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
mkdir -p $SCRIPT_DIR/third_party || echo "third_party has exists!"

##################################
function install_muduo() {
  cd $SCRIPT_DIR/third_party
  version=1.1.0
  url="https://github.com/chenshuo/muduo/archive/v${version}.tar.gz"
  #wget $url 
  #tar -zxvf v${version}.tar.gz 
  cd muduo-$version

  install_dir=$SCRIPT_DIR/third_party/deps/muduo-$version
  mkdir -p build || echo "build exists!" 
  cd build 

  cmake -DCMAKE_INSTALL_PREFIX=$install_dir -DProtobuf_LIBRARIES="$HOME/.openmit_deps/lib" -DProtobuf_INCLUDE_DIR=$HOME/.openmit_deps/include -DBoost_INCLUDE_DIRS=$HOME/.openmit_deps/include -DCMAKE_BUILD_NO_EXAMPLES=1 -DMUDUO_STD_STRING=1 -DCMAKE_BUILD_TYPE="release" ..

  make -j8 && make install

  link_dir=$SCRIPT_DIR/third_party/deps && (mkdir -p $link_dir || echo "$link_dir exists!")
  cd $SCRIPT_DIR/third_party/deps
  ln -s muduo-$version muduo

  # drop 
  if [ $? -eq 0 ]; then
    echo "success to build muduo. drop raw package."
    #rm $SCRIPT_DIR/third_party/v${version}.tar.gz 
    #rm -rf $SCRIPT_DIR/third_party/muduo-$version 
  else
    echo "failed to build muduo."
  fi
}

function install_gperftools() {
  cd $SCRIPT_DIR/third_party
  version=2.7 
  url="https://github.com/gperftools/gperftools/archive/gperftools-${version}.tar.gz"
  wget $url 
  tar -zxvf gperftools-2.7.tar.gz && cd gperftools-gperftools-2.7/ 
  install_dir=$SCRIPT_DIR/third_party/deps/gperftools-${version} 
  ./autogen.sh
  ./configure --prefix=$install_dir 
  make -j8 && make install 

  link_dir=$SCRIPT_DIR/third_party/deps && (mkdir -p $link_dir || echo "$link_dir exists!")
  cd $SCRIPT_DIR/third_party/deps
  ln -s gperftools-$version gperftools
  
  # drop 
  #if [ $? -eq 0 ]; then
  #  echo "success to build gperftools. drop raw package."
  #  rm $SCRIPT_DIR/third_party/gperftools-${version}.tar.gz* 
  #  rm -rf $SCRIPT_DIR/third_party/gperftools-gperftools-${version}
  #else
  #  echo "failed to build gperftools."
  #fi
  
}

##################################
# 1. Muduo
install_muduo
# 2. gperftools
#install_gperftools

echo "======== ${BASH_SOURCE[0]} ========"
