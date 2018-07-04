#!/bin/bash -e

#=================================#
# 1. boost-1.60.0
#=================================#

set -o pipefail
set -o errexit

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
mkdir -p $SCRIPT_DIR/third_party || echo "third_party exists!"

##################################
# https://github.com/boost/boost/blob/master/INSTALL.md
function install_boost() {
  cd $SCRIPT_DIR/third_party 
  version=1_60_0 
  raw_version=1.60.0
  wget --no-check-certificate http://sourceforge.net/projects/boost/files/boost/${raw_version}/boost_${version}.tar.gz
  tar -zxvf boost_${version}.tar.gz 
  cd boost_${version}

  install_dir=$SCRIPT_DIR/third_party/deps/boost_${version}
  mkdir -p $install_dir || echo "$install_dir exists!"
  ./bootstrap.sh --prefix=${install_dir}
  ./b2 install

  # drop 
  if [ $? -eq 0 ]; then 
    echo "success to build boost. drop raw package."
    rm -rf $SCRIPT_DIR/third_party/boost* 
  else
    echo "failed to build boost."
  fi
}

##################################
# 1. boost
install_boost

echo "======== ${BASH_SOURCE[0]} ========"
