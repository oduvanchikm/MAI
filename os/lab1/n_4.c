#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

enum status_code
{
    ok,
    error_filename,
    error_with_open_file,
    invalid_flag,
};

int flag_xor8(FILE* file)
{
    long long sum = 0;
    unsigned char byte;

    while (fread(&byte, sizeof(unsigned char), 1, file) > 0)
    {
        sum ^= byte;
    }

    return sum;
}

int flag_xor32(FILE* file)
{
    unsigned int bytes;
    long int result = 0;
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

int flag_mask(FILE* file, char* argv)
{
    int count;
    unsigned int mask_array;
    long int result = 0;
    unsigned long int mask = to_ten(argv, 16);
    while(fread(&mask, sizeof(unsigned int), 1, file) > 0)
    {   
        if(memcmp(mask_array, &mask, 4) == 0)
        {
            result += 1;
        }
    }
    return result;
}

int main(int argc, char* argv[])
{

    FILE* file = fopen(argv[1], "rb");
    if (file == NULL)
    {
        printf("Error with open file\n");
        return error_with_open_file;
    }

    if (strcmp(argv[2], "xor8") == 0)
    {
        int res = flag_xor8(file);
        printf("Result xor8: %d\n", res);
    }
    else if (strcmp(argv[2], "xor32") == 0)
    {
        int res = flag_xor32(file);
        printf("Result xor32: %d\n", res);
    }
    else if (strcmp(argv[2], "mask") == 0)
    {

        long long res = flag_mask(file, argv[3]);


        printf("%d\n", res);
        
    }
    else 
    {
        printf("Invalid flag\n");
        return invalid_flag;
    }

    fclose(file);
    return ok;
}
