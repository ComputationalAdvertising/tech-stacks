#!/bin/bash -e

#=================================#
# 1. jsoncpp-1.8.4
#=================================#

set -o pipefail
set -o errexit

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

mkdir -p $SCRIPT_DIR/third_party || echo "third_party exists!"
cd $SCRIPT_DIR/third_party 

version=1.8.4
install_dir=$SCRIPT_DIR/deps/jsoncpp-${version}
mkdir -p $install_dir || echo "$install_dir exists!"

# download
wget https://github.com/open-source-parsers/jsoncpp/archive/${version}.tar.gz 
tar -zxvf ${version}.tar.gz && cd jsoncpp-$version 
# build
mkdir -p build || echo "build exists!" && cd build 
cmake -DCMAKE_BUILD_TYPE=debug -DBUILD_STATIC_LIBS=ON -DBUILD_SHARED_LIBS=OFF -DCMAKE_INSTALL_PREFIX=$install_dir ..
make && make install 
cd $SCRIPT_DIR/deps 
ln -s jsoncpp-$version jsoncpp 

if [ $? -eq 0 ]; then 
  echo "success to build jsoncpp-$version. drop raw package."
  rm -rf $SCRIPT_DIR/third_party/${version}.tar.gz || true 
  #rm -rf $SCRIPT_DIR/third_party/jsoncpp-$version || true 
else
  echo "failed to build jsoncpp-$version"
fi

echo "======== ${BASH_SOURCE[0]} ========"
