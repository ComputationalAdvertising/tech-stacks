#!/bin/bash -x 

#=================================#
# 1. glog-${glog_version}
#=================================#

set -o pipefail
set -o errexit

SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd) 
THIRD_PARTY_DIR=$SCRIPT_DIR/third_party

if [ ! -d $THIRD_PARTY_DIR ]; then mkdir -p $THIRD_PARTY_DIR; fi 

##################################
function install_glog() {
  cd $THIRD_PARTY_DIR 
  glog_version=0.3.5
  url=https://github.com/google/glog/archive/v${glog_version}.tar.gz
  wget $url
  tar -zxvf v${glog_version}.tar.gz && cd glog-$glog_version

  install_dir=$THIRD_PARTY_DIR/deps/glog-$glog_version && (mkdir -p $install_dir || true)
  ./configure CFLAGS="-g -O3 -fPIC" CXXFLAGS="-g -O3 -fPIC" --prefix=$install_dir 
  make -j8  && make install 
  cd $THIRD_PARTY_DIR/deps
  ln -s glog-$glog_version glog

  if [ $? -eq 0 ]; then
    echo "successful to build glog. drop raw package."
    rm $THIRD_PARTY_DIR/v${glog_version}.tar.gz  
    rm -rf $THIRD_PARTY_DIR/glog-${glog_version}
  else
    echo "failed to build glog.."
  fi
}

##################################
# 1. Glog 
install_glog

echo "======== ${BASH_SOURCE[0]} ========"
