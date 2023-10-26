#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>

#define eps 1e-12
#define MAX_ITERATIONS 10000


enum status_code
{
    OK,
    INVALID_INPUT,
    ERROR_WITH_MEMORY_ALLOCATION,
    WRONG_BASE,
    INVALID_VALUE
};

void print_errors(int flag) 
{
    switch(flag) 
    {
        case INVALID_VALUE:
            printf("Invalid value\n");
            break;

        case ERROR_WITH_MEMORY_ALLOCATION:
            printf("Error with memory allocation\n");
            break;

        case WRONG_BASE:
            printf("This base is wrong\n");
            break;

        default:
            break;
    }
}

// алгоритм Евклда поиска наибольшего общего делителя
int greatest_common_divisor(long long first, long long second) 
{
    if (first == 0) 
    {
        return second;
    }
    return greatest_common_divisor(second % first, first);
}

// перевод числа из десятичной в дробь, где numerator - числитель, denominator - знаменатель
enum status_code decimal_to_fraction(double num, long long* numerator, long long* denominator) 
{
    if (!numerator && !denominator)
    {
        return INVALID_VALUE;
    }

    double remainder = num;

    *numerator = 1;
    *denominator = 1;

    while (fabs(remainder - floor(remainder)) >= eps) 
    {
        remainder *= 10;
        *denominator *= 10;
    }

    *numerator = (long long)remainder;

    int gcd = greatest_common_divisor(*numerator, *denominator);

    *numerator /= gcd;
    *denominator /= gcd;

    return OK;
}

// если дробь имеет период, то не она не имеет конечного представления, в обратном случае, имеет
enum status_code has_finite_representation(long long numerator, long long denominator, int base, int* result) 
{
    if (base < 2 || base > 36)
    {
        return WRONG_BASE;
    }

    int iterations = 0;

    int remainder = numerator % denominator;
    int remainder_array[denominator];
    
    for (int i = 0; i < denominator; i++)
    {
        remainder_array[i] = -1; 
    }
    
    while (remainder != 0 && iterations < MAX_ITERATIONS) 
    {
        if (remainder_array[remainder] != -1 || remainder == 0)
        {
            *result = 0; 
            return OK;
        }
        
        remainder_array[remainder] = remainder;
        
        remainder *= base;
        remainder %= denominator;
        
        iterations++;
    }
    
    *result = 1;
    return OK;
}

enum status_code finite_representation(int** result, int base, int count, ...) 
{
    if (count <= 0)
    {
        return INVALID_VALUE;
    }

    *result = (int*)malloc((count + 1) * sizeof(int));

    if (!*result) 
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }
    (*result)[count] = '\0';

    va_list args;

    va_start(args, count);

    for (int i = 0; i < count; i++) 
    {
        double num = va_arg(args, double);

        long long numerator = 1;
        long long denominator = 1;

        enum status_code status = decimal_to_fraction(num, &numerator, &denominator);

        if (status != OK)
        {
            return INVALID_VALUE;
        }

        (*result)[i] = has_finite_representation(numerator, denominator, base, *result);
    }
    va_end(args);
    return OK;
}

int main() 
{
    printf("Enter the base to understand has the final representation: \n");

    int base;

    if (scanf("%d", &base) != 1)
    {
        printf("Wrong base\n");
    }

    double num1 = 0.25, num2 = 0.3;
    
    int count = 2;

    int* result;

    enum status_code status = finite_representation(&result, base, count, num1, num2);

    if (status != OK) 
    {
        print_errors(status);
    }

    for (int i = 0; i < count; i++) 
    {
        printf("Number %d: %d\n", i + 1, result[i]);
    }

    printf("\n");

    free(result);

    return 0;
}

