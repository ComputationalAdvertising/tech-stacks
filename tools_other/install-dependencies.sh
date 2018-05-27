#!/bin/bash -e

set -o pipefail
set -o errexit

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

if [ ! -d third_party ]; then
  mkdir -p third_party
fi 
cd third_party

version=7.52.1
url="https://github.com/google/curl/archive/v${version}.tar.gz"
url=https://curl.haxx.se/download/curl-${version}.tar.gz
wget $url 
tar -zxvf curl-${version}.tar.gz && cd curl-$version

install_dir=$SCRIPT_DIR/third_party/deps/curl-$version
mkdir -p $install_dir || true
./configure --prefix=$install_dir --disable-shared --with-pic && make -j8 && make install 

link_dir=$SCRIPT_DIR/third_party/deps/curl 
cd $SCRIPT_DIR/third_party/deps
ln -s curl-$version curl

echo "======== ${BASH_SOURCE[0]} ========"
