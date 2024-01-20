#!/bin/bash

# Number of times to run the binary
num_runs=10

# Array to store the numbers
numbers=()

# Run the binary 10 times
for ((i=1; i<=$num_runs; i++)); do
    output=$(./main)  # Replace 'main' with the actual name of your binary
    number=$(echo "$output" | sed 's/us//')  # Remove the "us" suffix
    numbers+=("$number")
done

# Calculate the average
total=0
for num in "${numbers[@]}"; do
    total=$(echo "$total + $num" | bc)
done

average=$(echo "scale=2; $total / $num_runs" | bc)

echo "Numbers: ${numbers[@]}"
echo "Average: $average"
