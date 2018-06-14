#!/bin/bash

os_name=`uname | tr 'A-Z' 'a-z'`

GCC=`which g++`
if [[ $os_name == "darwin" ]]; then
  GCC=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++
fi
echo "cpp compiler: $GCC"

mkdir -p bin || echo "bin exists!"

source_file="callback_lambda"
$GCC -std=c++11 ${source_file}.cc -o bin/${source_file}
