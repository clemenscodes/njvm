#!/bin/sh

rm -rf test/out
mkdir test/out

echo "Testing prog1.bin ..."
echo
test/prog1.sh
echo
echo "Testing prog2.bin ..."
echo
test/prog2.sh
echo
