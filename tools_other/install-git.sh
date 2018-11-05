#!/bin/bash -e

set -o pipefail
set -o errexit

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

if [ ! -d third_party ]; then
  mkdir -p third_party
fi 
cd third_party

# git最重要的配置，需要依赖curl和ssl 
export LD_LIBRARY_PATH=$HOME/.openmit_deps/lib:$HOME/.openmit_deps/lib64:$LD_LIBRARY_PATH  
nohup ./configure --prefix=$HOME/.openmit_deps --with-openssl --with-curl LDFLAGS="-L$HOME/.openmit_deps/lib -L$HOME/.openmit_deps/lib64" LIBS="-lcurl -lssl -lcrypto" > xx1 &

# 安装完成后，在~/.bashrc中配置 PATH=$install_dir/libexec/git-core:$install_dir/bin:$PATH

echo "======== ${BASH_SOURCE[0]} ========"
