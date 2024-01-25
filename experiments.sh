#!/bin/bash

# Compile the project using CMake
#cd /path/to/ANSV2 || exit
mkdir -p cmake-build-debug  # Or any desired build directory
cd cmake-build-debug || exit
cmake .. || exit
make || exit

#n=1048576
n=1073741824 #16777216=2^24 #134217728=2^27 268435456=2^28 536870912=2^29 1073741824=2^30 (134217728 = 2^27 for server!)
#block_size=-1
repetitions=5

# run_speedup_experiment() {
#    for (( i = 1; i <= $(getconf _NPROCESSORS_ONLN); i++ )); do
#        echo "Running speedup experiment with $i threads..."
#        export PARLAY_NUM_THREADS=$i
#        ./ANSV2 "speedup" $n 8192 $repetitions
#    done
# }
#
run_running_time_experiment() {
    for i in 1 $(getconf _NPROCESSORS_ONLN); do
        echo "Running running time experiment with $i threads..."
        export PARLAY_NUM_THREADS=$i
        ./ANSV2 "running_time" $n -1 $repetitions
    done
}

#run_block_size_experiment() {
#    echo "Running block size experiment"
#    for i in $(getconf _NPROCESSORS_ONLN) 1; do
#      for (( e = 0; e <= 67; e++)); do
#          echo "Running block size experiment with $i threads and exponent $e"
#          export PARLAY_NUM_THREADS=$i
#          ./ANSV2 "block_size" $n $e $repetitions
#      done
#    done
#}
#
# RUNNING EXPERIMENTS
run_speedup_experiment
run_running_time_experiment
run_block_size_experiment

# Exit successfully
exit 0
