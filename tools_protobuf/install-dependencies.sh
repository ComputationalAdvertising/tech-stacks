#!/bin/bash -e

set -o pipefail
set -o errexit

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

if [ ! -d third_party ]; then
  mkdir -p third_party
fi 
cd third_party

version=3.5.0
url="https://github.com/google/protobuf/archive/v${version}.tar.gz"
wget $url 
tar -zxvf v${version}.tar.gz

install_dir=$SCRIPT_DIR/third_party/deps/protobuf-$version
cd protobuf-$version && ./autogen.sh
mkdir -p $install_dir || true
./configure --prefix=$install_dir --with-pic && make clean && make -j8 && make check && make install 

link_dir=$SCRIPT_DIR/third_party/deps/protobuf 
cd $SCRIPT_DIR/third_party/deps
ln -s protobuf-$version protobuf

echo "======== ${BASH_SOURCE[0]} ========"
