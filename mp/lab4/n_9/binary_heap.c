#include "binary_heap.h"

Binary_heap* create_binary_heap()
{
    Binary_heap* new_heap = (Binary_heap*)malloc(sizeof(Binary_heap));
    if (!new_heap)
    {
        return NULL;
    }

    new_heap->capacity = 10;
    new_heap->size = 0;

    new_heap->data = (Request**)malloc(sizeof(Request*));
    if (!new_heap->data)
    {
        free(new_heap);
        return NULL;
    }

    return new_heap;
}

void swap(Request** request, int index_1, int index_2)
{
    Request* temp = request[index_1];
    request[index_1] = request[index_2];
    request[index_2] = temp;
}

// 4
//5  6

void sift_up(Binary_heap* binary_heap, int index)
{
    int parent = (index - 1) / 2;

    while (index > 0 && (binary_heap->data[index]->priority > binary_heap->data[parent]->priority) ||
            (binary_heap->data[index]->priority == binary_heap->data[parent]->priority &&
            strcmp(binary_heap->data[index]->timestamp, binary_heap->data[parent]->timestamp) < 0))
    {
        swap(binary_heap->data, index, parent);
        index = parent;
        parent = (index - 1) / 2;
    }
}

status_code insert_in_binary_heap(Binary_heap* binary_heap, Request* request)
{
    if (!binary_heap)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    if (binary_heap->size == binary_heap->capacity)
    {
        binary_heap->capacity *= 2;
        binary_heap->data = (Request**)realloc(binary_heap->data, binary_heap->capacity * sizeof(Request*));
        if (!binary_heap->data)
        {
            free(binary_heap->data);
            return ERROR_WITH_MEMORY_ALLOCATION;
        }
    }

    binary_heap->data[binary_heap->size] = request;
    sift_up(binary_heap, binary_heap->size);
    binary_heap->size++;
}

void sift_down(Binary_heap* binary_heap, int index)
{
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < binary_heap->size && binary_heap->data[left]->priority < binary_heap->data[largest]->priority)
    {
        largest = left;
    }

    else if (right < binary_heap->size && binary_heap->data[right]->priority < binary_heap->data[largest]->priority)
    {
        largest = right;
    }

    if (largest != index)
    {
        swap(binary_heap->data, index, largest);
        sift_down(binary_heap, largest);
    }
}

Request* extract_max_binary_heap(Binary_heap* binary_heap)
{
    if (binary_heap->size <= 0)
    {
        return NULL;
    }

    Request* max_element = binary_heap->data[0];

    binary_heap->data[0] = binary_heap->data[binary_heap->size - 1];
    binary_heap->size--;

    sift_down(binary_heap, 0);

    return max_element;
}

void destroy_binary_heap(Binary_heap* binary_heap)
{
    if (!binary_heap)
    {
        return;
    }

    free(binary_heap->data);
    free(binary_heap);
}

void merge_binary_heaps_with_destruction(Binary_heap* binary_heap_1, Binary_heap* binary_heap_2)
{
    if (!binary_heap_1 || !binary_heap_2)
    {
        return;
    }

    for (int i = 0; i < binary_heap_2->size; i++)
    {
        insert_in_binary_heap(binary_heap_1, binary_heap_2->data[i]);
    }

    destroy_binary_heap(binary_heap_2);
}

Binary_heap* merge_binary_heaps_without_destruction(Binary_heap* binary_heap_1, Binary_heap* binary_heap_2)
{
    if (!binary_heap_1 || !binary_heap_2)
    {
        return NULL;
    }

    Binary_heap *merged_heap = create_binary_heap();

    for (int i = 0; i < binary_heap_1->size; i++)
    {
        insert_in_binary_heap(merged_heap, binary_heap_1->data[i]);
    }

    for (int i = 0; i < binary_heap_2->size; i++) {
        insert_in_binary_heap(merged_heap, binary_heap_2->data[i]);
    }

    return merged_heap;
}