#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>

typedef enum
{
    OK,
    INVALID_ARGUMENT,
    ERROR_WITH_MEMORY_ALLOCATION

} status_code;

void print_errors(int flag)
{
    switch(flag)
    {
        case ERROR_WITH_MEMORY_ALLOCATION:
            printf("Error with memory allocation\n");
            break;

        case INVALID_ARGUMENT:
            printf("This is wrong\n");
            break;

        default:
            break;
    }
}

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
        *--ptr = (r > 9)? r - 10 + 'a' : r + '0';
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

bool is_low(char string)
{
    if (string >= 'a' && string <= 'z')
    {
        return true;
    }
    return false;
}

bool is_high(char string)
{
    if (string >= 'A' && string <= 'Z')
    {
        return true;
    }
    return false;
}

int other_base_to_ten_h(char* number, int base)
{
    if (!number)
    {
        return INVALID_ARGUMENT;
    }

    if (!is_high(*number))
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

    if (!is_low(*number))
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

void overfprintf(FILE *file, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    int index = 0;

    while (format[index] != '\0')
    {
        if (format[index] != '%')
        {
            fprintf(file, "%c", format[index]);
            index++;
        }
        else
        {
            int next_index = index + 1;

            if (format[next_index] == '%')
            {
                fprintf(file, "%c", '%');
                index = next_index + 1;
            }
            else
            {
                char flag[25];
                int flag_index = 0;
                flag[flag_index++] = '%';

                while (format[next_index] != '\0' && (isalnum(format[next_index])) || format[next_index] == '.')
                {
                    char c = format[next_index];
                    flag[flag_index] = c;
                    next_index++;
                    flag_index++;
                }

                flag[flag_index] = '\0';

                if (strcmp(flag, "%Ro") == 0)
                {
                    char* roman_result = NULL;
                    int arg = va_arg(args, int);
                    status_code st_roman = roman_digits_flag(arg, &roman_result);
                    if (st_roman == OK)
                    {
                        fprintf(file, "%s", roman_result);
                    }
                    else
                    {
                        print_errors(st_roman);
                    }
                    free(roman_result);
                }

                else if (strcmp(flag, "%Zr") == 0)
                 {
                     char* zeck_result = NULL;
                     unsigned int arg = va_arg(args, unsigned int);
                     status_code st_zc = zecedorf_representation(arg, &zeck_result);
                     if (st_zc == OK)
                     {
                         fprintf(file, "%s", zeck_result);
                     }
                     else
                     {
                         print_errors(st_zc);
                     }
                     free(zeck_result);
                 }

                else if (strcmp(flag, "%Cv") == 0)
                {
                    char* Cv_result = NULL;
                    int arg = va_arg(args, int);
                    int system = va_arg(args, int);
                    status_code Cv_st = decemal_to_other_base_l(&Cv_result, arg, system);

                    if (Cv_st == OK)
                    {
                        fprintf(file, "%s", Cv_result);
                    }

                    else
                    {
                        print_errors(Cv_st);
                    }
                    free(Cv_result);
                }

                else if (strcmp(flag, "%CV") == 0)
                {
                    char* CV_result = NULL;
                    int arg = va_arg(args, int);
                    int system = va_arg(args, int);
                    status_code CV_st = decemal_to_other_base_h(&CV_result, arg, system);

                    if (CV_st == OK)
                    {
                        fprintf(file, "%s", CV_result);
                    }
                    else
                    {
                        print_errors(CV_st);
                    }
                    free(CV_result);
                }

                else if (strcmp(flag, "%to") == 0)
                {
                    char* arg = va_arg(args, char*);
                    int system = va_arg(args, int);
                    int to_st = other_base_to_ten_l(arg, system);
                    fprintf(file, "%d", to_st);
                }

                else if (strcmp(flag, "%TO") == 0)
                {
                    char* arg = va_arg(args, char*);
                    int system = va_arg(args, int);
                    int TO_st = other_base_to_ten_h(arg, system);
                    fprintf(file, "%d", TO_st);
                }

                else if (strcmp(flag, "%mi") == 0)
                {
                    char *mi_result = NULL;
                    int arg = va_arg(args, int);
                    status_code mi_st = print_dump_memory(&mi_result, &arg, sizeof(arg));

                    if (mi_st == OK)
                    {
                        fprintf(file, "%s", mi_result);
                    }
                    else
                    {
                        print_errors(mi_st);
                    }
                    free(mi_result);
                }

                else if (strcmp(flag, "%mu") == 0)
                {
                    char *mu_result = NULL;
                    unsigned int arg = va_arg(args, unsigned int);
                    status_code mu_st = print_dump_memory(&mu_result, &arg, sizeof(arg));

                    if (mu_st == OK)
                    {
                        fprintf(file, "%s", mu_result);
                    }
                    else
                    {
                        print_errors(mu_st);
                    }
                    free(mu_result);
                }

                else if (strcmp(flag, "%md") == 0)
                {
                    char *md_result = NULL;
                    double arg = va_arg(args, double);
                    status_code md_st = print_dump_memory(&md_result, &arg, sizeof(arg));

                    if (md_st == OK)
                    {
                        fprintf(file, "%s", md_result);
                    }
                    else
                    {
                        print_errors(md_st);
                    }
                    free(md_result);
                }

                else if (strcmp(flag, "%mf") == 0)
                {
                    char *mf_result = NULL;
                    float arg = va_arg(args, double);
                    status_code mf_st = print_dump_memory(&mf_result, &arg, sizeof(arg));

                    if (mf_st == OK)
                    {
                        fprintf(file, "%s", mf_result);
                    }
                    else
                    {
                        print_errors(mf_st);
                    }
                    free(mf_result);
                }

                else
                {
                    if (strcmp(flag, "%n") == 0)
                    {
                        int *n_ptr = va_arg(args, int*);

                        *n_ptr = ftell(file);
                    }
                    else
                    {
                        vfprintf(file, flag, args);
                    }
                }
                index = next_index;
            }
        }
    }
    index++;
    va_end(args);
}

void oversprintf(char *buffer, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    int index = 0;
    int buffer_index = 0;

    char* roman_result = NULL;
    char* zeck_result = NULL;
    char* Cv_result = NULL;
    char* CV_result = NULL;
    char* mi_result = NULL;
    char* mu_result = NULL;
    char* md_result = NULL;
    char* mf_result = NULL;

    while (format[index] != '\0')
    {
        if (format[index] != '%')
        {
            buffer[buffer_index] = format[index];
            buffer_index++;
            index++;
        }
        else
        {
            int next_index = index + 1;

            if (format[next_index] == '%')
            {
                sprintf(&(buffer[buffer_index]), "%c", '%');
                index = next_index + 1;
                buffer_index++;
            }
            else
            {
                char flag[25];
                int flag_index = 0;
                flag[flag_index++] = '%';

                while (format[next_index] != '\0' && (isalnum(format[next_index])))
                {
                    flag[flag_index++] = format[next_index++];
                }

                flag[flag_index] = '\0';

                if (strcmp(flag, "%Ro") == 0)
                {
                    int arg = va_arg(args, int);
                    status_code st_roman = roman_digits_flag(arg, &roman_result);
                    if (st_roman == OK)
                    {
                        sprintf((buffer + buffer_index), "%s\n", roman_result);
                        buffer_index += strlen(roman_result) + 1;
                    }
                    else
                    {
                        print_errors(st_roman);
                    }
                    free(roman_result);
                }

                else if (strcmp(flag, "%Zr") == 0)
                {
                    unsigned int arg = va_arg(args, unsigned int);
                    status_code st_zc = zecedorf_representation(arg, &zeck_result);
                    if (st_zc == OK)
                    {
                        sprintf(&(buffer[buffer_index]), "%s\n", zeck_result);
                        buffer_index += strlen(zeck_result) + 1;
                    }
                    else
                    {
                        print_errors(st_zc);
                    }
                    free(zeck_result);
                }

                else if (strcmp(flag, "Cv") == 0)
                {
                    int arg = va_arg(args, int);
                    int system = va_arg(args, int);
                    status_code Cv_st = decemal_to_other_base_l(&Cv_result, arg, system);

                    if (Cv_st == OK)
                    {
                        sprintf(&(buffer[buffer_index]), "%s\n", Cv_result);
                        buffer_index += strlen(Cv_result) + 1;
                    }

                    else
                    {
                        print_errors(Cv_st);
                    }
                    free(Cv_result);
                }

                else if (strcmp(flag, "CV") == 0)
                {
                    int arg = va_arg(args, int);
                    int system = va_arg(args, int);
                    status_code CV_st = decemal_to_other_base_l(&CV_result, arg, system);

                    if (CV_st == OK)
                    {
                        sprintf(&(buffer[buffer_index]), "%s\n", CV_result);
                        buffer_index += strlen(CV_result) + 1;
                    }
                    else
                    {
                        print_errors(CV_st);
                    }
                    free(CV_result);
                }

                else if (strcmp(flag, "to") == 0)
                {
                    char* arg = va_arg(args, char*);
                    int system = va_arg(args, int);
                    int to_st = other_base_to_ten_l(arg, system);
                    sprintf(&(buffer[buffer_index]), "%d\n", system);
                    buffer_index += 1;
                }

                if (strcmp(flag, "TO") == 0)
                {
                    char* arg = va_arg(args, char*);
                    int system = va_arg(args, int);
                    int TO_st = other_base_to_ten_h(arg, system);
                    sprintf(&(buffer[buffer_index]), "%d\n", system);
                    buffer_index += 1;
                }

                if (strcmp(flag, "mi") == 0)
                {
                    int arg = va_arg(args, int);
                    status_code mi_st = print_dump_memory(&mi_result, &arg, sizeof(arg));

                    if (mi_st == OK)
                    {
                        sprintf(&(buffer[buffer_index]), "%s\n", mi_result);
                        buffer_index += strlen(mi_result) + 1;
                    }
                    else
                    {
                        print_errors(mi_st);
                    }
                    free(mi_result);
                }

                else if (strcmp(flag, "mu") == 0)
                {
                    unsigned int arg = va_arg(args, unsigned int);
                    status_code mu_st = print_dump_memory(&mu_result, &arg, sizeof(arg));

                    if (mu_st == OK)
                    {
                        sprintf(&(buffer[buffer_index]), "%s\n", mu_result);
                        buffer_index += strlen(mu_result) + 1;
                    }
                    else
                    {
                        print_errors(mu_st);
                    }
                    free(mu_result);
                }

                else if (strcmp(flag, "md") == 0)
                {
                    double arg = va_arg(args, double);
                    status_code md_st = print_dump_memory(&md_result, &arg, sizeof(arg));

                    if (md_st == OK)
                    {
                        sprintf(&(buffer[buffer_index]), "%s\n", md_result);
                        buffer_index += strlen(md_result) + 1;
                    }
                    else
                    {
                        print_errors(md_st);
                    }
                    free(md_result);
                }

                else if (strcmp(flag, "mf") == 0)
                {
                    float arg = va_arg(args, double);
                    status_code mf_st = print_dump_memory(&mf_result, &arg, sizeof(arg));

                    if (mf_st == OK)
                    {
                        sprintf(&(buffer[buffer_index]), "%s\n", mf_result);
                        buffer_index += strlen(mf_result) + 1;
                    }
                    else
                    {
                        print_errors(mf_st);
                    }
                    free(mf_result);
                }

                else
                {
                    if (strcmp(flag, "%n") == 0)
                    {
                        int *n_ptr = va_arg(args, int*);
                        *n_ptr = index;
                    }
                    else
                    {
                        vsprintf(buffer + buffer_index, flag, args);
                    }
                }
                index = next_index;
            }
        }

    }
    buffer[index] = '\0';
    va_end(args);
}

int main()
{
    FILE* file = fopen("t1.txt", "w");
    if (!file)
    {
        printf("Error with opening file\n");
        return 0;
    }
    int x;

    overfprintf(file, "Roman: %Ro \n", 56);
    overfprintf(file, "Zeckendorf: %Zr \n", 56);
    overfprintf(file, "gooo %%%d %n %.001f\n", 65, &x, 0.4874587);
    overfprintf(file, "System low: %Cv\n", 4375687, 16);
    overfprintf(file, "System high: %CV\n", 455439, 7);
    overfprintf(file, "System 10 low: %to\n", "aa", 32);
    overfprintf(file, "System 10 high: %TO\n", "123A", 16);
    overfprintf(file, "Bytes signed int: %mi\n", 45);
    overfprintf(file, "Bytes signed unsighted int: %mu\n", 485);
    overfprintf(file, "Bytes signed double: %md\n", 45.546);
    overfprintf(file, "Bytes signed float: %mf\n", 45.3463);
    overfprintf(file, "%n\n", &x);

    char buffer[256];

    // oversprintf(buffer, "Roman: %Ro", 56);
    // oversprintf(buffer, "Zeckendorf: %Zr\n", 100); TODO:
    // oversprintf(buffer, "System low: %Cv\n", 4375687, 16); TODO:
    // oversprintf(buffer, "System high: %CV\n", 455439, 7);
    // oversprintf(buffer, "System 10 low: %to\n", "aa", 32); 
    // oversprintf(buffer, "System 10 high: %TO\n", "123A", 16); TODO:
    // oversprintf(buffer, "Bytes signed int: %mi\n", 45);
    // oversprintf(buffer, "Bytes signed unsighted int: %mu\n", 485);
    // oversprintf(buffer, "Bytes signed double: %md\n", 45.546);
    // oversprintf(buffer, "Bytes signed float: %mf\n", 45.3463);
    // oversprintf(buffer, "%n\n", &x);

    char mas[150];
    oversprintf(mas, "I want%%%d", 52);
    printf("%s\n", mas);

    printf("%s\n", buffer);

    // char mas[150];
    // oversprintf(mas, "%Ro", 1004);
    // printf("%s\n", mas);

    fclose(file);
    return 0;
}