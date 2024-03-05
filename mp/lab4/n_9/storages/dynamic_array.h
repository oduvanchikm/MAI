#ifndef N_9_STORAGES_DYNAMIC_ARRAY_H
#define N_9_STORAGES_DYNAMIC_ARRAY_H

#include "../main.h"

typedef struct Dynamic_array
{
    int capacity; // емкость массива
    int size; // размер
    char** keys; // массив ключей
    Department* values; // массив значений (отделов)
    Department* least_load; // указатель на отдел с наименьшей нагрузкой

} Dynamic_array;

#endif