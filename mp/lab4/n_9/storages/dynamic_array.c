#include "dynamic_array.h"

Dynamic_array* create_dynamic_array(int capacity)
{
    Dynamic_array* new_array = (Dynamic_array*)malloc(sizeof(Dynamic_array));
    if (!new_array)
    {
        return NULL;
    }

    new_array->capacity = capacity;
    new_array->size = 0;
    new_array->values = (Department*)malloc(sizeof(Department));
    if (!new_array->values)
    {
        free(new_array);
        return NULL;
    }

    new_array->keys = (char**)malloc(sizeof(char));
    if (!new_array->keys)
    {
        free(new_array);
        free(new_array->values);
        return NULL;
    }

    new_array->least_load = NULL;

    return new_array;
}

int binary_search(Dynamic_array* dynamic_array, char* key)
{
    int low = 0;
    int high = dynamic_array->size - 1;

    while (low <= high)
    {
        int middle = (low + high) / 2;

        if (strcmp(dynamic_array->keys[middle], key) < 0)
        {
            low = middle + 1;
        }
        else if (strcmp(dynamic_array->keys[middle], key) > 0)
        {
            high = middle - 1;
        }
        else
        {
            return middle;
        }
    }

    return -1;
}

void insert_in_dynamic_array(Dynamic_array* dynamic_array, char* key, Department value)
{
    if (dynamic_array->size == dynamic_array->capacity)
    {
        dynamic_array->capacity *= 2;
        dynamic_array->keys = (char**)realloc(dynamic_array->keys, dynamic_array->capacity * sizeof(char*));
        if (!dynamic_array->keys)
        {
            return;
        }

        dynamic_array->values = (Department*)realloc(dynamic_array->values, dynamic_array->capacity * sizeof(Department));
        if (dynamic_array->values)
        {
            free(dynamic_array->keys);
            return;
        }
    }

    int i = dynamic_array->size - 1;
    while (i >= 0 && strcmp(key, dynamic_array->keys[i]) < 0)
    {
        dynamic_array->keys[i + 1] = dynamic_array->keys[i];
        dynamic_array->values[i + 1] = dynamic_array->values[i];
        i--;
    }

    dynamic_array->keys[i + 1] = strdup(key);
    if (!dynamic_array->keys[i + 1])
    {
        return;
    }

    dynamic_array->values[i + 1] = value;
    dynamic_array->size++;
}

Department* search(Dynamic_array* dynamic_array, char* key)
{
    int index = binary_search(key, dynamic_array->keys);

    if (index != -1)
    {
        return &(dynamic_array->values[index]);
    }
    else
    {
        return NULL;
    }
}

void free_dynamic_array(Dynamic_array* dynamic_array)
{
    for (int i = 0; i < dynamic_array->size; i++)
    {
        free(dynamic_array->keys[i]);
    }

    free(dynamic_array->keys);
    free(dynamic_array->values);
    free(dynamic_array);
}