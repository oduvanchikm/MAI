#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

typedef enum
{
    OK,
    INVALID_INPUT,
    ERROR_WITH_MEMORY_ALLOCATION,
    WRONG_BASE,
    INVALID_VALUE
} status_code;

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

int greatest_common_divisor(int a, int b)
{
    if (a == 0)
    {
        return b;
    }
    else if (a < 0 || b < 0)
    {
        return greatest_common_divisor(abs(a), abs(b));
    }
    else
    {
        return greatest_common_divisor(b % a, a);
    }
}

bool is_prime(int a)
{
    if (a <= 1) 
    {
        return false;
    }
    for (int i = 2; i * i <= a; i++) 
    {
        if (a % i == 0) 
        {
            return false;
        }
    }
    return true;
}

status_code prime_in_base(int base, int numerator, int denominator)
{
    for (int i = 2; i <= denominator; i++)
    {
        if(denominator % i == 0)
        {
            if(is_prime(i) && base % i != 0)
            {
                return INVALID_INPUT;
            }
        }
    }
    return OK;
}

status_code finite_representation(int** res, unsigned int base, int count, ...)
{
    if (base < 2 || base > 36 || count < 1)
    {
        return INVALID_INPUT;
    }

    *res = (int*)malloc(sizeof(int) * count);
    if (*res == NULL)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }
    
    va_list ptr;
    va_start(ptr, count);

    for (int i = 0; i < count; i++)
    {
        double value = va_arg(ptr, double);

        int numerator, denominator = 1;

        while(value > (int)value)
        {
            value *= 10;
            denominator *= 10;
        }

        numerator = (int)value; 

        int nod = greatest_common_divisor(numerator,denominator); 
        
        numerator /= nod;
        denominator /= nod;

        status_code res_prime_in_base = prime_in_base(base, numerator, denominator);
        
        if (res_prime_in_base == OK)
        {
            (*res)[i] = 1; 
        }
        else
        {
            (*res)[i] = 0; 
        }
    }
    va_end(ptr);
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
    
    int count = 2;
    int* result;
    status_code status = finite_representation(&result, base, count, 0.0002, 0.9439);

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

