#!/bin/bash -x 

#=================================#
# 1. thrift-0.10.0
# 2. snappy-1.1.7
# 3. libevent-
#=================================#

set -o pipefail
set -o errexit

SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd) 
THIRD_PARTY_DIR=$SCRIPT_DIR/third_party

if [ ! -d $THIRD_PARTY_DIR ]; then mkdir -p $THIRD_PARTY_DIR; fi 

################################## 
# deps 
function install_libevent() { 
  cd $THIRD_PARTY_DIR
  version=2.0.22
  url=https://github.com/nmathewson/Libevent/archive/release-${version}-stable.tar.gz
  wget $url 
  tar -zxvf release-${version}-stable.tar.gz  
  cd Libevent-release-${version}-stable 
  aclocal && autoconf && autoheader && libtoolize --automake --copy --debug  --force && automake -a  
  install_dir=$THIRD_PARTY_DIR/deps/libevent-$version && (mkdir -p $install_dir || echo "$install_dir exists!")
  ./configure --prefix=$install_dir 
  make && make install 
  link_dir=$THIRD_PARTY_DIR/deps && (mkdir -p $link_dir || echo "$link_dir exists!")
  cd $THIRD_PARTY_DIR/deps && ln -s libevent-$version libevent 

  if [ $? -eq 0]; then 
    echo "successful to build libevent. drop raw package"
    rm $THIRD_PARTY_DIR/release-${version}-stable.tar.gz 
    rm -rf $THIRD_PARTY_DIR/Libevent-release-${version}-stable 
  else
    echo "failed to build libevent."
  fi 

  cp -r $THIRD_PARTY_DIR/deps/libevent/bin/* $HOME/local/bin/
  cp -r $THIRD_PARTY_DIR/deps/libevent/include/* $HOME/local/include/
  cp -r $THIRD_PARTY_DIR/deps/libevent/lib/libevent*.a $HOME/local/lib/
}

function install_openssl() {
  cd $THIRD_PARTY_DIR
  version=1.1.1
  url=https://www.openssl.org/source/old/${version}/openssl-${version}-pre7.tar.gz
  wget $url
  tar -zxvf openssl-${version}-pre7.tar.gz
  cd openssl-1.1.1-pre7
  mkdir -p $HOME/local || echo "$HOME/local exists"
  ./config --prefix=$HOME/local 
  ./config -t
  make && make install 
}

function install_thrift() {
  export LD_LIBRARY_PATH=$HOME/lib:$LD_LIBRARY_PATH
  cd $THIRD_PARTY_DIR 
  thrift_version=0.10.0
  url=https://github.com/apache/thrift/archive/${thrift_version}.tar.gz
  wget $url
  tar -zxvf ${thrift_version}.tar.gz 
  cd thrift-$thrift_version

  install_dir=$THIRD_PARTY_DIR/deps/thrift-${thrift_version} && (mkdir -p $install_dir || echo "$install_dir exists")
  ./bootstrap.sh
  ./configure --with-boost-libdir=$HOME/local/lib CXXFLAGS='-g -O3 -fPIC' CFLAGS='-g -O3' CPPFLAGS='-DDEBUG_MY_FEATURE' --enable-coverage --prefix=$install_dir --with-php=no --with-php_extension=no --with-dart=no --with-ruby=no --with-haskell=no --with-go=no --with-rs=no --with-haxe=no --with-dotnetcore=no --with-d=no --with-qt4=no --with-qt5=no --with-csharp=no --with-java=no --with-erlang=no --with-nodejs=no --with-lua=no --with-perl=no --with-python=no --with-cpp --with-libevent=$HOME/local --with-openssl=$HOME/local --enable-tests=no
  make -j8 && make install 
  link_dir=$THIRD_PARTY_DIR/deps && (mkdir -p $link_dir || echo "$link_dir exists")
  cd $THIRD_PARTY_DIR/deps 
  ln -s thrift-${thrift_version} thrift

  if [ $? -eq 0 ]; then
    echo "successful to build thrift. drop raw package."
    rm $THIRD_PARTY_DIR/${thrift_version}.tar.gz* || echo "rm done!"
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
# deps
install_libevent
install_openssl
# 1. Thrift 
install_thrift
# 2. Snappy 
install_snappy

echo "======== ${BASH_SOURCE[0]} ========"
