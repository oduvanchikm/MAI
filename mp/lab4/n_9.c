#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

typedef enum
{
    OK,
    ERROR_WITH_MEMORY_ALLOCATION,
    INVALID_INPUT,
    ERROR_WITH_COUNT_OF_ARGUMENTS,
    ERROR_WITH_OPENING_FILE,
    NEGATIVE_DIGIT,
    WRONG_COUNT_OF_BRACKETS,
    OVERFLOW,

} status_code;

void print_errors(int flag)
{
    switch (flag)
    {
        case ERROR_WITH_COUNT_OF_ARGUMENTS:
            printf("Error with count of arguments\n");
            break;

        case ERROR_WITH_MEMORY_ALLOCATION:
            printf("Error with memory allocation\n");
            break;

        case INVALID_INPUT:
            printf("Invalid input\n");
            break;

        case ERROR_WITH_OPENING_FILE:
            printf("Error with opening file\n");
            break;

        case NEGATIVE_DIGIT:
            printf("It's a negativ digit\n");
            break;

        case WRONG_COUNT_OF_BRACKETS:
            printf("Wrong count of brackets\n");
            break;

        case OVERFLOW:
            printf("It's very big digit\n");
            break;

        default:
            break;
    }
}

typedef struct Request
{
    char* timestamp;
    int priority;
    int department_id;
    char* text;
} Request;

typedef struct Operator
{
    int id;
    int processing_time_min;
} Operator;

typedef struct Info
{
    char heap_type[100];
    char set_type[100];
    char date_of_start[100];
    char date_of_end[100];
    int min_time;
    int max_time;
    int count_of_depatment;
    char count_of_operators[100];
    double overload_coef;
} Info;

typedef struct Log
{
    char* timestamp;
    int code;
    char* description;
} Log;

//typedef struct Request
//{
//    int priority;
//    int key;
//} Request;


//---------------------------------------------------------------------------------------------
// Min binary heap
//---------------------------------------------------------------------------------------------

typedef struct Min_binary_heap
{
    Request* data;
    int capacity;
    int size;
} Min_binary_heap;

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

Info read_data_from_first_file(FILE* file)
{
    Info data;
    fscanf(file, "%s", data.heap_type);
    fscanf(file, "%s", data.set_type);
    fscanf(file, "%s", data.date_of_start);
    fscanf(file, "%s", data.date_of_end);
    fscanf(file, "%d", &(data.min_time));
    fscanf(file, "%d", &(data.max_time));
    fscanf(file, "%d", &(data.count_of_depatment));
    fscanf(file, "%s", data.count_of_operators);
    fscanf(file, "%lf", &(data.overload_coef));
    fclose(file);
    return data;
}

status_code info_from_first_file(FILE* file)
{
    Info data = read_data_from_first_file(file);

    if (strcmp(data.heap_type, "BinaryHeap") == 0)
    {
        printf("good\n");
    }

    else if (strcmp(data.heap_type, "BinomalHeap") == 0)
    {
        printf("binomail\n");
    }

    else if (strcmp(data.heap_type, "FibonacciHeap") == 0)
    {
        printf("binomail\n");
    }

    else if (strcmp(data.heap_type, "SkewHeap") == 0)
    {
        printf("binomail\n");
    }

    else if (strcmp(data.heap_type, "LeftistHeap") == 0)
    {
        printf("binomail\n");
    }

    else if (strcmp(data.heap_type, "Treap") == 0)
    {
        printf("binomail\n");
    }
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("Error with number of arguments\n");
        return 1;
    }

    int max_priority = atoi(argv[1]);
    char *file_path = argv[2];

    FILE* file = fopen(file_path, "r");
    if (!file)
    {
        printf("Error with opnening file\n");
        return 1;
    }

    status_code st = info_from_first_file(file);


    // Чтение информации о структуре данных из файла

    // Создание соответствующей структуры данных

    // Реализация операций для выбранной структуры данных

    // Моделирование работы центра клиентской поддержки

    fclose(file);

    return 0;
}
