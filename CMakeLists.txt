cmake_minimum_required(VERSION 3.25)
project(ANSV2)

set(CMAKE_CXX_STANDARD 20)

add_executable(ANSV2 main.cpp test.cpp)
target_include_directories (ANSV2 PUBLIC parlaylib/include)
target_include_directories (ANSV2 PUBLIC parlaylib/examples)

add_executable(parallelMinBinaryTreeArray parallelMinBinaryTreeArray.cpp)
target_include_directories(parallelMinBinaryTreeArray PUBLIC parlaylib/include)

add_executable(loopTest loopTest.cpp)
target_include_directories(loopTest PUBLIC parlaylib/include)

add_executable(parallelMinBinaryTreePointers parallelMinBinaryTreePointers.cpp)
target_include_directories(parallelMinBinaryTreePointers PUBLIC parlaylib/include)

add_executable(ANSV_nlogn_work ANSV_nlogn_work.cpp parallelMinBinaryTreeArray.cpp)
target_include_directories(ANSV_nlogn_work PUBLIC parlaylib/include)

## -------------------------------------------------------------------
##                       Library definition
#
#add_library(parlay INTERFACE)
#set(PARLAY_INCLUDE_DIR "${PARLAY_SOURCE_DIR}/include")
#target_include_directories(parlay INTERFACE
#        $<BUILD_INTERFACE:${PARLAY_INCLUDE_DIR}>
#        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
#
#option(PARLAY_USE_CXX_20 "Require Parlay to build with C++20")
#if (PARLAY_USE_CXX_20)
#    target_compile_features(parlay INTERFACE cxx_std_20)
#else()
#    target_compile_features(parlay INTERFACE cxx_std_17)
#endif()
#
## Link against system threads
#find_package(Threads REQUIRED)
#target_link_libraries(parlay INTERFACE Threads::Threads)


set(EXAMPLES "primes" "BFS" "word_counts" "tokens" "filter" "linefit"
        "mcss" "quickhull" "pagerank" "spanning_tree" "maximal_matching"
        "kruskal" "mergesort" "samplesort" "kth_smallest"
        "spectral_separator" "find_if" "rabin_karp" "kmeans_pp" "delaunay"
        "lasso_regression" "knn" "set_cover" "scan" "flatten" "reduce"
        "BFS_ligra" "triangle_count" "graph_color" "maximal_independent_set"
        "nbody_fmm" "cartesian_tree" "kcore" "cycle_count"
        "betweenness_centrality" "low_diameter_decomposition" "quicksort" "filter_kruskal"
        "knuth_shuffle" "minimum_edit_distance" "bigint_add" "bellman_ford" "suffix_array"
        "le_list" "longest_common_prefix" "longest_repeated_substring" "range_min"
        "fast_fourier_transform" "bucketed_dijkstra" "push_relabel_max_flow"
        "knuth_morris_pratt" "huffman_tree" "decision_tree_c45" "karatsuba" "suffix_tree"
        "2d_linear_program" "box_kdtree" "radix_tree" "ray_trace" "hash_map" "oct_tree"
        "3d_range" "rectangle_intersection")

function(add_example NAME)
    add_executable(${NAME} parlaylib/examples/${NAME}.cpp)
    target_include_directories(${NAME} PUBLIC parlaylib/include)
    target_include_directories(${NAME} PUBLIC parlaylib/examples)
endfunction()

foreach(example ${EXAMPLES})
    add_example(${example})
endforeach()
