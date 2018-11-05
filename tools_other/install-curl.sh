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

##############################################
# curl依赖openssl项目，因此在configure时需要指定openssl信息
# openssl相关库文件（ssl, crypto）要放在LD_LIBRARY_PATH中
# 注：linux 64位机器环境下 openssl的库文件路径 可能在$prefix/lib64下面
##############################################
export LD_LIBRARY_PATH=$HOME/.openmit_deps/lib:$HOME/.openmit_deps/lib64:$LD_LIBRARY_PATH  
./configure --prefix=$install_dir --with-ssl=$HOME/.openmit_deps LDFLAGS="-L$HOME/.openmit_deps/lib -L$HOME/.openmit_deps/lib64" LIBS="-lssl -lcrypto" --with-pic && make -j8 && make install 

link_dir=$SCRIPT_DIR/third_party/deps/curl 
cd $SCRIPT_DIR/third_party/deps
ln -s curl-$version curl

echo "======== ${BASH_SOURCE[0]} ========"
