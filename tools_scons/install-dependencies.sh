#!/bin/bash -x 

#=================================#
# 1. scons-2.5.0
#=================================#

set -o pipefail
set -o errexit

SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd) 
THIRD_PARTY_DIR=$SCRIPT_DIR/third_party

if [ ! -d $THIRD_PARTY_DIR ]; then mkdir -p $THIRD_PARTY_DIR; fi 

##################################
function install_scons() {
  cd $THIRD_PARTY_DIR 
  version=2.5.0
  url=https://jaist.dl.sourceforge.net/project/scons/scons/${version}/scons-${version}.tar.gz
  wget $url
  tar -zxvf scons-${version}.tar.gz 
  cd scons-$version

  install_dir=$THIRD_PARTY_DIR/deps/scons-${version} && (mkdir -p $install_dir || echo "$install_dir exists")
  python setup.py install --prefix=$install_dir
  link_dir=$THIRD_PARTY_DIR/deps && (mkdir -p $link_dir || echo "$link_dir exists")
  cd $THIRD_PARTY_DIR/deps 
  ln -s scons-${version} scons

  if [ $? -eq 0 ]; then
    echo "successful to build scons. drop raw package."
    rm $THIRD_PARTY_DIR/scons-${version}.tar.gz || echo "rm done!"
    rm -rf $THIRD_PARTY_DIR/scons-${version} || echo "rm done!"
  else
    echo "failed to build scons.."
  fi
}

##################################
# 1. Thrift 
install_scons

echo "======== ${BASH_SOURCE[0]} ========"
