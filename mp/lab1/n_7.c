#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef enum
{
    OK,
    ERROR_WITH_NUMBER_OF_ARGUMENTS,
    WRONG_ARGUMENTS,
    ERROR_WITH_OPENING_FILE,
    ERROR_WITH_MEMORY_ALLOCATION

} status_code;

void print_errors(int flag)
{
    switch(flag)
    {
        case ERROR_WITH_NUMBER_OF_ARGUMENTS:
            printf("Invalid value\n");
            break;

        case ERROR_WITH_OPENING_FILE:
            printf("Error with opening file\n");
            break;

        case ERROR_WITH_MEMORY_ALLOCATION:
            printf("Error with memory allocation\n");
            break;
        
        case WRONG_ARGUMENTS:
            printf("Invalid value\n");
            break;

        default:
            break;
    }
}

void to_lower(char str)
{
    if (str >= 'A' && str <= 'Z')
    {
        str = tolower(str);
    }
}

int convert_from_decimal(char str, int base) 
{
    int num = str;
    int result = 0, k = 1;
    while (num > 0) 
    {
        int remainder = num % base;
        result += remainder * k;
        num /= base;
        k *= 10;
    }
    return result;
}

status_code flag_r(const char *file_1, const char *file_2, const char *file_3) 
{
    if ((strcmp(file_1, file_3) == 0) || (strcmp(file_2, file_3) == 0))
    {
        return ERROR_WITH_OPENING_FILE;
    }

    FILE *file1 = fopen(file_1, "r");
    FILE *file2 = fopen(file_2, "r");
    FILE *outfile = fopen(file_3, "w");

    if(!file1 || !file2 || !outfile) 
    {
        return ERROR_WITH_OPENING_FILE;
    }
    
    char c1 = fgetc(file1);
    char c2 = fgetc(file2);

    while (c1 != EOF || c2 != EOF) 
    {
        if (c1 != EOF) 
        {
            while (c1 != EOF && c1 != ' ' && c1 != '\t' && c1 != '\n') 
            {
                fprintf(outfile, "%c", c1);
                c1 = fgetc(file1);
            }
            while (c1 == '\n' || c1 == ' ')
            {
                c1 = fgetc(file1);
            }
            fputc(' ', outfile);
        }

        if (c2 != EOF) 
        {
            while (c2 != EOF && c2 != ' ' && c2 != '\t' && c2 != '\n') 
            {
                fprintf(outfile, "%c", c2);
                c2 = fgetc(file2);
            }
            while (c2 == '\n' || c2 == ' ')
            {
                c2 = fgetc(file2);
            }
            fputc(' ', outfile);
        }
    }

    fclose(file1);
    fclose(file2);
    fclose(outfile);

    return OK;
}

status_code flag_a(const char *file_1, const char *file_2)
{
    if (strcmp(file_1, file_2) == 0)
    {
        return ERROR_WITH_OPENING_FILE;
    }

    FILE *file1 = fopen(file_1, "r");
    FILE *file2 = fopen(file_2, "w");

    if (!file1 || !file2)
    {
        return ERROR_WITH_OPENING_FILE;
    }

    char c = fgetc(file1);
    int count = 1;

    while (c != EOF)
    {
        while(isspace(c)) 
        {
            c = fgetc(file1); 
        }

        if (count % 10 == 0)
        {
            while (!isspace(c) && c != EOF)
            {
                to_lower(c);

                int symbol1 = convert_from_decimal(c, 4);
                fprintf(file2, "%d", symbol1);
                c = fgetc(file1);
            }
        }

        else if (count % 2 == 0 && count % 10 != 0)
        {
            while (!isspace(c) && c != EOF)
            {
                fputc(tolower(c), file2);
                c = fgetc(file1);
            }
        } 
        
        else if (count % 5 == 0 && count % 10 != 0)
        {
            while (!isspace(c) && c != EOF)
            {
                int symbol2 = convert_from_decimal(c, 8);
                fprintf(file2, "%d", symbol2);
                c = fgetc(file1);
            }
        }
        count++;
    }
    fclose(file1);
    fclose(file2);
    return OK;
}

bool validation(char* flag)
{
    if (strlen(flag) != 2)
    {
        return false;
    }
    if (flag[0] != '-' && flag[0] != '/' || flag[1] != 'r' && flag[1] != 'a') 
    {
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    if (argc < 4 || argc > 5)
    {
        printf("Error with number of argument\n");
        return 0;
    }

    if (!validation(argv[1]))
    {
        printf("Error with input data\n");
        return 0;
    }

    char flag = argv[1][1];
    switch (flag)
    {
        case 'r':
            if (argc != 5)
            {
                printf("Wrong number of arguments\n");
                return 0;
            }
            status_code st_r = flag_r(argv[2], argv[3], argv[4]);
            if (st_r != OK)
            {
                print_errors(st_r);
                return 0;
            }
            else
            {
                printf("GOOD!\n");
            }
            break;

        case 'a':
            if (argc != 4)
            {
                printf("Wrong number of arguments\n");
                return 0;
            }

            status_code st_a = flag_a(argv[2], argv[3]);
            if (st_a != OK)
            {
                print_errors(st_a);
                return 0;
            }
            else
            {
                printf("GOOD\n");
            }

            break;

        default:
            break;
    }
    return 0;
}

