#!/bin/sh

rm -rf src/a1/build
mkdir src/a1/build && cd src/a1/build || exit
cmake -DCMAKE_C_COMPILER=gcc -DCMAKE_C_FLAGS="-g -Wall -std=c99 -pedantic" .. 
make
./njvm