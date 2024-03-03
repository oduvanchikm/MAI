#ifndef N_9_BINARY_HEAP_H
#define N_9_BINARY_HEAP_H
#include "main.h"

typedef struct Binary_heap
{
    Request** data;
    int capacity;
    int size;

} Binary_heap;

Binary_heap* create_binary_heap();
void swap(Request** request, int index_1, int index_2);
void sift_up(Binary_heap* binary_heap, int index);
status_code insert_in_binary_heap(Binary_heap* binary_heap, Request* request);
void sift_down(Binary_heap* binary_heap, int index);
Request* extract_max_binary_heap(Binary_heap* binary_heap);
void destroy_binary_heap(Binary_heap* binary_heap);
void merge_binary_heaps_with_destruction(Binary_heap* binary_heap_1, Binary_heap* binary_heap_2);
Binary_heap* merge_binary_heaps_without_destruction(Binary_heap* binary_heap_1, Binary_heap* binary_heap_2);


#endif // N_9_BINARY_HEAP_H
