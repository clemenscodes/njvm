#!/bin/sh

BUILD="build/njvm"
BUILD_OUT="test/out/prog2.out"

TEST="test/njvm"
TEST_OUT="test/out/target.prog2.out"

BIN="test/prog2.bin"

$BUILD $BIN > $BUILD_OUT
$TEST $BIN > $TEST_OUT

if diff $BUILD_OUT $TEST_OUT
then
    echo "PASSED" 
else
    echo "FAILED" 
    exit 1
fi
