#!/bin/bash

# Check if source file exists
if [ ! -f "$1.cpp" ]; then
    echo "Source file $1.cpp not found."
    exit 1
fi

# Check if input file exists
if [ ! -f "$1.txt" ]; then
    echo "Input file $1.txt not found."
    exit 1
fi

# Compile the source file
if ! g++ -x c++ -g -O2 -std=gnu++17 -static "$1.cpp" -o "$1"; then
    echo "Compilation failed."
    exit 1
fi

# Display the output of the program
./"$1" < "$1.txt"

# Remove the compiled executable
rm -f "$1"
