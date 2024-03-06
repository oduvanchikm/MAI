cmake_minimum_required(VERSION 3.16)
project(n_9 C)

set(CMAKE_C_STANDARD 99)

add_executable(n_9 main.c
        heaps/binary_heap.c
        heaps/fibonacci_heap.c
        heaps/binomial_heap.c
        storages/hash_set.c
        storages/binary_search_tree.c
        storages/dynamic_array.c
        logger.c
)
