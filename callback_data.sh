#!/bin/bash

if [ $# -gt 0 ]; then
  cur_date=$1 
else
  cur_date=`date +"%Y%m%d"`
fi

# callback task
for i in {0..10}
do
  exec_date=`date +"%Y%m%d" -d"-10 day $cur_date"`
  echo $i, $exec_date
done

echo $cur_date
