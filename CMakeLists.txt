cmake_minimum_required(VERSION 3.25)
project(ANSV2)

set(CMAKE_CXX_STANDARD 20)

add_executable(ANSV2 main.cpp Glue/_aux.cpp Testing/TestANSV.cpp ANSV/naive_n2_work.cpp ANSV/seq_array_n_work.cpp ANSV/seq_stack_n_work.cpp)
target_include_directories (ANSV2 PUBLIC parlaylib/include)
target_include_directories (ANSV2 PUBLIC parlaylib/examples)


add_executable(ANSV_nlogn_work ANSV/ANSV_nlogn_work.cpp ParallelMinBinaryTrees/parallelMinBinaryTreeArray.cpp)
target_include_directories(ANSV_nlogn_work PUBLIC parlaylib/include)

function(add_myFile NAME PATH)
    add_executable(${NAME} ${PATH}/${NAME}.cpp)
    target_include_directories(${NAME} PUBLIC parlaylib/include)
endfunction()

# --- dir misc: my files compiled individually ---

set(miscFiles "loopTest")
foreach(file ${miscFiles})
    add_myFile(${file} Misc)
endforeach()

# --- dir misc: my files compiled individually ---

set(myFiles "parallelMinBinaryTreeArray" "parallelMinBinaryTreePointers")
foreach(file ${myFiles})
    add_myFile(${file} ParallelMinBinaryTrees)
endforeach()


# --- FROM PARLAYLIB ---

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
