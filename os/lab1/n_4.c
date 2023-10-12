#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE 128


enum status_code
{
    ok,
    error_filename,
    error_with_open_file,
    error_with_writing_file,
    error_with_reading_file,
    invalid_flag,
};


int flag_xor8(FILE* file, int* array)
{
    long long sum = 0;
    char byte;

    while ((byte = fread(&byte, sizeof(char), 1, file)) > 0)
    {
        sum ^= byte;
        // printf("%lld\n", sum);
        array[0] += sum;
    }

    return ok;
}

int flag_xor32(FILE* file, int* array)
{
    long long sum = 0;
    int byte;

    while ((byte = fread(&byte, sizeof(int), 1, file)) > 0)
    {
        sum ^= byte;
        // printf("%lld\n", sum);
        array[0] += sum;
    }

    return ok;
}

// int mask()

int main(int argc, char* argv[])
{
    if (argc != 3 && argc != 4)
    {
        printf("Error\n");
        return error_filename;
    }


    FILE* file = fopen(argv[1], "rb");
    if (file == NULL)
    {
        printf("Error with open file\n");
        return error_with_open_file;
    }

    if (strcmp(argv[2], "xor8") == 0)
    {
        int array[ARRAY_SIZE] = {};
        flag_xor8(file, array);
        printf("Result xor8: %d\n", array[0]);
    }

    else if (strcmp(argv[2], "xor32") == 0)
    {
        int array[ARRAY_SIZE] = {};
        flag_xor32(file, array);
        printf("Result xor 32: %d\n", array[0]);
    }

    else if (strcmp(argv[2], "mask") == 0)
    {
        printf("bebe");
    }

    else 
    {
        printf("Invalid flag\n");
        return invalid_flag;
    }

    return ok;

}