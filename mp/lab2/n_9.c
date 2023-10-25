#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>


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
        return second;
    }

    return greatest_common_divisor(second % first, first);
}

// проверка, что число простое
bool is_prime(int num) 
{
    if (num > 1) 
    {
        for (int i = 2; i < sqrt(num); i++)

            if (num % i == 0)

                return false;

        return true;
    }

    else

        return false;
}

// является ли число base простым по основанию numerator 
// и показателю denominator
bool prime_in_base(int base, int numerator, int denominator) 
{
    int i = 2;

    while (denominator > 1) 
    {
        if (denominator % i == 0) 
        {
            if (is_prime(i) && base % i != 0) 
            {
                return false;
            }
            denominator /= i;
        } 
        else 
        {
            i++;
        }
    }

    return true;
}

// перевод числа из десятичной в дробь, где numerator - числитель, denominator - знаменатель
enum status_code decimal_to_fraction(double num, int* numerator, int* denominator) 
{
    double remainder = num;

    *numerator = 1;
    *denominator = 1;

    while (remainder > (int)remainder) 
    {
        remainder *= 10;
        *denominator *= 10;
    }

    *numerator = (int)remainder;


    int gcd = greatest_common_divisor(*numerator, *denominator);


    *numerator /= gcd;
    *denominator /= gcd;


    return OK;
}

// 
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

        (*result)[i] = prime_in_base(base, numerator, denominator);
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

    double num1 = -0.3455, num2 = 0.32433, num3 = -0.1, num4 = 0.343445, num5 = 0.13333;
    
    int count = 5;

    char* result;

    enum status_code status = finite_representation(&result, base, count, num1, num2, num3, num4, num5);

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