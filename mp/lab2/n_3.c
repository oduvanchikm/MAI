#include <stdio.h>
#include <stdarg.h>

typedef enum
{
    OK,
    ERROR_WITH_OPENING_FILE 

} status_code;

void print_errors(int flag)
{
    switch(flag)
    {
        case ERROR_WITH_OPENING_FILE:
            printf("Error with opening file\n");
            break;

        default:
            break;
    }
}

void print_result(char* name, int line_number, int position)
{
    printf("File %s: line is %d and position is %d\n", name, line_number, position);
}

void print_no_sub(char* name)
{
    printf("No sub in file: %s\n", name);
}

status_code find_sub(FILE* file, char* sub, char* name)
{
    char line[256];
    int count = 1;
    int ok = 0;
    while(fgets(line, sizeof(line), file) != NULL)
    {
        char* position = line;
        int file_index = 1;

        while(*position != '\0')
        {
            int index = 0;
            int flag = 1;

            while(sub[index] != '\0')
            {
                if(sub[index] != position[index])
                {
                    flag = 0;
                    break;
                }
                index++;
            }
            if (flag)
            {
                print_result(name, count, file_index);
                ok = 1;
            }
            position++;
            file_index++;
        }
        count++;
    }
    if(!ok)
    {
        print_no_sub(name);
    }
    return OK;
}

status_code get_file(char* sub, int count, ...)
{
    va_list arg;
    va_start(arg, count);

    for(int i = 0; i < count; i++)
    {
        char* name = va_arg(arg, char*);
        FILE* file = fopen(name, "r");

        if(!file)
        {
            return ERROR_WITH_OPENING_FILE;
        }

        if (find_sub(file, sub, name) != OK)
        {
            fclose(file);
            print_errors(find_sub(file, sub, name));
        }
        fclose(file);
    }
    va_end(arg);
    
    return OK;
}

int main()
{
    char* sub = "4";
    char* file_1 = "t1.txt";
    char* file_2 = "t2.txt";
    int count = 2;

    if(get_file(sub, count, file_1, file_2) == ERROR_WITH_OPENING_FILE)
    {
        print_errors(get_file(sub, count, file_1, file_2));
    }

    return 0;
}