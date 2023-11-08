#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum status_code 
{
    OK,
    ERROR_WITH_MEMORY_ALLOCATION,
    WRONG_ARGUMENT,
    WRONG_BASE
};

void print_errors(int error)
{
    switch(error)
    {
        case ERROR_WITH_MEMORY_ALLOCATION:
            printf("Error with memory allocation\n");
            break;

        case WRONG_BASE:
            printf("Wrong base\n");
            break;

        case WRONG_ARGUMENT:
            printf("This is wrong\n");
            break;

        default:
            break;
    }
}

int sum_digits(long long int number1, long long int number2) 
{
    long long int sum = 0;
    long long int carry = 0;

    sum = number1 ^ number2;
    carry = (number1 & number2) << 1;

    while (carry > 0) 
    {
        long long int tmp = sum;
        sum = sum ^ carry;
        carry = (tmp & carry) << 1;
    }
    return sum;
}

int negative_digit(int number) 
{
    return sum_digits(~number, 1);
}

int subtraction(int number1, int number2) 
{
    return sum_digits(number1, negative_digit(number2));
}

enum status_code converting_number(long long int number, unsigned int r, char** result)
{
    int remainder = 0;

    if (r < 1 || r > 5)
    {
        return WRONG_BASE;
    }

    int count = 0;
    int flag = 0;
    

    if (number < 0)
    {
        number = negative_digit(number);
        count = sum_digits(count, 1);
        flag = 1;
    }

    long long int new_number = number;

    while (new_number > 0)
    {
        count = sum_digits(count, 1);
        new_number >>= r;
    }

    if (flag)
    {
        *result = (char*)malloc(sizeof(char) * sum_digits(count, 1));

        if (*result == NULL)
        {
            return ERROR_WITH_MEMORY_ALLOCATION;
        }

        (*result)[count] = '\0';
        (*result)[0] = '-';
    }

    else 
    {
        *result = (char*)malloc(sizeof(char) * sum_digits(count, 1));
        if (*result == NULL)
        {
            return ERROR_WITH_MEMORY_ALLOCATION;
        }
        (*result)[count] = '\0';
    }
    while (number)
    {
        remainder = number & subtraction((1 << r), 1);
        count = subtraction(count, 1);
        (*result)[count] = (remainder < 10) ? sum_digits(remainder, '0') : subtraction(sum_digits(remainder, 'A'), 10);
        number >>= r;
    }
    return OK;
}

int main()
{
    long long int number;
    printf("Enter a digit in 10 in decimal notation: \n");

    if (scanf("%lld", &number) != 1)
    {
        return WRONG_ARGUMENT;
    }

    int r;
    printf("Enter degree of 2: \n");

    if (scanf("%d", &r) != 1)
    {
        return WRONG_BASE;
    }

    char* result = NULL;

    enum status_code n = converting_number(number, r, &result);
    if (n == OK)
    {
        printf("A %lld in %d system: \n", number, 1 << r);
        printf("%s\n", result);
    }
    else
    {
        print_errors(n);
    }
    free(result);
}
