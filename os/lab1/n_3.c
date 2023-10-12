#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1

enum status_file
{
    error_filename,
    error_with_open_file,
    error_with_writing_file,
    error_with_reading_file,
};

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Error\n");
        return error_filename;
    }

    FILE* first_file = fopen(argv[1], "rb");
    
    if (first_file == NULL)
    {
        printf("Can't open the file\n");
        return error_with_open_file;
    }

    FILE* second_file = fopen(argv[2], "wb");

    if (second_file == NULL)
    {
        printf("Can't open the file\n");
        return error_with_open_file;
    }


    char buffer[BUFFER_SIZE];

    char bytes;

    while (bytes = fread(buffer, sizeof(char), sizeof(buffer), first_file) > 0)
    {
        if (fwrite(buffer, sizeof(char), bytes, second_file) != bytes)
        {
            printf("Can't write to a file\n");
            fclose(first_file);
            fclose(second_file);
            return error_with_writing_file;
        }
    }

    fclose(first_file);
    fclose(second_file);

    return 0;
}
