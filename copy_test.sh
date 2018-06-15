#!/bin/bash


for dir in `ls $(pwd)`
do 
  if [ -d $dir ]; then
    echo "$dir is dir" 
    cp README.md $dir
  else
    echo "$dir is file"
  fi
done

