cmake_minimum_required(VERSION 3.16)
project(ANSV2)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(ANSV2
        main.cpp
        Glue/_aux.cpp
        Glue/data.cpp
        Testing/TestANSV.cpp
        ANSV/naive_n2_work.cpp
        ANSV/seq_array_n_work.cpp
        ANSV/seq_stack_n_work.cpp
        ANSV/nlogn_work_mine.cpp
        ParallelMinBinaryTrees/parallelMinBinaryTreeArray.cpp
        ANSV/berkmanOptimal.cpp
        Experiments/experiments.cpp
        ANSV/shunZhaoOriginal.cpp
        Misc/test.cpp
)
target_include_directories (ANSV2 PUBLIC parlaylib/include)
target_include_directories (ANSV2 PUBLIC parlaylib/examples)

target_link_libraries(ANSV2 PRIVATE pthread)