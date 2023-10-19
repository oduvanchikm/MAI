#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdarg.h>

enum status_code
{
    ok,
    error_with_number_of_arguments = -1,
    error_with_memory_allocation = -2,
    out_of_range = -3
};

enum flag
{
    error_number_arguments,
    wrong_arguments,
    flag_l,
    flag_r,
    flag_u,
    flag_n,
    flag_c
};

enum status_code my_strlen(const char *str)
{
    int length = 0;
    while (*str != '\0') 
    {
        length++;
        str++;
    }
     
    return ok;
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

int choose_flag(char* str_1, char* str_2, int argc)
{
    if (argc < 3)
    {
        return error_number_arguments;
    }

    else if (argc == 3)
    {
        if (my_strlen(str_1) != 2 || str_1[0] != '-' && str_1[0] != '/') 
        {
           return wrong_arguments; 
        }

        if (str_1[1] == 'l')
        {
            return flag_l;
        }

        if (str_1[1] == 'r')
        {
            return flag_r;
        }

        if (str_1[1] == 'u')
        {
            return flag_u;
        }

        if (str_1[1] == 'n')
        {
            return flag_n;
        }
    }

    else 
    {
        if (str_1[1] == 'c')
        {
            if (my_strlen(str_2) == 10 && checking_unsigned_int(str_2) )
            {
                return flag_c;
            }

            else 
            {
                return wrong_arguments;
            }

        }
    }
    return 0;
}

enum status_code reversed_function(char* string, char** new_string)
{
    int len = my_strlen(string);

    *new_string = (char*)malloc((len + 1) * sizeof(char));
    
    if (*new_string == NULL)
    {
        return error_with_memory_allocation;
    }

    for (int i = len - 1; i >= 0; i--)
    {
        (*new_string)[len - 1 - i] = string[i];
    }

    return ok;
}

enum status_code string_conversion(char* string, char** new_string)
{
    int len = my_strlen(string);

    *new_string = (char*)malloc((len + 1) * sizeof(char));

    if (*new_string == NULL)
    {
        return error_with_memory_allocation;
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

    return ok;
}

enum status_code string_digits_letters_symbols(char **new_string, char* string)
{
    int len = my_strlen(string);

    *new_string = (char*)malloc((len + 1) * sizeof(char));

    if (*new_string == NULL)
    {
        return error_with_memory_allocation;
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

    return ok;

}


int main(int argc, char* argv[])
{
    int flag = choose_flag(argv[1], argv[3], argc);
    int len = my_strlen(argv[2]);
    int seed = atoi(argv[3]);
    char* string = argv[2];
    char* new_string = NULL;
    enum status_code result_r;
    enum status_code result_u;
    enum status_code result_n;

    switch (flag)
    {
        case error_number_arguments:
            printf("Error with number of arguments\n");
            break;

        case wrong_arguments:
            printf("Wrong arguments\n");
            break;

        case flag_l:
            printf("%d\n", len);
            break;

        case flag_r:
            result_r = reversed_function(string, &new_string);

            if (result_r == ok)
            {
                printf("%s\n", new_string);
            }
            else
            {
                printf("Error with memory allocation\n");
            }

            free(new_string);
            break;
        
        case flag_u:
            result_u = string_conversion(string, &new_string);

            if (result_u == ok)
            {
                printf("%s\n", new_string);
            }
            else
            {
                printf("Error with memory allocation\n");
            }

            free(new_string);
            break;
        
        case flag_n:
            result_n = string_digits_letters_symbols(&new_string, string);

            if (result_n == ok)
            {
                printf("%s\n", new_string);
            }
            else
            {
                printf("Error with memory allocation\n");
            }

            free(new_string);

            break;
        
        case flag_c:
            ////////////////////////////////////////////////////////////////////////////////////////
            break;
    
    default:
        break;
    }
    return 0;
}

