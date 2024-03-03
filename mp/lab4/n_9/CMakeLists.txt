cmake_minimum_required(VERSION 3.16)
project(n_9 C)

set(CMAKE_C_STANDARD 99)

add_executable(n_9 main.c
        binary_heap.c
        fibonacci_heap.c
        binomial_heap.c
)
