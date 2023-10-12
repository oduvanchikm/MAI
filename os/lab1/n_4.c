#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE 128


enum status_code
{
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

    while ((byte = fgetc(file)) != EOF)
    {

        sum ^= byte;
        printf("%lld\n", sum);
        array[0] += sum;
    }

    return 0;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
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
        printf("Result: %d\n", array[0]);
    }

    else if (strcmp(argv[2], "xor32") == 0)
    {
        printf("be");
    }

    else 
    {
        printf("Invalid flag\n");
        return invalid_flag;
    }

}