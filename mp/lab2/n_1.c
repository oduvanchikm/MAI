#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

enum status_code
{
    error_with_number_of_arguments,
    error_with_memory_allocation,
    out_of_range
};

enum flag
{
    error_number_arguments,
    flag_l,
    flag_r,
    flag_u,
    flag_n,
    flag_c
};

int my_strlen(const char *str)
{
    int length = 0;
    while (*str != '\0') 
    {
        length++;
        str++;
    }
     
    return length;
}

int choose_flag(char* str, int argc)
{
    if (argc < 3)
    {
        return error_number_arguments;
    }

    else if (argc == 3)
    {
        if (my_strlen(str) != 2 || str[0] != '-' && str[0] != '/') 
        {
           return error_number_arguments; 
        }

        if (str[1] == 'l')
        {
            return flag_l;
        }

        if (str[1] == 'r')
        {
            return flag_r;
        }

        if (str[1] == 'u')
        {
            return flag_u;
        }

        if (str[1] == 'n')
        {
            return flag_n;
        }
    }

    else 
    {
        if (str[1] == 'c')
        {
            return flag_c;
        }
    }

    return 0;
}

char* reversed_function(char* string, char* new_string)
{
    int len = my_strlen(string);

    new_string = (char*)malloc((len) * sizeof(char));


    for (int i = len - 1; i >= 0; i--)
    {
        new_string[len - 1 - i] = string[i];
    }

    return new_string;
}

char* string_conversion(char* string, char* new_string)
{
    int len = my_strlen(string);

    new_string = (char*)malloc((len) * sizeof(char));


    for (int i = 0; i < len; i++)
    {
        if (i & 1 == 1)
        {
            new_string[i] = toupper(string[i]);
        }
        else
        {
            new_string[i] = string[i];
        }
    }

    return new_string;
}

bool digits(const char *str)
{
    if (*str == '\0')
    {
        return false;
    }

    if (*str >= '0' && *str <= '9')
    {
        return true;
    }
    return false;
}

bool letters(const char *str)
{
    if (*str == '\0')
    {
        return false;
    }

    if ((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z'))
    {
        return true;
    }
    return false;
}

bool symbols(const char *str)
{
    if (*str == '\0')
    {
        return false;
    }

    if (!(letters(str)) && !(digits(str)))
    {
        return true;
    }
    return false;
}

char* my_strcpy(char* first, const char* second)
{
    char *ptr = first;

    while (*second)
    {
        *first = *second;
        first++;
        second++;
    }

    return ptr;
}

char* string_digits_letters_symbols(char* string, char* new_string)
{
    char* digits_string;
    char* letter_string;
    char* symbol_string;

    int count_for_digits = 0;
    int count_for_letters = 0;
    int count_for_symbols = 0;


    while (*string)
    {
        if (digits(string))
        {
            count_for_digits += 1;
        }
        string++;
        
    }

    digits_string = (char*)malloc((count_for_digits) * sizeof(char));  


    for (int i = 0; i < count_for_digits; i++)
    {
        digits_string[i] = string[i];
    }

    while (*string)
    {
        if (letters(string))
        {
            count_for_letters += 1;
        }
        string++;
    }

    letter_string = (char*)malloc((count_for_letters) * sizeof(char));  


    for (int i = 0; i < count_for_letters; i++)
    {
        letter_string[i] = string[i];
    }

    while (*string)
    {
        if (symbols(string))
        {
            count_for_symbols += 1;
        }
        string++;
    }

    symbol_string = (char*)malloc((count_for_symbols) * sizeof(char));  

    for (int i = 0; i < count_for_symbols; i++)
    {
        symbol_string[i] = string[i];
    }

    new_string = (char*)malloc(my_strlen(digits_string) + my_strlen(letter_string) + my_strlen(symbol_string) + 1);

    my_strcpy(new_string, digits_string);
    my_strcpy(new_string, letter_string);
    my_strcpy(new_string, symbol_string);

    free(digits_string);
    free(letter_string);
    free(symbol_string);

    return new_string;
}


int main(int argc, char* argv[])
{

    int flag = choose_flag(argv[1], argc);
    int len = my_strlen(argv[2]);
    char* string = argv[2];
    char* new_string = NULL;

    switch (flag)
    {
        case error_number_arguments:
            printf("Error with number of arguments\n");
            break;

        case flag_l:
            printf("%d\n", len);
            break;

        case flag_r:
            new_string = reversed_function(string, new_string);

            printf("%s\n", new_string);

            free(new_string);
            break;
        
        case flag_u:
            new_string = string_conversion(string, new_string);

            printf("%s\n", new_string);

            free(new_string);
            break;
        
        case flag_n:
            new_string = string_digits_letters_symbols(string, new_string);

            printf("%s\n", new_string);
            free(new_string);

            break;
        
        case flag_c:
            printf("c flag\n");
            break;
    
    default:
        break;
    }
    return 0;
}

