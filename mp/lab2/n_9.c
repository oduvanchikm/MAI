#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdarg.h>


enum status_code
{
    OK,
    INVALID_INPUT,
    ERROR_WITH_MEMORY_ALLOCATION,
    OVERFLOW,
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

        case OVERFLOW:
            printf("Overflow\n");
            break;

        case WRONG_BASE:
            printf("This base is wrong\n");
            break;

        default:
            break;
    }
}

// проверка на то, что число с плавающей точкой
bool check_string(char *str) 
{ 
    if (strlen(str) > 6) 
    {
        return false;
    }
    int count = 0;

    if (*str == '\0') 
    {
        return false;
    }
    if (*str == '-' || *str == '+')
    {
        str++;
        if (*str == '\0') 
        {
            return false;
        }
    }
    while (*str) 
    {
        if (*str >= '0' && *str <= '9') 
        {
            str++;
            if (*str == '.') 
            {
                count += 1;
                str++;
                if (*str == '\0')
                {
                    return false;
                }
            }
            
        }
        else 
        {
            return false;
        }
    }
    if (count == 0 || count > 1)
    {
        return false;
    }
    return true;
}

// алгоритм Евклда поиска наибольшего общего делителя
int greatest_common_divisor(int first, int second) 
{
    if (first == 0) 
    {
        // **result = second;
        // return OK;
        return second;
    }

    // **result = greatest_common_divisor(second % first, first, result);

    return greatest_common_divisor(second % first, first);

    // return OK;
}




// перевод числа из десятичной в дробь, где numerator - числитель, denominator - знаменатель
enum status_code decimal_to_fraction(double num, int* numerator, int* denominator) 
{
    double remainder = num;

    int *result = (int*)malloc(sizeof(int));

    if (!result)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    *numerator = 1;
    *denominator = 1;

    while (remainder > (int)remainder) 
    {
        remainder *= 10;
        *denominator *= 10;
    }

    *numerator = (int)remainder;

    // int gcd_result;

    enum status_code gcd = greatest_common_divisor(*numerator, *denominator);

    // if (gcd == OK)
    // {
        *numerator /= gcd;
        *denominator /= gcd;
    // }

    return OK;
}

enum status_code finite_representation(char** result, int base, int count, ...) 
{
    if (base < 2 || base > 36)
    {
        return WRONG_BASE;
    }

    if (count <= 0)
    {
        return INVALID_VALUE;
    }

    *result = (char*)malloc((count + 1) * sizeof(char));

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

        char str[20];
        sprintf(str, "%f", num);

        if ((num <= 0 || num >= 1) && check_string(str)) 
        {
            return INVALID_VALUE;
        }

        int numerator = 1;
        int denominator = 1;

        enum status_code status = decimal_to_fraction(num, &numerator, &denominator);

        if (status != OK)
        {
            return INVALID_VALUE;
        }

        sprintf(*result, "%s%d/%d ", *result, numerator, denominator);

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
        return WRONG_BASE;
    }


    double num1 = 0.045;
    double num2 = 0.4737;
    double num3 = 0.2545;
    double num4 = 0.1;

    char* result;
    int count = 4;

    enum status_code status = finite_representation(&result, base, count, num1, num2, num3, num4);

    if (status != OK) 
    {
        print_errors(status);
    }

    for (int i = 0; i < count; i++) 
    {
        printf("%s\n", result);
    }

    printf("\n");

    free(result);

    return 0;
}