#!/bin/bash -x 

#=================================#
# 1. sparsehash-2.0.3
#=================================#

set -o pipefail
set -o errexit

SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd) 
THIRD_PARTY_DIR=$SCRIPT_DIR/third_party
mkdir -p $THIRD_PARTY_DIR || echo "$THIRD_PARTY_DIR exists"

################################## 
# deps 
function install_sparsehash() { 
  cd $THIRD_PARTY_DIR
  version=2.0.3
  url=https://github.com/sparsehash/sparsehash/archive/sparsehash-${version}.tar.gz
  wget $url 
  tar -zxvf sparsehash-${version}.tar.gz  
  cd sparsehash-sparsehash-$version
  install_dir=$THIRD_PARTY_DIR/deps/sparsehash-$version && (mkdir -p $install_dir || echo "$install_dir exists!")
  ./configure --prefix=$install_dir 
  make -j8 && make install 
  link_dir=$THIRD_PARTY_DIR/deps && (mkdir -p $link_dir || echo "$link_dir exists!")
  cd $THIRD_PARTY_DIR/deps && ln -s sparsehash-$version sparsehash

  if [ $? -eq 0]; then 
    echo "successful to build sparsehash. drop raw package"
    rm $THIRD_PARTY_DIR/sparsehash-${version}.tar.gz
    rm -rf $THIRD_PARTY_DIR/sparsehash-sparsehash-$version
  else
    echo "failed to build sparsehash."
  fi 

  cp -r $THIRD_PARTY_DIR/deps/sparsehash/include/* $HOME/local/include/
}

################################## 
# 1. SparseHash 
install_sparsehash

echo "======== ${BASH_SOURCE[0]} ========"
