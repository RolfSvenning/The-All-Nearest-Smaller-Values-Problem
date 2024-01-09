#!/bin/bash

# Compile the project using CMake
#cd /path/to/ANSV2 || exit
mkdir -p cmake-build-debug  # Or any desired build directory
cd cmake-build-debug || exit
cmake .. || exit
make || exit

#n=1048576 #134217728=2^27 268435456=2^28 536870912=2^29 1073741824=2^30 (2^30 for server!)
n=1048576 #16777216 #134217728=2^27 268435456=2^28 536870912=2^29 1073741824=2^30 (2^30 for server!)
repetitions=3

#run_speedup_experiment() {
#    for (( i = 1; i <= $(getconf _NPROCESSORS_ONLN); i++ )); do
#        echo "Running speedup experiment with $i threads..."
#        export PARLAY_NUM_THREADS=$i
#        ./ANSV2 "speedup" $n 8192 $repetitions
#    done
#}
#
run_running_time_experiment() {
    for i in 1 $(getconf _NPROCESSORS_ONLN); do
        echo "Running running time experiment with $i threads..."
        export PARLAY_NUM_THREADS=$i
        ./ANSV2 "running_time" $n 8192 $repetitions
    done
}

#run_block_size_experiment() {
#    for i in 1 $(getconf _NPROCESSORS_ONLN); do
#        echo "Running block size experiment with $i threads..."
#        export PARLAY_NUM_THREADS=$i
#        ./ANSV2 "block_size" $n 8192 $repetitions
#    done
#}

# RUNNING EXPERIMENTS
run_speedup_experiment
run_running_time_experiment
run_block_size_experiment

# Exit successfully
exit 0
