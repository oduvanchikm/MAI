#include "lab.h"

status_code roman_digits_flag(int num, char **result)
{
    int roman_value[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char* roman_char[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    int len = sizeof(roman_value) / sizeof(roman_value[0]);

    *result = (char*)malloc(sizeof(char) * (len + 1));

    if (!(*result))
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    (*result)[0] = '\0';

    for (int i = 0; i < len; i++)
    {
        if (num < 0)
        {
            (*result)[0] = '-';
            i++;
            num = abs(num);
        }
        else
        {
            while (num >= roman_value[i])
            {
                num -= roman_value[i];

                strcat(*result, roman_char[i]);
            }
        }
    }
    return OK;
}

int fibonacci(int n)
{
    if (n <= 1)
    {
        return n;
    }
    else
    {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

status_code zecedorf_representation(unsigned int num, char **result)
{
    if (num == 0)
    {
        *result = (char*)malloc(sizeof(char) * 3);

        if (!(*result))
        {
            return ERROR_WITH_MEMORY_ALLOCATION;
        }

        (*result)[0] = '0';
        (*result)[1] = '1';
        (*result)[2] = '\0';
    }
    else
    {
        int fib_num = 0;
        int fib_index = 0;
        int count = 0;

        while (fib_num <= num)
        {
            fib_num = fibonacci(fib_index);
            fib_index++;
            count++;
        }

        *result = (char*)malloc(sizeof(char) * (count + 1));

        if (!(*result))
        {
            return ERROR_WITH_MEMORY_ALLOCATION;
        }

        for (int i = 0; i < count; i++)
        {
            (*result)[i] = '0';
        }

        int index = fib_index - 3;
        while (num > 0)
        {
            while (fibonacci(index) > num)
            {
                index--;
            }
            num -= fibonacci(index);
            (*result)[index] = '1';
        }
        
        (*result)[fib_num] = '\0';
    }
    return OK;
}

int my_strlen(int number, int base)
{
    int count = 0;
    if (number < 0)
    {
        count++;
        number *= -1;
    }

    while (number > 0)
    {
        number /= base;
        count++;
    }

    return count;
}

status_code decemal_to_other_base_l(char **result, int number, int base)
{
    if (base < 2 || base > 36)
    {
        base = 10;
    }
    int len = my_strlen(number, base);
    int sign = 1;
    
    if (number < 0)
    {
        sign = -1;
        number *= -1;
    }

    int r;
    char *buffer = (char*)malloc(sizeof(char) * (len + 1));

    if (!buffer)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    char* ptr = buffer + len;
    *ptr = '\0';

    while(number > 0)
    {
        r = number % base;
        *--ptr = (r > 9) ? r - 10 + 'a' : r + '0';
        number /= base;
    }

    if (sign == -1)
    {
        *--ptr = '-';
    }

    *result = buffer;

    return OK;
}

status_code decemal_to_other_base_h(char **result, int number, int base)
{
    if (base < 2 || base > 36)
    {
        base = 10;
    }
    int len = my_strlen(number, base);
    int sign = 1;
    if (number < 0)
    {
        sign = -1;
        number *= -1;
    }
    int r;
    char *buffer = (char*)malloc(sizeof(char) * (len + 1));

    if (!buffer)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    char* ptr = buffer + len;
    *ptr = '\0';

    while(number > 0)
    {
        r = number % base;
        *--ptr = (r > 9)? r - 10 + 'A' : r + '0';
        number /= base;
    }

    if (sign == -1)
    {
        *--ptr = '-';
    }

    *result = buffer;

    return OK;
}

int other_base_to_ten_h(char* number, int base)
{
    if (!number)
    {
        return INVALID_ARGUMENT;
    }

    int symbol = 1;
    char *ptr = NULL;
    int result = 0;

    if (*number == '-')
    {
        symbol = -1;
        ptr = number + 1;
    }
    else
    {
        ptr = number;
    }
    while (*ptr)
    {
        result = result * base + (isdigit(*ptr) ? *ptr  - '0' : *ptr - 'A' + 10);
        ptr++;
    }
    return result * symbol;
}

int other_base_to_ten_l(char* number, int base)
{
    if (!number)
    {
        return INVALID_ARGUMENT;
    }

    int symbol = 1;
    char *ptr = NULL;
    int result = 0;

    if (*number == '-')
    {
        symbol = -1;
        ptr = number + 1;
    }
    else
    {
        ptr = number;
    }
    while (*ptr)
    {
        result = result * base + (isdigit(*ptr) ? *ptr  - '0' : *ptr - 'a' + 10);
        ptr++;
    }

    return result * symbol;
}

status_code print_dump_memory(char **result, void *num, size_t size)
{
    unsigned char *bytes = (unsigned char*)num;
    unsigned char *buffer = (unsigned char*) malloc((size * 8 + 1) * sizeof(unsigned char));

    if (!buffer)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    buffer[size * 8] = '\0';

    int k = 0;

    for (size_t i = 0; i < size; ++i)
    {
        for (int j = 7; j >= 0; --j)
        {
            unsigned char bit = (bytes[i] >> j) & 1;
            buffer[k++] = bit + '0';
        }
    }
    *result = buffer;
    return OK;
}