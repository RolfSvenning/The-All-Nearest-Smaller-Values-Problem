#!/bin/bash

# Compile the project using CMake
cd /path/to/ANSV2 || exit
mkdir -p cmake-build-debug  # Or any desired build directory
cd cmake-build-debug || exit
cmake .. || exit
make || exit

# Define functions for each set of experiments
run_speedup_experiment() {
    # Define variables
    n=65536
    repetitions=3

    for (( i = 1; i <= $(getconf _NPROCESSORS_ONLN); i++ )); do
        echo "Running speedup experiment with $i threads..."
        export PARLAY_NUM_THREADS=$i
        ./ANSV2 "speedup" $n 8192 $repetitions
    done
}

run_running_time_experiment() {
    # Implement your running time experiment
    n=65536
    repetitions=3

    for i in 1 $(getconf _NPROCESSORS_ONLN); do
        echo "Running running time experiment with $i threads..."
        export PARLAY_NUM_THREADS=$i
        ./ANSV2 "running_time" $n 8192 $repetitions
    done
}

run_block_size_experiment() {
    # Implement your block size experiment
    n=65536
    repetitions=3

    for (( i = 1; i <= $(getconf _NPROCESSORS_ONLN); i++ )); do
        echo "Running block size experiment with $i threads..."
        export PARLAY_NUM_THREADS=$i
        ./ANSV2 "block_size" $n 8192 $repetitions
    done
}

# Run each set of experiments
run_speedup_experiment
run_running_time_experiment
run_block_size_experiment

# Exit successfully
exit 0
