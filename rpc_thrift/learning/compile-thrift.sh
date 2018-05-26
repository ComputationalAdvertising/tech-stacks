#!/bin/bash

SCRIPT_DIR=$(cd "$(dirname ${BASH_SOURCE[0]})" && pwd)
PROJECT_DIR=$SCRIPT_DIR/..

thrift="$PROJECT_DIR/third_party/deps/bin/thrift"

$thrift -r --gen cpp -o $SCRIPT_DIR $SCRIPT_DIR/thrift/tutorial.thrift
$thrift -r --gen cpp -o $SCRIPT_DIR $SCRIPT_DIR/thrift/shared.thrift
