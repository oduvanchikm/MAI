#ifndef N_9_HEAPS_FIBONACCI_HEAP_H
#define N_9_HEAPS_FIBONACCI_HEAP_H
#include "../main.h"

typedef struct Fibonacci_heap_node
{
    Request* request;
    int degree;
    struct Fibonacci_heap* parent;
    struct Fibonacci_heap* child;
    struct Fibonacci_heap* left;
    struct Fibonacci_heap* right;

} Fibonacci_heap_node;

typedef struct Fibonacci_heap
{
    Fibonacci_heap_node* max_node;
    int num_nodes;

} Fibonacci_heap;

#endif //N_9_HEAPS_FIBONACCI_HEAP_H
