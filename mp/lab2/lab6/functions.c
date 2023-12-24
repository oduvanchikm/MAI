#include "n_6.h"

void oversscanf(char* buffer, const char* format, ...)
{
    va_list arg;
    va_start(arg, format);

    int index = 0;
    int buffer_index = 0;
    int result = 0;


    while (format[index] != '\0')
    {
        if (format[index] != '%')
        {
            index++;
        }

        char flag[3];
        int index_flag = 0;
        flag[index_flag++] = '%';
        index++;

        while (format[index] != '\0' && (isalnum(format[index])))
        {
            flag[index_flag++] = format[index++];
        }

        flag[index_flag] = '\0';

        if (strcmp(flag, "%Ro") == 0)
        {
            int* args = va_arg(arg, int*);
            char temp[256];
            result += sscanf(buffer + buffer_index, "%s", temp);
            buffer_index += strlen(temp) + 1;
            status_code st_result = from_roman_to_int(temp, args);
            if (!st_result)
            {
                print_errors(st_result);
            }
        }

        else if (strcmp(flag, "%Zr") == 0)
        {
            int* args = va_arg(arg, int*);
            char temp[256];
            result += sscanf(buffer + buffer_index, "%s", temp);
            buffer_index += strlen(temp) + 1;
            status_code st_result = zeckendorf(temp, args);
            if (!st_result)
            {
                print_errors(st_result);
            }
        }

        else if (strcmp(flag, "%Cv") == 0)
        {
            int* digit = va_arg(arg, int*);
            int base = va_arg(arg, int);
            char temp[256];
            result += sscanf(buffer + buffer_index, "%s", temp);
            buffer_index += strlen(temp) + 1;
            status_code st_result = flag_cv(digit, temp, base, 0);
            if (!st_result)
            {
                print_errors(st_result);
            }
        }

        else if (strcmp(flag, "%CV") == 0)
        {
            int* digit = va_arg(arg, int*);
            int base = va_arg(arg, int);
            char temp[256];
            result += sscanf(buffer + buffer_index, "%s", temp);
            buffer_index += strlen(temp) + 1;
            status_code st_result = flag_cv(digit, temp, base, 1);
            if (!st_result)
            {
                print_errors(st_result);
            }
        }
    }
}

void overfscanf(FILE* file, const char* format, ...)
{
    
}


