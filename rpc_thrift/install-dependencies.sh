#!/bin/bash -x 

set -o pipefail
set -o errexit

SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd) 
THIRD_PARTY_DIR=$SCRIPT_DIR/third_party

if [ ! -d $THIRD_PARTY_DIR ]; then mkdir -p $THIRD_PARTY_DIR; fi 
cd $THIRD_PARTY_DIR 

# thrift
thrift_version=0.11.0
url=https://github.com/apache/thrift/archive/${thrift_version}.tar.gz
wget $url
tar -zxvf ${thrift_version}.tar.gz && cd thrift-$thrift_version

# build
install_dir=$THIRD_PARTY_DIR/deps && make -p $install_dir || true
./bootstrap.sh
./configure --with-boost-libdir=/usr/lib/x86_64-linux-gnu CXXFLAGS='-g -O3' CFLAGS='-g -O3' CPPFLAGS='-DDEBUG_MY_FEATURE' --enable-coverage --prefix=$install_dir --with-php=no --with-php_extension=no --with-dart=no --with-ruby=no --with-haskell=no --with-go=no --with-rs=no --with-haxe=no --with-dotnetcore=no --with-d=no --with-qt4=no --with-qt5=no --with-csharp=no --with-java=no --with-erlang=no --with-nodejs=no --with-lua=no --with-perl=no --with-python=no
make -j8 && make install

if [ $? -eq 0 ]; then
  echo "successful to build. drop raw package."
  rm $THIRD_PARTY_DIR/${thrift_version}.tar.gz  
  rm -rf $THIRD_PARTY_DIR/thrift-${thrift_version}
else
  echo "failed to build."
fi

echo "======== ${BASH_SOURCE[0]} ========"
