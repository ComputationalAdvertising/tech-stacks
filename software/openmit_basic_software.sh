#!/bin/bash

set -o pipefail
set -o errexit

SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd) 
THIRD_PARTY_DIR=$SCRIPT_DIR/third_party

mkdir -p $THIRD_PARTY_DIR || echo "$THIRD_PARTY_DIR exists!"
mkdir -p $HOME/local || echo "$HOME/local exists!"

function install_cmake() {
  cd $THIRD_PARTY_DIR
  version=3.3.2
  url=https://cmake.org/files/v3.3/cmake-${version}.tar.gz
  wget $url
  tar -zxvf cmake-${version}.tar.gz 
  cd cmake-${version}
  ./bootstrap --prefix=$HOME/local
  make && make install
}

function install_openssl() {
  cd $THIRD_PARTY_DIR
  version=1.1.1
  url=https://www.openssl.org/source/old/${version}/openssl-${version}-pre7.tar.gz
  wget $url
  tar -zxvf openssl-${version}-pre7.tar.gz
  cd openssl-1.1.1-pre7
  ./config --prefix=$HOME/local 
  ./config -t
  make && make install
}

################
#install_cmake 
install_openssl
