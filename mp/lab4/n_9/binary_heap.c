#include "binary_heap.h"

Min_binary_heap* create_heap(int max_priority)
{
    Min_binary_heap* new_heap = (Min_binary_heap*)malloc(sizeof(Min_binary_heap));
    if (!new_heap)
    {
        return NULL;
    }

    new_heap->capacity = max_priority;
    new_heap->size = 0;
    new_heap->data = (Request*)malloc(sizeof(Request));
    if (!new_heap->data)
    {
        return NULL;
    }

    return new_heap;
}

void swap(Request* first, Request* second)
{
    Request temp = *first;
    *first = *second;
    *second = temp;
}

// 4
//5  6

void sift_up(Min_binary_heap* heap, int index)
{
    if (index > 0 && heap->data[index].priority < heap->data[(index - 1) / 2].priority)
    {
        swap(&heap->data[index].priority, &heap->data[(index - 1) / 2].priority);
        index = (index - 1) / 2;
    }
}

void insert(Min_binary_heap* heap, int priority)
{
    if (!heap)
    {
        return;
    }

    if (heap->size == heap->capacity)
    {
        return;
    }

    heap->data[heap->size].priority = priority;
    sift_up(heap, heap->size);
    heap->size++;
}

void sift_down(Min_binary_heap* heap, int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap-> size && heap->data[left].priority < heap->data[smallest].priority)
    {
        smallest = left;
    }

    else if (right < heap-> size && heap->data[right].priority < heap->data[smallest].priority)
    {
        smallest = right;
    }

    if (smallest != index)
    {
        swap(&heap->data[index].priority, &heap->data[smallest].priority);
        sift_down(heap, smallest);
    }
}

int delete_min(Min_binary_heap* heap)
{
    if (heap->size == 0)
    {
        return -1;
    }

    int min = heap->data[0].priority;
    heap->data[0].priority = heap->data[heap->size - 1].priority;
    heap->size--;
    sift_down(heap, 0);
    return min;
}

Request* extract_min(Min_binary_heap* heap)
{
    if (heap->size <= 0)
    {
        return NULL;
    }

    Request* min_element = &heap->data[0].priority;

    heap->data[0].priority = heap->data[heap->size - 1].priority;
    heap->size--;

    sift_down(heap, 0);

    return min_element;
}

void destroy_heap(Min_binary_heap* heap)
{
    if (!heap)
    {
        return;
    }

    free(heap->data);
    free(heap);
}

Min_binary_heap* merge_heaps_with_destruction(Min_binary_heap* heap_1, Min_binary_heap* heap_2)
{
    if (!heap_1 || !heap_2)
    {
        return NULL;
    }

    Min_binary_heap* new_heap = create_heap(heap_1->capacity + heap_2->capacity);

    for(int i = 0; i < heap_1->size; i++)
    {
        new_heap->data[i].priority = heap_1->data[i].priority;
    }

    for (int i = 0; i < heap_2->size; i++)
    {
        new_heap->data[heap_1->size + i].priority = heap_2->data[i].priority;
    }

    new_heap->size = heap_1->size + heap_2->size;

    sift_up(new_heap, 0);
    destroy_heap(heap_1);
    destroy_heap(heap_2);

    return new_heap;
}

Min_binary_heap* merge_heaps_without_destruction(Min_binary_heap* heap_1, Min_binary_heap* heap_2)
{
    if (!heap_1 || !heap_2)
    {
        return NULL;
    }

    Min_binary_heap* new_heap = create_heap(heap_1->capacity + heap_2->capacity);

    for(int i = 0; i < heap_1->size; i++)
    {
        new_heap->data[i].priority = heap_1->data[i].priority;
    }

    for (int i = 0; i < heap_2->size; i++)
    {
        new_heap->data[heap_1->size + i].priority = heap_2->data[i].priority;
    }

    new_heap->size = heap_1->size + heap_2->size;

    sift_up(new_heap, 0);
    return new_heap;
}