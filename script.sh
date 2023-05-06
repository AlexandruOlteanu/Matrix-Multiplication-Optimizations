#!/bin/bash

make clean
make

name=$1

./tema2_$name /export/asc/tema2/input

./compare out1 /export/asc/tema2/out1 0.0001
./compare out2 /export/asc/tema2/out2 0.0001
./compare out3 /export/asc/tema2/out3 0.0001