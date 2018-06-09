#!/bin/bash -x 

#=================================#
# 1. thrift-0.11.0
# 2. snappy-1.1.7
#=================================#

set -o pipefail
set -o errexit

SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd) 
THIRD_PARTY_DIR=$SCRIPT_DIR/third_party

if [ ! -d $THIRD_PARTY_DIR ]; then mkdir -p $THIRD_PARTY_DIR; fi 

##################################
function install_thrift() {
  cd $THIRD_PARTY_DIR 
  thrift_version=0.10.0
  url=https://github.com/apache/thrift/archive/${thrift_version}.tar.gz
  wget $url
  tar -zxvf ${thrift_version}.tar.gz && cd thrift-$thrift_version

  install_dir=$THIRD_PARTY_DIR/deps/thrift-${thrift_version} && make -p $install_dir || true
  ./bootstrap.sh
  ./configure --with-boost-libdir=/usr/lib/x86_64-linux-gnu CXXFLAGS='-g -O3' CFLAGS='-g -O3' CPPFLAGS='-DDEBUG_MY_FEATURE' --enable-coverage --prefix=$install_dir --with-php=no --with-php_extension=no --with-dart=no --with-ruby=no --with-haskell=no --with-go=no --with-rs=no --with-haxe=no --with-dotnetcore=no --with-d=no --with-qt4=no --with-qt5=no --with-csharp=no --with-java=no --with-erlang=no --with-nodejs=no --with-lua=no --with-perl=no --with-python=no 
  make -j8 && make install 
  link_dir=$THIRD_PARTY_DIR/deps && (mkdir -p $link_dir || echo "$link_dir exists")
  cd $THIRD_PARTY_DIR/deps 
  ln -s thrift-${thrift_version} thrift

  if [ $? -eq 0 ]; then
    echo "successful to build thrift. drop raw package."
    rm $THIRD_PARTY_DIR/${thrift_version}.tar.gz || echo "rm done!"
    rm -rf $THIRD_PARTY_DIR/thrift-${thrift_version} || echo "rm done!"
  else
    echo "failed to build thrift.."
  fi
}

function install_snappy() {
  cd $THIRD_PARTY_DIR 
  snappy_version=1.1.7
  url=https://github.com/google/snappy/archive/${snappy_version}.tar.gz
  wget $url
  tar -zxvf ${snappy_version}.tar.gz && cd snappy-${snappy_version} 
  mkdir build || echo "build exists"
  cd build  
  install_dir=$THIRD_PARTY_DIR/deps/snappy-$snappy_version 
  cmake -DCMAKE_INSTALL_PREFIX=$install_dir -DCMAKE_C_COMPILER=`which gcc` -DCMAKE_CXX_COMPILER=`which g++` -DSNAPPY_BUILD_TESTS=0 ../
  make -j8 && make install 
  link_dir=$THIRD_PARTY_DIR/deps && (mkdir -p $link_dir || echo "$link_dir exists")
  cd $THIRD_PARTY_DIR/deps
  ln -s snappy-${snappy_version} snappy

  rm $THIRD_PARTY_DIR/${snappy_version}.tar.gz || echo "rm done!"
  rm -rf $THIRD_PARTY_DIR/snappy-${snappy_version} || echo "rm done!"
}

##################################
# 1. Thrift 
#install_thrift
# 2. Snappy 
install_snappy

echo "======== ${BASH_SOURCE[0]} ========"
