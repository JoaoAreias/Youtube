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

# Number of times to run the program
runs=100
total_time=0

for ((i = 1; i <= runs; i++)); do
    # Run the compiled program and measure execution time
    start=$(date +%s.%N)
    ./"$1" < "$1.txt" > /dev/null
    end=$(date +%s.%N)
    diff=$(echo "$end - $start" | bc)
    total_time=$(echo "$total_time + $diff" | bc)
    echo "Run $i time: $diff seconds"
done

# Calculate the average time
average_time=$(echo "$total_time / $runs" | bc -l)
printf "Average time over %d runs: %.6f seconds\n" "$runs" "$average_time"

# Display the output of the program
echo "Ouput of the program:"
./"$1" < "$1.txt"

# Remove the compiled executable
rm -f "$1"
