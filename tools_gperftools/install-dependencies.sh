#!/bin/bash -x 

#=================================#
# 1. gperftools-2.7
#=================================#

set -o pipefail
set -o errexit

SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd) 
THIRD_PARTY_DIR=$SCRIPT_DIR/third_party

if [ ! -d $THIRD_PARTY_DIR ]; then mkdir -p $THIRD_PARTY_DIR; fi 

################################## 
# deps 
function install_gperftools() { 
  export LD_LIBRARY_PATH=$HOME/local/lib:$LD_LIBRARY_PATH
  export LIBRARY_PATH=$HOME/local/lib:$LIBRARY_PATH
  export C_INCLUDE_PATH=$HOME/local/include:$C_INCLUDE_PATH
  export CPLUS_INCLUDE_PATH=$HOME/local/include:$CPLUS_INCLUDE_PATH
  cd $THIRD_PARTY_DIR
  version=2.7
  url=https://github.com/gperftools/gperftools/archive/gperftools-${version}.tar.gz
  wget $url 
  tar -zxvf gperftools-${version}.tar.gz 
  cd gperftools-gperftools-2.7
  aclocal && autoconf && autoheader && libtoolize --automake --copy --debug  --force && automake -a  
  install_dir=$THIRD_PARTY_DIR/deps/gperftools-$version && (mkdir -p $install_dir || echo "$install_dir exists!")
  ./configure --prefix=$install_dir 
  make -j4 && make install 
  link_dir=$THIRD_PARTY_DIR/deps && (mkdir -p $link_dir || echo "$link_dir exists!")
  cd $THIRD_PARTY_DIR/deps && ln -s gperftools-$version gperftools 

  if [ $? -eq 0]; then 
    echo "successful to build gperftools. drop raw package"
    rm $THIRD_PARTY_DIR/gperftools-${version}.tar.gz 
    rm -rf $THIRD_PARTY_DIR/gperftools-gperftools-${version}
  else
    echo "failed to build gperftools."
  fi 

  cp -r $THIRD_PARTY_DIR/deps/gperftools/bin/* $HOME/local/bin/
  cp -r $THIRD_PARTY_DIR/deps/gperftools/include/* $HOME/local/include/
  cp -r $THIRD_PARTY_DIR/deps/gperftools/lib/lib*.a $HOME/local/lib/
}

################################## 
# deps
# 1. gperftools
install_gperftools

echo "======== ${BASH_SOURCE[0]} ========"
