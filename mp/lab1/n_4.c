#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum status_code
{
    OK,
    ERROR_WITH_NUMBER_OF_ARGUMENTS,
    WRONG_ARGUMENTS,
    WRONG_PARAMETER,
    ERROR_WITH_OPENING_FILE,
    ERROR_WITH_MEMORY_ALLOCATION
};

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

        case WRONG_PARAMETER:
            printf("This is wrong\n");
            break;

        case ERROR_WITH_MEMORY_ALLOCATION:
            printf("Error with memory allocation\n");
            break;

        default:
            break;
    }
}

enum status_code remove_arabic_nums(const char *file_input, const char *file_output)
{
    FILE *file_1 = fopen(file_input, "r");
    FILE *file_2 = fopen(file_output, "w");

    if (!file_1 || !file_2)
    {
        fclose(file_1);
        fclose(file_2);
        return ERROR_WITH_OPENING_FILE;
    }

    char c;
    while ((c = fgetc(file_1)) != EOF)
    {
        if (c >= '0' && c <= '9')
        {
            fputc(c, file_2);

        }
    }

    fclose(file_1);
    fclose(file_2);

    return OK;
}

enum status_code latin_alphabet(const char *file_input, const char *file_output)
{
    FILE *file_1 = fopen(file_input, "r");
    FILE *file_2 = fopen(file_output, "w");

    if (!file_1 || !file_2)
    {
        fclose(file_1);
        fclose(file_2);
        return ERROR_WITH_OPENING_FILE;
    }

    int count = 0;
    char alphabet;
    while ((alphabet = getc(file_1)) != EOF)
    {
        if (isalpha(alphabet))
        {
            count++;
        }
        // else if (alphabet == '\n')
        else
        {
            count = 0;
            // fprintf(file_2, "%d\n", count);
        }
    }
    fprintf(file_2, "%d\n", count);

    fclose(file_1);
    fclose(file_2);
    return OK;
}

enum status_code s_flag(const char *file_input, const char *file_output)
{
    FILE *file_1 = fopen(file_input, "r");
    FILE *file_2 = fopen(file_output, "w");

    if (!file_1 || !file_2)
    {
        fclose(file_1);
        fclose(file_2);
        return ERROR_WITH_OPENING_FILE;
    }

    int count = 0;
    char string;
    while ((string = getc(file_1)) != EOF)
    {
        if (!(isalpha(string)) && !(isdigit(string)))
        {
            count++;
        }
        if (string == '\n')
        {
            fprintf(file_2, "%d\n", count);
            count = 0;
        }
    }

    fclose(file_1);
    fclose(file_2);
    return OK;
}

enum status_code ascii_code(const char *file_input, const char *file_output) 
{  
    FILE *file_1 = fopen(file_input, "r");
    FILE *file_2 = fopen(file_output, "w");

    if (!file_1 || !file_2)
    {
        fclose(file_1);
        fclose(file_2);
        return ERROR_WITH_OPENING_FILE;
    }

    int c;
    while ((c = fgetc(file_1)) != EOF)
    {
        if ((c >= '0' && c <= '9') || c == '\n')
        { 
            fputc(c, file_2);
        }
        else 
        {
            fprintf(file_2, "%X", c);
        }
    }

    fclose(file_1);
    fclose(file_2);
    return OK;
}

const char* get_file_name(const char *string) 
{
    const char* file_name = strrchr(string, '/');

    if (file_name != NULL) 
    {
        file_name++;
    } 
    else 
    {
        file_name = string;
    }

    return file_name;
}

int main(int argc, char* argv[])
{
    if (argv[1][0] != '-' && argv[1][0] != '/')
    {
        printf("Your flag must start with '-' or '/' symbol\n");
        return 0;
    }

    char flag;
    const char *input = argv[2];

    char *output = NULL;

    if (argv[1][1] == 'n')
    {
        if (argc != 4)
        {
            printf("Invalid number of arguments\n");
            printf("Please enter: flag, input file, and output file\n");
            return 0;
        }
        // printf("ererere\n");

        output = argv[3];

        if (strlen(argv[1]) != 3)
        {
            printf("Wrong enter\n");
            return 0;
        }

        // printf("ererere\n");

        if (strcmp(argv[2], argv[3]) == 0)
        {
            printf("You have to enter different files\n");
            return 0;
        }
        // printf("ererere\n");

        flag = argv[1][2];
    }
    else
    {
        if (strlen(argv[1]) != 2)
        {
            printf("Wrong enter\n");
            return 0;
        }

        if (argc != 3)
        {
            printf("Invalid number of arguments\n");
            printf("Please enter: flag, input file, and output file\n");
            return 0;
        }

        flag = argv[1][1];

        char *prefix = "out_";
        const char *input_file = get_file_name(input);

        output = (char*)malloc(strlen(input_file) + strlen(prefix) + 1);

        if (!output) 
        {
            printf("Error with memory allocation\n");
            return 0;
        }

        sprintf(output, "out_%s", input_file);
        free(output);
    }

    switch (flag)
    {
        case 'd':
            remove_arabic_nums(input, output);
            break;
        case 'i':
            // printf("ererere\n");
            latin_alphabet(input, output);
            break;
        case 's':
            s_flag(input, output);
            break;
        case 'a':
            ascii_code(input, output);
            break;
        default:
            printf("Invalid flag argument\n");
            break;
    }

    // free(output);
    return 0;
}