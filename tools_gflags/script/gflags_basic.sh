#!/bin/bash

SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd) 
PROJECT_DIR=$SCRIPT_DIR/..

$PROJECT_DIR/bin/gflags_basic --daemon=false --port 8888 --conf_path $PROJECT_DIR/third_party 

echo "======== ${BASH_SOURCE[0]} ========"
