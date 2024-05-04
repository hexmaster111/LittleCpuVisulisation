#!/bin/bash
set -e
if ! test -d bin; then
    mkdir bin
fi
cc -ggdb src/main.cpp  -o bin/main -lraylib -lm -std=c++11
