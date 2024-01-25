#!/bin/bash

# Compile the C++ files first
g++ test_gen.cpp -o test_gen
g++ answer.cpp -o answer
g++ check.cpp -o check

# Initialize counter
counter=0

while true; do
    # Increment counter
    ((counter++))

    # Generate the input data
    ./test_gen > input.txt

    # Run the programs with the input and save their output
    ./answer < input.txt > answer.txt
    ./check < input.txt > check.txt

    # Compare the output files
    if ! diff -q answer.txt check.txt > /dev/null; then
        cat input.txt
        break
    fi
    echo $counter
done