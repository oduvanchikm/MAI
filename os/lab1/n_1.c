#include <stdio.h>
#include <stdlib.h>

enum status_file
{
    error_filename,
    error_with_open_file,
    error_with_writing_file,
    error_with_reading_file,
};

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Error, enter the file name\n");
        return error_filename;
    }

    FILE* filew = fopen(argv[1], "wb+");

    if (filew == NULL)
    {
        printf("Can't open the file\n");
        return error_with_open_file;
    }

    char arr_bytes[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};

    if (fwrite(arr_bytes, sizeof(arr_bytes[0]), sizeof(arr_bytes) / sizeof(arr_bytes[0]), filew) != sizeof(arr_bytes) / sizeof(arr_bytes[0]))
    {
        printf("Can't write to a file\n");
        fclose(filew);
        return error_with_writing_file;
    }
    fclose(filew);

    FILE* filer = fopen(argv[1], "rb");
    if (filer == NULL)
    {
        printf("Can't open the file\n");
        return error_with_open_file;
    }

    fseek(filer, 3, SEEK_SET);

    char arr_bytes_res[11] = {0};

    for (int i = 0; i < 11; i++)
    {
        if (fread(&arr_bytes_res[i], sizeof(char), 1, filer) != sizeof(char))
        {
            printf("Can't read a file\n");
            fclose(filer);
            return error_with_reading_file;
        }
    }

    for (int i = 0; i < 11; ++i)
    {
        printf("%x ", arr_bytes_res[i]);
    }

    printf("\n");

    fclose(filer);

    return 0;
}