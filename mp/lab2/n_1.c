#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>

enum status_code
{
    OK,
    ERROR_WITH_NUMBER_OF_ARGUMENTS = -1,
    ERROR_WITH_MEMORY_ALLOCATION = -2,
    OUT_OF_RANGE = -3,
    WRONG_ARGUMENTS = -4
};

enum flag
{
    FLAG_L,
    FLAG_R,
    FLAG_U,
    FLAG_N,
    FLAG_C
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

enum status_code my_strlen(const char *str)
{
    int length = 0;
    while (*str != '\0') 
    {
        length++;
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

enum status_code choose_flag(char* str_1, char* str_2, int argc)
{
    if (argc < 3 || argc > 10)
    {
        return ERROR_WITH_NUMBER_OF_ARGUMENTS;
    }

    else if (argc == 3)
    {
        if (my_strlen(str_1) != 2 || str_1[0] != '-' && str_1[0] != '/') 
        {
           return WRONG_ARGUMENTS; 
        }

        if (str_1[1] == 'l')
        {
            return FLAG_L;
        }

        if (str_1[1] == 'r')
        {
            return FLAG_R;
        }

        if (str_1[1] == 'u')
        {
            return FLAG_U;
        }

        if (str_1[1] == 'n')
        {
            return FLAG_N;
        }
    }

    else 
    {
        if (str_1[1] == 'c')
        {
            if (my_strlen(str_2) == 10 && checking_unsigned_int(str_2) )
            {
                return FLAG_C;
            }

            else 
            {
                return WRONG_ARGUMENTS;
            }

        }
    }
    return OK;
}

enum status_code reversed_function(char* string, char** new_string)
{
    int len = my_strlen(string);

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
    int len = my_strlen(string);

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
    int len = my_strlen(string);

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


// void concatination(char* str, char** result, int* len)
// {
//     for (int i = 0; str[i] != '\0'; ++i)
//     {
//         (*result)[(*len)++] = str[i];
//     }

//     (*result)[(*len)] = '\0';
// }


// // char max_string(char* string_1, char* string_2)
// // {
// //     char max_elem;

// //     // Проверка, не пусты ли строки
// //     if (string_1 == NULL && string_2 == NULL) {
// //         return '\0';  
// //     }
// //     else if (string_1 == NULL) {
// //         return *string_2;  
// //     }
// //     else if (string_2 == NULL) {
// //         return *string_1;  
// //     }

// //    
// //     if (*string_1 > *string_2) {
// //         max_elem = *string_1;
// //     }
// //     else {
// //         max_elem = *string_2;
// //     }

// //     return max_elem;
// // }

// enum status_code generating_numbers(unsigned int seed, char **numbers, int count, char **string)
// {
//     int len = 0;
//     char max_string;

//     if (count == 0)
//     {
//         return WRONG_ARGUMENTS;
//     }

//     for (int i = 0; i < count; i++)
//     {
//         len = my_strlen(string[i]);
//         // max_elem = max_string(string[i], &max_elem);
//         if (len > max_string) 
//         {
//             max_string = len;
//         }
//     }

//     max_string * count;

//     *numbers = (char*)malloc((max_string + 1) * sizeof(char));

//     if (!*numbers)
//     {
//         return ERROR_WITH_MEMORY_ALLOCATION;
//     }

//     int rand_number;

//     srand(seed);

//     for (int i = 0; i < count; i++)
//     {
//         rand_number = rand() % count;
//         concatination(string[rand_number], numbers, &len);
//     }

//     return OK;

// }

int main(int argc, char* argv[])
{
    int flag = choose_flag(argv[1], argv[3], argc);
    int len = my_strlen(argv[2]);
    int len_str = argc - 3;
    unsigned int seed = atoi(argv[3]);
    char* string = argv[2];
    char* new_string;
    enum status_code result_r;
    enum status_code result_u;
    enum status_code result_n;
    enum status_code result_c;

    switch (flag)
    {
        case FLAG_L:
            printf("%d\n", len);
            break;

        case FLAG_R:
            result_r = reversed_function(string, &new_string);

            if (result_r == OK)
            {
                printf("%s\n", new_string);
            }

            print_errors(result_r);

            free(new_string);
            break;
        
        case FLAG_U:
            result_u = string_conversion(string, &new_string);

            if (result_u == OK)
            {
                printf("%s\n", new_string);
            }

            print_errors(result_u);

            free(new_string);
            break;
        
        case FLAG_N:
            result_n = string_digits_letters_symbols(&new_string, string);

            if (result_n == OK)
            {
                printf("%s\n", new_string);
            }

            print_errors(result_n); 

            free(new_string);

            break;
        
        case FLAG_C:

            // result_c = generating_numbers(seed, &new_string, len_str, argv + 3);

            // if (result_c != OK)
            // {
            //     print_errors(result_c);
            // }

            // printf("%s\n", new_string);

            // free(new_string);

            // break;

    default:
        break;
    }
    return 0;
}

