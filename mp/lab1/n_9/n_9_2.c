#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>

typedef enum 
{
    OK,
    ERROR_WITH_INVALID_ARGUMENT,
    ERROR_WITH_MEMORY_ALLOCATION
} status_code;

void print_errors(int flag)
{
    switch (flag)
    {
    case ERROR_WITH_INVALID_ARGUMENT:
        printf("Invalid value\n");
        break;

    case ERROR_WITH_MEMORY_ALLOCATION:
        printf("Error with memory allocation\n");
        break;

    default:
        break;
    }
}

int generate_random_array(int **array, int size, int min, int max) 
{
    *array = (int*)malloc(sizeof(int) * size);

    if (!(*array))
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    for (int i = 0; i < size; i++)
    {
        (*array)[i] = rand() % (max - min + 1) + min;
    }

    return OK;
}

int find_closest_value(int size, int num, int *array, int *out_digit)
{
    int closest_value = array[0];
    int min_diff = INT_MAX;

    for (int i = 0; i < size; i++)
    {
        if (abs(num - array[i]) < min_diff)
        {
            closest_value = array[i];
            min_diff = abs(num - array[i]);
        }
    }

    *out_digit = closest_value;

    return OK;
}
 
int generate_new_array(int *a_array, int *b_array, int **c_array, int c_size, int a_size, int b_size)
{
    *c_array = (int*)malloc(sizeof(int) * a_size);

    if (!(*c_array))
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    for (int i = 0; i < a_size; i++)
    {
        int closest_value;
        find_closest_value(b_size, a_array[i], b_array, &closest_value);
        (*c_array)[i] = a_array[i] + closest_value;
    }

    return OK;
}

int main()
{
    srand(time(NULL));

    int a_size = rand() % 9991 + 10;
    int b_size = rand() % (10000 - 10 + 1) + 10;

    int *a_array;
    int *b_array;
    int *c_array;

    int st_random_a = generate_random_array(&a_array, a_size, -1000, 1000);

    if (st_random_a == ERROR_WITH_MEMORY_ALLOCATION)
    {
        print_errors(st_random_a);
        exit(1);
    }

    int st_random_b = generate_random_array(&b_array, b_size, -1000, 1000);

    if (st_random_b == ERROR_WITH_MEMORY_ALLOCATION)
    {
        print_errors(st_random_b);
        exit(1);
    }

    printf("array a: ");

    for (int i = 0; i < a_size; i++)
    {
        printf("%d ", a_array[i]);
    }

    printf("\n\n");

    printf("array b: ");

    for (int i = 0; i < b_size; i++)
    {
        printf("%d ", b_array[i]);
    }
    
    printf("\n\n");

    int st_new = generate_new_array(a_array, b_array, &c_array, a_size, a_size, b_size);

    if (st_new == ERROR_WITH_MEMORY_ALLOCATION)
    {
        print_errors(st_new);
        free(a_array);
        free(b_array);
        exit(1);
    }

    printf("array c: ");
    
    for (int i = 0; i < a_size; i++)
    {
        printf("%d ", c_array[i]);
    }
    
    printf("\n\n");

    free(a_array);
    free(b_array);
    free(c_array);

    return 0;
}

