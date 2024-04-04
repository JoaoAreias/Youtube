#!/bin/bash

# Check if source file exists
if [ ! -f "$1.cpp" ]; then
    echo "Source file $1.cpp not found."
    exit 1
fi


# Compile the source file
if ! g++ -x c++ -g3 -O2 -std=gnu++17 -static "$1.cpp" -o "$1"; then
    echo "Compilation failed."
    exit 1
fi

