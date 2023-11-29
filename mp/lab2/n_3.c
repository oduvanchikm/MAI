#include <stdio.h>
#include <stdarg.h>

typedef enum 
{
    OK,
    ERROR_WITH_OPENING_FILE,
    ERROR_ARGUMENT

} status_code;

void print_errors(int flag)
{
    switch(flag)
    {
        case ERROR_WITH_OPENING_FILE:
            printf("Error with opening file\n");
            break;
        
        case ERROR_ARGUMENT:
            printf("Error argument\n");
            break;
    }
}

void print_result(const char* file_name, int line_number, int pos)
{
    printf("File %s: line - %d, pos - %d\n", file_name, line_number, pos);
}

void print_no_sub(const char* file_name)
{
    printf("No sub in file: %s\n", file_name);
}

status_code find_sub(FILE* file, const char* sub, const char* file_name)
{
    char line[256];
    int line_count = 1;
    int s = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char* pos = line;
        int file_index = 1;

        while (*pos != '\0')
        {
            int sub_index = 0;
            int flag = 1;

            while (sub[sub_index] != '\0')
            {
                if (sub[sub_index] != pos[sub_index])
                {
                    flag = 0;
                    break;
                }

                sub_index++;
            }

            if (flag)
            {
                print_result(file_name, line_count, file_index);
                s = 1;
            }

            pos++;
            file_index++;
        }

        line_count++;
    }

    if (!s)
    {
        print_no_sub(file_name);
    }
    return OK;
}

status_code file(const char* sub, int num_files, ...)
{
    va_list arg;
    va_start(arg, num_files);

    for (int i = 0; i < num_files; i++)
    {
        const char* file_name = va_arg(arg, const char*);
        FILE* file = fopen(file_name, "r");

        if (!file)
        {
            va_end(arg);
            return ERROR_WITH_OPENING_FILE;
        }

        if (find_sub(file, sub, file_name) == OK)
        {
            va_end(arg);
            return OK;
        }
        fclose(file);
    }
    va_end(arg);

    return ERROR_ARGUMENT;
}

int main()
{
    const char* sub = "4";
    const char* file_1 = "t1.txt";
    const char* file_2 = "t2.txt";
    int count = 2;

    status_code st = file(sub, count, file_1, file_2);

    if (st != OK)
    {
        print_errors(st);
    }
    return 0;
}