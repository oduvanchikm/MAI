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

#include "binary_heap.h"


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

typedef struct Storage_of_applications
{
    Request* requests;
    int num_requests;

} Storage_of_applications;

typedef struct Operator
{
    int processing_time; // время, за которое обрабатывается заявка
    char* name; // имя
    int is_free; // свободен ли сейчас оператор
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
    char** count_of_operators;
    double overload_coef;
} Info;

typedef struct Department
{
    Operator* operators;
    int count_of_operators;
    void* data_structure; // указатель на структуру, в которой хранятся заявки
} Department;

//typedef struct Log
//{
//    char* timestamp;
//    char* code;
//    char* description;
//} Log;

Info* read_data_from_first_file(FILE* file);
//storage_of_applications choosing_data_structure(Info* data);


#endif