#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

#include "logger.h"

#include "heaps/binary_heap.h"
#include "heaps/binomial_heap.h"
#include "heaps/fibonacci_heap.h"

#include "storages/binary_search_tree.h"
#include "storages/dynamic_array.h"
#include "storages/hash_set.h"

typedef enum
{
    OK,
    ERROR_WITH_MEMORY_ALLOCATION,
    INVALID_INPUT,
    ERROR_WITH_COUNT_OF_ARGUMENTS,
    ERROR_WITH_OPENING_FILE,

} status_code;

typedef enum
{
    BINARY_HEAP,
    BINOMIAL_HEAP,
    FIBONACCI_HEAP,
    SKEW_HEAP,
    LEFTIST_HEAP,
    TREAP, // декартово дерево
    INVALID_STRUCTURE

} heap_structure;

typedef enum
{
    HASH_SET,
    DYNAMIC_ARRAY,
    BINARY_SEARCH_TREE,
    TRIE,
    INVALID_SET

} set_structures;

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

        default:
            break;
    }
}

typedef struct Request
{
    char timestamp[35]; // время добавления
    int priority; // приоритет заявки
    char department_id[10]; // индентификатор, в какое отделение отправляется заявка
    char* text; // текст заявления

} Request;

typedef struct Operator
{
    int processing_time; // время, за которое обрабатывается заявка
    char* name; // имя
    int start_time; // время начала работы
    Request* request; // заявка, которая сейчас в обработке
} Operator;

typedef struct Info_from_first_file
{
    char date_of_start[100];
    char date_of_end[100];
    int min_time;
    int max_time;
    int count_of_departments;

} Info_from_first_file;

typedef struct Department
{
    Operator* operators;
    int count_of_operators; // количество операторов
    int count_of_requests; // количество оставшихся заявок
    void* data_structure; // указатель на структуру, в которой хранятся заявки
    double overload_coef;
    int is_overload;

} Department;

//typedef struct Log
//{
//    char* timestamp;
//    char* code;
//    char* description;
//} Log;

//Info* read_data_from_first_file(FILE* file);
//storage_of_applications choosing_data_structure(Info* data);


#endif