#!/bin/sh

gcc -g -Wall -std=c99 -pedantic -o src/a0/njvm src/a0/njvm.c && src/a0/njvm --help
