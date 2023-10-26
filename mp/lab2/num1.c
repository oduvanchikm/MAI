#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

enum status_code
{
    OK,
    ERROR_WITH_NUMBER_OF_ARGUMENTS = -1,
    ERROR_WITH_MEMORY_ALLOCATION = -2,
    OUT_OF_RANGE = -3,
    WRONG_ARGUMENTS = -4
};

void print_errors(int flag)
{
    switch(flag)
    {
        case ERROR_WITH_NUMBER_OF_ARGUMENTS:
            printf("Invalid value\n");
            break;

        case ERROR_WITH_MEMORY_ALLOCATION:
            printf("Error with memory allocation\n");
            break;

        case OUT_OF_RANGE:
            printf("out of range\n");
            break;

        case WRONG_ARGUMENTS:
            printf("This is wrong\n");
            break;

        default:
            break;
    }
}

enum status_code my_strlen(const char *str, int *length)
{
    while (*str != '\0')
    {
        (*length)++;
        str++;
    }

    return OK;
}

bool checking_unsigned_int(char *str)
{
    if (*str == '\0' || *str == '-') {
        return false;
    }

    if (*str >= '0' && *str <= '9')
    {
        return true;
    }
    return false;
}


enum status_code reversed_function(char* string, char** new_string)
{
    int len = 0;
    my_strlen(string, &len);

    *new_string = (char*)malloc((len + 1) * sizeof(char));

    if (*new_string == NULL)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    for (int i = len - 1; i >= 0; i--)
    {
        (*new_string)[len - 1 - i] = string[i];
    }

    return OK;
}

enum status_code string_conversion(char* string, char** new_string)
{
    int len = 0;
    my_strlen(string, &len);

    *new_string = (char*)malloc((len + 1) * sizeof(char));

    if (!*new_string)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }


    for (int i = 0; i < len; i++)
    {
        if (!(i & 1))
        {
            (*new_string)[i] = toupper(string[i]);
        }
        else
        {
            (*new_string)[i] = string[i];
        }
    }

    return OK;
}

enum status_code string_digits_letters_symbols(char **new_string, char* string)
{
    int len = 0;
    my_strlen(string, &len);

    *new_string = (char*)malloc((len + 1) * sizeof(char));

    if (!*new_string)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    int index = 0;

    for (int i = 0; i < len; i++)
    {
        if (isdigit(string[i]))
        {
            (*new_string)[index] = string[i];
            index++;
        }
    }

    for (int i = 0; i < len; i++)
    {
        if (isalpha(string[i]))
        {
            (*new_string)[index] = string[i];
            index++;
        }
    }

    for (int i = 0; i < len; i++)
    {
        if (!(isdigit(string[i])) && !(isalpha(string[i])))
        {
            (*new_string)[index] = string[i];
            index++;
        }
    }

    (*new_string)[index] = '\0';

    return OK;

}

void concatination(char *str1, char*str2)
{
    while (*str1)
    {
        str1++;
    }
    while(*str2)
    {
        *str1 = *str2;
        str1++;
        str2++;
    }
    *str1 = '\0';
}

void shuffle(char** array, int count)
{
    for (int i = count - 1; i >= 1; i--)
    {
        int j = rand() % (i + 1);
        int tmp = *array[j];
        *array[j] = *array[i];
        *array[i] = tmp;
    }
}

enum status_code concat_strings(char **result, int count, char **strings, unsigned int seed)
{
    srand(seed);

    int result_len = 0;

    for (int i = 0; i < count; ++i)
    {
        int string_length = 0;
        my_strlen(strings[i], &string_length);
        result_len += string_length;
    }

    *result = (char*)malloc(sizeof(char) * (result_len + 1));
    if (!(*result))
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }
    (*result)[0] = '\0';

    shuffle(strings, count);

    for (int i = 0; i < count; ++i)
    {
        concatination(*result, strings[i]);
    }

    return OK;
}

int main(int argc, char* argv[])
{

    if (argc < 3 || argc > 10)
    {
        printf("A lot of arguments\n");
    }

    if (argv[1][0] != '-')
    {
        printf("invalid symbol\n");
    }



    int len = 0;
    my_strlen(argv[2], &len);
    int len_str = argc - 3;
    if (!checking_unsigned_int(argv[3]))
    {
        return WRONG_ARGUMENTS;
    }

    unsigned int seed = atoi(argv[3]);
    char* string = argv[2];
    char* new_string;
    enum status_code result_r;
    enum status_code result_u;
    enum status_code result_n;
    enum status_code result_c;

    char **strings = (char**)malloc(sizeof(char*) * len_str);
    if (!strings)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    if (argc == 3)
    {
        if (argv[1][1] == 'l')
        {
            printf("%d\n", len);
        }

        else if (argv[1][1] == 'r')
        {
            result_r = reversed_function(string, &new_string);

            if (result_r == OK)
            {
                printf("%s\n", new_string);
            }

            else
            {
                print_errors(result_r);
            }

            free(new_string);
        }

        else if (argv[1][1] == 'u')
        {
            result_u = string_conversion(string, &new_string);

            if (result_u == OK)
            {
                printf("%s\n", new_string);
            }

            else
            {
                print_errors(result_u);
            }

            free(new_string);
        }

        else if (argv[1][1] == 'n')
        {
            result_n = string_digits_letters_symbols(&new_string, string);

            if (result_n == OK)
            {
                printf("%s\n", new_string);
            }

            else
            {
                print_errors(result_n);
            }

            free(new_string);
        }

        else
        {
            printf("invalid flag\n");
        }
    }

    if (argc > 3 && argc < 10)
    {
        if (argv[1][1] == 'c')
        {
            strings[0] = string;
            for (int i = 1; i < len_str; i++)
            {
                strings[i] = argv[i + 3];
            }
            char *result;

            result_c = concat_strings(&result, len_str, strings, seed);

            if (result_c == OK)
            {
                printf("%s\n", result);
            }

            else
            {
                print_errors(result_c);
            }

            free(strings);
            free(result);
        }
        else
        {
            printf("invalid flag\n");
        }
    }
    else
    {
        printf("error with count of arguments\n");
    }
}