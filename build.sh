#!/bin/bash
set -e
if ! test -d bin; then
    mkdir bin
fi
cc src/main.cpp -o bin/main -lraylib -lm
