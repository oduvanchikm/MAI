#ifndef N_9_BINOMIAL_HEAP_H
#define N_9_BINOMIAL_HEAP_H
#include "main.h"

typedef struct Binomial_heap
{
    Request* data;
    int key;
    int degree;
    struct Binomial_heap *parent;
    struct Binomial_heap *child;
    struct Binomial_heap *sibling;
} Binomial_heap;

#endif // N_9_BINOMIAL_HEAP_H