#!/bin/bash

echo "sequential";

for i in 100 1000 10000 100000 1000000
do
  ./sequential.exe $i;
done

echo "----------------------------------"
echo "parallel"
for i in 100 1000 10000 100000 1000000
do
  for j in 1 2 4
  do
    mpiexec -n $j ./main.exe $i;
  done
done
