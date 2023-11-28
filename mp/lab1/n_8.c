#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

typedef enum
{
    OK,
    ERROR_WITH_NUMBER_OF_ARGUMENTS,
    WRONG_ARGUMENT,
    ERROR_WITH_OPENING_FILE,
    OVERFLOW

} status_code;

void print_errors(int flag)
{
    switch(flag)
    {
        case ERROR_WITH_NUMBER_OF_ARGUMENTS:
            printf("Invalid value\n");
            break;

        case ERROR_WITH_OPENING_FILE:
            printf("Error with file\n");
            break;
        
        case WRONG_ARGUMENT:
            printf("It's wrong argument\n");
            break;

        default:
            break;
    }
}

char* remove_zeros(char* str) 
{
    int i, j = 0;
    int len = strlen(str);

    while (str[j] == '0') 
    {
        j++;
    }

    if (j == len) 
    {
        str[1] = '\0';
    } 
    else 
    {
        for (i = 0; i < len - j; i++) 
        {
            str[i] = str[i + j];
        }
        str[i] = '\0';
    }
    return str;
}

status_code find_min_base(char *number, int *base)
{
    int len = strlen(number);
    int max = 0;
    int i = 0;

    if (number[0] == '-')
    {
        i++;
    }

    for (; i < len; ++i)
    {
        if (number[i] >= '0' && number[i] <= '9')
        {
            max = fmax(max, number[i] - '0');
        }
        else if ((number[i] >= 'A' && number[i] <= 'Z') || (number[i] >= 'a' && number[i] <= 'z'))
        {
            max = fmax(max, number[i] - 'A' + 10);
        }
        else
        {
            return WRONG_ARGUMENT;
        }
    }

    *base = max + 1;

    if (*base < 2)
    {
        *base = 2;
    }
    return OK;
}

int other_base_to_ten(char* number, int base)
{
    if (!number)
    {
        return WRONG_ARGUMENT;
    }
    int symbol = 1;
    char *ptr = number;
    int result = 0;

    if (*number == '-')
    {
        symbol = -1;
        ptr++;
    }

    while (*ptr)
    {
        if (result > INT_MAX / base || (isdigit(*ptr) ? *ptr  - '0' : *ptr - 'A' + 10) > INT_MAX - result * base)
        {
            return OVERFLOW;
        }

        result = result * base + (isdigit(*ptr) ? *ptr  - '0' : *ptr - 'A' + 10);
        ptr++;
    }

    return result * symbol;
}

status_code in_file(const char *file1, const char *file2)
{
    if (strcmp(file1, file2) == 0)
    {
        return ERROR_WITH_OPENING_FILE;
    }

    FILE *input = fopen(file1, "r");
    FILE *output = fopen(file2, "w");

    if (!input || !output)
    {
        fclose(input);
        fclose(output);
        return ERROR_WITH_OPENING_FILE;
    }

    char mas[256];
    status_code st;
    int base, res;

    while (fscanf(input, "%s", mas) != EOF)
    {
        char *new_nums = remove_zeros(mas);

        st = find_min_base(new_nums, &base);

        if (st == WRONG_ARGUMENT)
        {
            fprintf(output, "INVALID INPUT\n");
        }

        else if (st == OVERFLOW)
        {
            fprintf(output, "Overflow\n");
        }

        else
        {
            fprintf(output, "%s %d %d\n", new_nums, base, other_base_to_ten(new_nums, base));
        }
    }
    
    fclose(input);
    fclose(output);
    return OK;
}

int main(int argc, char*argv[])
{
    if (argc != 3 )
    {
        printf("Wrong number of arguments\n");
        return 0;
    }

    char *input = argv[1];
    char *output = argv[2];

    status_code st = in_file(input, output);

    if (st != OK)
    {
        print_errors(st);
    }

    else
    {
        printf("Good!\n");
    }
    return 0;
}