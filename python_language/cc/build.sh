#!/bin/bash

g++ -o libpycallclass.so -shared -fPIC pycallclass.cc

echo "======== ${BASH_SOURCE[0]} ========"
