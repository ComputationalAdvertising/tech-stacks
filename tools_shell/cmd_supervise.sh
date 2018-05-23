#!/bin/bash

function prog() {
  echo "xxxx"
}

supervise prog

echo "======== ${BASH_SOURCE[0]} ========"
