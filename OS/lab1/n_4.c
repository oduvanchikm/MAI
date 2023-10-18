#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

enum status_code
{
    ok,
    error_filename,
    error_with_open_file,
    invalid_flag,
    error_with_base
};

unsigned char flag_xor8(FILE* file)
{
    unsigned char sum = 0;
    unsigned char byte = 0;

    while (fread(&byte, sizeof(unsigned char), 1, file) > 0)
    {
        sum ^= byte;
    }

    return sum;
}

unsigned int flag_xor32(FILE* file)
{
    unsigned int bytes = 0;
    unsigned int result = 0;

    while(fread(&bytes, sizeof(unsigned int), 1, file) > 0)
    {
        result ^= bytes;
    }

    return result;
}

int to_ten(char *number, int base)
{
    int result = 0;
    char *ptr = number;

    while (*ptr)
    {
        result = result * base + (*ptr > '9' ? *ptr - 'A' + 10 : *ptr - '0');
        ptr++;
    }

    return result;
}

unsigned int flag_mask(FILE* file, char* argv)
{
    unsigned int number;
    unsigned int result = 0;
    unsigned int mask = to_ten(argv, 16);

    while(fread(&number, sizeof(unsigned int), 1, file) > 0)
    {
        result += (number & mask) != 0 ? 1 : 0;
    }

    return result;
}

bool is_16(char* str)
{
    while (*str)
    {
        if(!isxdigit(*str))
        {
            return false;
        }
        str++;
    }
    return true;
}

int main(int argc, char* argv[])
{
    //switch(task) {......} catch errors
    FILE* file = fopen(argv[1], "rb");

    if (file == NULL)
    {
        printf("Error with open file \n");

        return error_with_open_file;
    }


    if (argc == 3)
    {

        if (strcmp(argv[2], "xor8") == 0)
        {
            printf("Result xor8: %d\n", flag_xor8(file));
        }

        else if (strcmp(argv[2], "xor32") == 0)
        {
            printf("Result xor32: %d\n", flag_xor32(file));
        }
    }

    else if (argc == 4)
    {
        if (strcmp(argv[2], "mask") == 0)
        {
            if (is_16(argv[3]))
            {
                printf("%d\n", flag_mask(file, argv[3]));
            }
            else
            {
                printf("😃 It's not a digit in 16 base 😃\n");
                return error_with_base;
            }
        }

        else
        {
            printf("Invalid flag\n");
            fclose(file);

            return invalid_flag;
        }
    }

    else {
        printf("Invalid flag\n");
        fclose(file);

        return invalid_flag;

    }

    fclose(file);

    return ok;
}
