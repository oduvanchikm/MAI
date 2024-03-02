#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H
#include "main.h"

typedef struct Min_binary_heap
{
    Request* data;
    int capacity;
    int size;
} Min_binary_heap;

Min_binary_heap* create_heap(int max_priority);
void swap(Request* first, Request* second);
void sift_up(Min_binary_heap* heap, int index);
void insert(Min_binary_heap* heap, int priority);
void sift_down(Min_binary_heap* heap, int index);
int delete_min(Min_binary_heap* heap);
Request* extract_min(Min_binary_heap* heap);
void destroy_heap(Min_binary_heap* heap);
Min_binary_heap* merge_heaps_with_destruction(Min_binary_heap* heap_1, Min_binary_heap* heap_2);
Min_binary_heap* merge_heaps_without_destruction(Min_binary_heap* heap_1, Min_binary_heap* heap_2);


#endif
