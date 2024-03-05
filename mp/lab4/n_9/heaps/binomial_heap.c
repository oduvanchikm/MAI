#include "binomial_heap.h"

Binomial_heap* create_node(int key, int max_priority)
{
    Binomial_heap *new_heap = (Binomial_heap*)malloc(sizeof(Binomial_heap));
    new_heap->key = key;
    new_heap->degree = max_priority;
    new_heap->parent = NULL;
    new_heap->child = NULL;
    new_heap->sibling = NULL;

    new_heap->data = (Request*)malloc(sizeof(Request));
    if (!new_heap->data)
    {
        return NULL;
    }

    return new_heap;
}

Binomial_heap* merge_heaps(Binomial_heap* heap1, Binomial_heap* heap2)
{
    if (heap1->key > heap2->key)
    {
        Binomial_heap* temp = heap1;
        heap1 = heap2;
        heap2 = temp;
    }

    heap2->parent = heap1;
    heap2->sibling = heap1->child;
    heap1->child = heap2;
    heap1->degree++;
    return heap1;
}


Binomial_heap* merge(Binomial_heap* heap1, Binomial_heap* heap2)
{
    Binomial_heap dummy;
    Binomial_heap* prev_tree = &dummy;
    dummy.sibling = NULL;

    while (heap1 != NULL && heap2 != NULL)
    {
        if (heap1->degree <= heap2->degree)
        {
            prev_tree = prev_tree->sibling = heap1;
            heap1 = heap1->sibling;
        }
        else
        {
            prev_tree = prev_tree->sibling = heap2;
            heap2 = heap2->sibling;
        }
    }

    if (heap1 != NULL)
    {
        prev_tree->sibling = heap1;
    }
    else
    {
        prev_tree->sibling = heap2;
    }

    Binomial_heap* heap = dummy.sibling;
    Binomial_heap* prev = NULL;
    Binomial_heap* curr = heap;
    Binomial_heap* next = heap->sibling;
    while (next != NULL)
    {
        if ((curr->degree != next->degree) || (next->sibling != NULL && next->sibling->degree == curr->degree))
        {
            prev = curr;
            curr = next;
        }
        else if (curr->key <= next->key)
        {
            curr->sibling = next->sibling;
            curr = merge_heaps(curr, next);
        }
        else
        {
            if (prev == NULL)
            {
                heap = next;
            }
            else
            {
                prev->sibling = next;
            }
            curr = merge_heaps(next, curr);
        }
        next = curr->sibling;
    }

    return heap;
}

Binomial_heap* insert(Binomial_heap* heap, int key, int max_priority)
{
    Binomial_heap* node = create_node(key, max_priority);
    return merge(heap, node);
}

Binomial_heap* extract_min(Binomial_heap** heap)
{
    Binomial_heap* min = NULL;
    Binomial_heap* prev = NULL;
    Binomial_heap* current = *heap;
    Binomial_heap* prev_to_del = NULL;

    Binomial_heap* temp = *heap;
    while (temp != NULL)
    {
        if (min == NULL || temp->key < min->key)
        {
            min = temp;
            prev = prev_to_del;
        }
        prev_to_del = temp;
        temp = temp->sibling;
    }

    if (prev == NULL)
    {
        *heap = min->sibling;
    }
    else
    {
        prev->sibling = min->sibling;
    }

    Binomial_heap* child = min->child;
    while (child != NULL)
    {
        Binomial_heap* next = child->sibling;
        child->sibling = NULL;
        child->parent = NULL;
        *heap = merge(child, *heap);
        child = next;
    }

    return min;
}