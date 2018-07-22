#!/bin/bash -e

set -o pipefail
set -o errexit

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

if [ ! -d third_party ]; then
  mkdir -p third_party
fi 
cd third_party

url=https://github.com/google/cityhash.git
git clone $url 
cd cityhash 

install_dir=$SCRIPT_DIR/third_party/deps/cityhash
mkdir -p $install_dir || true
./configure --enable-sse4.2 --prefix=$install_dir 
make all check CXXFLAGS="-g -O3 -msse4.2"
make install

echo "======== ${BASH_SOURCE[0]} ========"
