#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

enum status_code 
{
    OK,
    ERROR_WITH_INVALID_ARGUMENT
};

void fill_array(int *digits_array, int a, int b, int size)
{
    for (int i = 0; i < size; i++)
    {
        digits_array[i] = rand() % (b - a + 1) + a;
    }
}

void swap(int *max, int *min)
{
    int temp = *max;
    *max = *min;
    *min = temp;
}

void find_max_min_element(int *digits_array, int *max, int *min, int size)
{
    if (size < 1)
    {
        return;
    }

    int max_index = 0;
    int min_index = 0;

    for (int i = 0; i < size; i++)
    {
        if (digits_array[i] < digits_array[min_index])
        {
            min_index = i;
        }

        if (digits_array[i] > digits_array[max_index])
        {
            max_index = i;
        }
    }

    if (min_index != max_index)
    {
        swap(&digits_array[min_index], &digits_array[max_index]);
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2 || argc > 3)
    {
        printf("Invalid number of arguments\n");
        printf("Please enter two numbers a and b, which are the left and right boundaries of the range\n");
        exit(1);
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    if (a > b)
    {
        printf("Error, invalid range\n");
        return 0;
    }

    srand(time(NULL));

    int size = 10;

    int *array_for_digits;

    fill_array(array_for_digits, a, b, size);

    printf("Your array:\n");

    for (int i = 0; i < size; i++)
    {
        printf("%d ", array_for_digits[i]);
    }
    printf("\n");

    int max_digit;
    int min_digit;

    find_max_min_element(array_for_digits, &max_digit, &min_digit, size);

    printf("Result:\n");

    for (int i = 0; i < size; i++)
    {
        printf("%d ", array_for_digits[i]);
    }
    printf("\n");

    return 0;
}