#!/bin/bash -x 

#=================================#
# 1. eigen-3.3.4
#=================================#

set -o pipefail
set -o errexit

SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd) 
THIRD_PARTY_DIR=$SCRIPT_DIR/third_party

if [ ! -d $THIRD_PARTY_DIR ]; then mkdir -p $THIRD_PARTY_DIR; fi 

export LD_LIBRARY_PATH=${HOME}/lib:${LD_LIBRARY_PATH}
export LIBRARY_PATH=${HOME}/lib:${LIBRARY_PATH}
export C_INCLUDE_PATH=${HOME}/include:${C_INCLUDE_PATH}
export CPLUS_INCLUDE_PATH=${HOME}/include:${CPLUS_INCLUDE_PATH}

##################################
function install_eigen() {
  cd $THIRD_PARTY_DIR 
  version=3.3.4
  url=http://bitbucket.org/eigen/eigen/get/${version}.tar.bz2
  #wget $url
  tar -xjf ${version}.tar.bz2
  cd eigen-eigen*
  install_dir=$THIRD_PARTY_DIR/deps/eigen-${version} && (mkdir -p $install_dir || echo "$install_dir exists") 
  mkdir -p build || echo "build exist!" 
  cd build
  cmake -DCMAKE_INSTALL_PREFIX=$install_dir .. 
  make -j8 && make install 
  cd $THIRD_PARTY_DIR/deps   
  ln -s eigen-${version} eigen

  if [ $? -eq 0 ]; then
    echo "successful to build eigen-$version. drop raw package."
    rm $THIRD_PARTY_DIR/${version}.tar.bz2 || echo "rm done!"
    rm -rf $THIRD_PARTY_DIR/eigen-${version} || echo "rm done!"
  else
    echo "failed to build eigen.."
  fi
}

##################################
# 1. eigen
install_eigen

echo "======== ${BASH_SOURCE[0]} ========"
