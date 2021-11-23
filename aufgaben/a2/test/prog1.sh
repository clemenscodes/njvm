#!/bin/sh

BUILD="build/njvm"
BUILD_OUT="test/out/prog1.out"

TEST="test/njvm"
TEST_OUT="test/out/target.prog1.out"

BIN="test/prog1.bin"

$BUILD $BIN > $BUILD_OUT
$TEST $BIN > $TEST_OUT

if diff $BUILD_OUT $TEST_OUT
then
    echo "PASSED" 
else
    echo "FAILED" 
    exit 1
fi
