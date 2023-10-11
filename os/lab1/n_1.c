#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

enum status_file
{
    error_filename,
    error_with_open_file,
    error_with_writing_file,
    error_with_reading_file,
};

void print_file_state(FILE* file)
{
    printf("__pad5: %ld ", file->__pad5);
    // printf("_chain: %d ", file->_chain);
    // printf("_codecvt: %d ", file->_codecvt);
    printf("_cur_column: %d ", file->_cur_column);
    printf("_fileno: %d ", file->_fileno);
    printf("_flags: %d ", file->_flags);
    printf("_freeres_buf: %p ", file->_freeres_buf);
    printf("_freeres_list: %p ", file->_freeres_list);
    printf("_IO_backup_base: %p ", file->_IO_backup_base);
    printf("_IO_buf_base: %p ", file->_IO_buf_base);
    printf("_IO_buf_end: %p ", file->_IO_buf_end);

    printf("_IO_read_base: %p ", file->_IO_read_base);
    printf("_IO_read_end: %p ", file->_IO_read_end);
    printf("_IO_read_ptr: %p ", file->_IO_read_ptr);
    printf("_IO_save_base: %p ", file->_IO_save_base);
    printf("_IO_save_end: %p ", file->_IO_save_end);
    printf("_IO_write_base: %p ", file->_IO_write_base);
    printf("_IO_write_end: %p ", file->_IO_write_end);
    printf("_IO_write_ptr: %p ", file->_IO_write_ptr);
    printf("_lock: %p ", file->_lock);
    printf("_markers: %p ", file->_markers);
    printf("_mode: %d ", file->_mode);
    printf("_offset: %ld ", file->_offset);

    printf("_shortbuf: %p ", file->_shortbuf);
    printf("_unused2: %p ", file->_unused2);
    printf("_vtable_offset: %d ", file->_vtable_offset);
    printf("_wide_data: %p ", file->_wide_data);
}

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

    fseek(filew, 0, SEEK_SET);

    int size_file = sizeof(arr_bytes) / sizeof(arr_bytes[0]);

    char array[11] = {};

    if (fread(array, sizeof(char), 11, filew) != 11)
    {
        printf("Can't read a file\n");
        fclose(filew);
        return error_with_reading_file;
    }

    for (int i = 0; i < size_file; i++)
    {
        printf("%d\n", array[i]);
        print_file_state(filew);
        printf("\n");
    }

    fclose(filew); 

    FILE* filer = fopen(argv[1], "rb");
    if (filer == NULL)
    {
        printf("Can't open the file\n");
        return error_with_open_file;
    }

    fseek(filer, 3, SEEK_SET);

    char arr_bytes_res[4] = {0};

    if (fread(arr_bytes_res, sizeof(char), 4, filer) != 4)
    {
        printf("Can't read a file\n");
        fclose(filer);
        return error_with_reading_file;
    }
    printf("After moving the pointer to 3 and reading 4 bytes: \n");

    for (int i = 0; i < 4; ++i)
    {
        printf("%d ", arr_bytes_res[i]);
    }
    printf("\n");
    fclose(filer);

    return 0;
}