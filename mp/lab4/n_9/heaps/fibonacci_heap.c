#include "fibonacci_heap.h"

Fibonacci_heap* create_heap()
{
    Fibonacci_heap* new_heap = (Fibonacci_heap*)malloc(sizeof(Fibonacci_heap));
    if (!new_heap)
    {
        return NULL;
    }

    new_heap->max_node = NULL;
    new_heap->num_nodes = 0;

    return new_heap;
}

Fibonacci_heap_node* create_node(Request* request)
{
    Fibonacci_heap_node* new_node = (Fibonacci_heap_node*)malloc(sizeof(Fibonacci_heap_node));
    if (!new_node)
    {
        return NULL;
    }

    new_node->parent = NULL;
    new_node->child = NULL;
    new_node->left = new_node;
    new_node->right = new_node;
    new_node->degree = 0;
    new_node->request = request;
}

