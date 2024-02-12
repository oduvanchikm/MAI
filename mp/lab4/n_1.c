#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <unistd.h>

typedef enum
{
    OK,
    ERROR_WITH_MEMORY_ALLOCATION,
    INVALID_INPUT,
    ERROR_WITH_OPENING_FILE,
    ERROR_WITH_FILE_TRUNCATION

} status_code;

void print_errors(int flag)
{
    switch(flag)
    {
        case ERROR_WITH_MEMORY_ALLOCATION:
            printf("Error with memory allocation\n");
            break;

        case INVALID_INPUT:
            printf("Invalid input\n");
            break;

        case ERROR_WITH_OPENING_FILE:
            printf("Error with opening file\n");
            break;

        case ERROR_WITH_FILE_TRUNCATION:
            printf("Error with file truncation\n");
            break;

        default:
            break;
    }
}

typedef struct Hash_items
{
    char* name;
    char* value;
    unsigned long hash;
    struct Hash_items* next;

} Hash_items;

typedef struct Hash_table
{
    int hash_size;
    Hash_items** items;

} Hash_table;

int hash_function(char* name)
{
    int res = 0;
    int power = 1;

    for (int i = 0; i < (int)strlen(name); i++)
    {
        int char_value;

        if (name[i] >= '0' && name[i] <= '9')
        {
            char_value = name[i] - '0';
        }
        else if ('A' <= name[i] && name[i] <= 'Z')
        {
            char_value = name[i] - 'A' + 10;
        }
        else if ('a' <= name[i] && name[i] <= 'z')
        {
            char_value = name[i] - 'a' + 36;
        }

        res += (char_value * power);
        power *= 62;
    }

    return res;
}

status_code check_hash_table(Hash_table* hash_table, int* count)
{
    int min = INT_MAX;
    int max = INT_MIN;

    for (int i = 0; i < hash_table->hash_size; i++)
    {
        int m = 0;
        Hash_items* current = hash_table->items[i];
        while (current != NULL)
        {
            m++;
            (*count)++;
            current = current->next;
        }

        if (m > max)
        {
            max = m;
        }

        if (m < min)
        {
            min = m;
        }
    }
    if (min == 0)
    {
        if (max >= 2)
        {
            return INVALID_INPUT;
        }
        else
        {
            return OK;
        }
    }
    if (max / min >= 2)
    {
        return INVALID_INPUT;
    }
    return OK;
}

status_code create_hash_table(Hash_table** hash_table,int size_of_hash_table)
{
    (*hash_table) = (Hash_table*)malloc(sizeof(Hash_table));
    if (!(*hash_table))
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    (*hash_table)->hash_size = size_of_hash_table;

    (*hash_table)->items = (Hash_items**)malloc(sizeof(Hash_items*) * size_of_hash_table);
    if (!(*hash_table)->items)
    {
        free(*hash_table);
        (*hash_table) = NULL;
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    for (int i = 0; i < (*hash_table)->hash_size; i++)
    {
        (*hash_table)->items[i] = NULL;
    }

    return OK;
}

status_code insert_in_hash_table(Hash_table* hash_table, char* name, char* value)
{
    unsigned long hash_value = hash_function(name);

    unsigned long index = hash_value % hash_table->hash_size;

    Hash_items* new_item = (Hash_items*)malloc(sizeof(Hash_items));
    if (!new_item)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    new_item->hash = hash_value;
    new_item->name = strdup(name);
    if (!new_item->name)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    new_item->value = strdup(value);
    if (!new_item->value)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    new_item->next = hash_table->items[index];
    hash_table->items[index] = new_item;

    return OK;
}

char* find_word(Hash_table* hash_table, char* name)
{
    unsigned long hash_value = hash_function(name);

    unsigned long index = hash_value % hash_table->hash_size;

    Hash_items* items = hash_table->items[index];

    while(items != NULL)
    {
        if(strcmp(items->name, name) == 0)
        {
            return items->value;
        }

        items = items->next;
    }

    return NULL;
}

status_code read_define(FILE* file, Hash_table* hash_table)
{
    char define[8];
    char def_name[100];
    char value[100];

    fscanf(file, "%s", define);
    while (strcmp(define, "#define") == 0)
    {
        fscanf(file, "%s %s\n", def_name, value);

        status_code st_insert = insert_in_hash_table(hash_table, def_name, value);
        if (st_insert != OK)
        {
            return ERROR_WITH_MEMORY_ALLOCATION;
        }

        else
        {
            fscanf(file, "%s", define);
        }
    }

    fseek(file, ftell(file) - strlen(define), SEEK_SET);

    return OK;
}


status_code replace_in_file(Hash_table* hash_table, FILE* file)
{
    int start_index = ftell(file);
    char string[256];
    fseek(file, 0, SEEK_END);

    long size_file = ftell(file) - start_index + 1;

    fseek(file, start_index, SEEK_SET);

    char *buffer = (char*)malloc(size_file);
    if (!buffer)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    int index_buffer = 0;
    char c = fgetc(file);
    int flag = 0;

    while(c != EOF && !isalnum(c))
    {
        if (index_buffer == size_file)
        {
            char* temp = realloc(buffer, size_file * 2);
            if (!temp)
            {
                return ERROR_WITH_MEMORY_ALLOCATION;
            }

            buffer = temp;
            size_file *= 2;
        }

        buffer[index_buffer] = c;
        index_buffer++;

        c = fgetc(file);
    }

    if (c == EOF)
    {
        flag = 1;
    }

    fseek(file, -1, SEEK_CUR);

    while (!flag && fscanf(file, "%s", string) == 1)
    {
        if (index_buffer == size_file)
        {
            char* temp = realloc(buffer, size_file * 2);
            if (!temp)
            {
                return ERROR_WITH_MEMORY_ALLOCATION;
            }

            buffer = temp;
            size_file *= 2;
        }

        char *value = find_word(hash_table, string);
        if (value != NULL)
        {
            if (index_buffer + strlen(value) >= size_file)
            {
                char *temp = realloc(buffer, size_file * 2);
                if (!temp)
                {
                    return ERROR_WITH_MEMORY_ALLOCATION;
                }

                buffer = temp;
                size_file *= 2;
            }

            for (int j = 0; j < strlen(value); j++)
            {
                buffer[index_buffer] = value[j];
                index_buffer++;
            }
        }

        else
        {
            if (index_buffer + strlen(string) >= size_file)
            {
                char *temp = realloc(buffer, size_file * 2);
                if (!temp)
                {
                    return ERROR_WITH_MEMORY_ALLOCATION;
                }

                buffer = temp;
                size_file *= 2;
            }

            index_buffer += sprintf(&(buffer[index_buffer]), "%s", string);
        }

        c = fgetc(file);
        while (c != EOF && !isalnum(c))
        {
            if (index_buffer == size_file)
            {
                char *temp = realloc(buffer, size_file * 2);
                if (!temp)
                {
                    return ERROR_WITH_MEMORY_ALLOCATION;
                }

                buffer = temp;
                size_file *= 2;
            }

            buffer[index_buffer] = c;
            index_buffer++;
            c = fgetc(file);

        }
        if (c == EOF)
        {
            flag = 1;
        }

        fseek(file, -1, SEEK_CUR);
    }

    printf("%s\n", buffer);
    fseek(file, start_index, SEEK_SET);

    for (int i = 0; i < index_buffer; i++)
    {
        fprintf(file, "%c", buffer[i]);
    }

    int result = ftruncate(fileno(file), start_index + index_buffer);
    if (result != 0)
    {
        return ERROR_WITH_FILE_TRUNCATION;
    }

    while(( c = fgetc(file)) != EOF)
    {
        fprintf(file, "%c", ' ');
    }

    free(buffer);
    return OK;
}

void print_hash_table(Hash_table* hash_table)
{
    for (int i = 0; i < hash_table->hash_size; i++)
    {
        if (hash_table->items[i] != NULL)
        {
            Hash_items* current = hash_table->items[i];
            while (current != NULL)
            {
                printf("%s ", current->value);
                current = current->next;
            }

            printf("\n");
        }
    }
}

void free_table(Hash_table* hash_table)
{
    for (int i = 0; i < hash_table->hash_size; i++)
    {
        if (hash_table->items[i] != NULL)
        {
            Hash_items* current = hash_table->items[i];
            while(current != NULL)
            {
                Hash_items* prev = current;
                current = current->next;
                free(prev->name);
                free(prev->value);
                free(prev);
            }
            free(current);
        }
    }
    free(hash_table->items);
    free(hash_table);
}

status_code resize_hash_table(Hash_table** hash_table, int new_size)
{
    Hash_table* new_table;
    status_code st_create = create_hash_table(&new_table, new_size);
    if (st_create != OK)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    for (int i = 0; i < (*hash_table)->hash_size; i++)
    {
        if ((*hash_table)->items[i] != NULL)
        {
            Hash_items* current = (*hash_table)->items[i];
            while (current != NULL)
            {
                unsigned long hash = current->hash;
                int new_index = hash % new_size;

                Hash_items* new_items = (Hash_items*)malloc(sizeof(Hash_items*));
                if (!new_items)
                {
                    return ERROR_WITH_MEMORY_ALLOCATION;
                }

                new_items->hash = hash;
                new_items->name = strdup(current->name);
                if (!new_items->name)
                {
                    return ERROR_WITH_MEMORY_ALLOCATION;
                }

                new_items->value = strdup(current->value);
                if (new_items->value)
                {
                    return ERROR_WITH_MEMORY_ALLOCATION;
                }

                new_items->next = new_table->items[new_index];
                new_table->items[new_index] = new_items;
                current = current->next;
            }
        }
    }
    free_table(*hash_table);
    *hash_table = new_table;

    return OK;
}

int is_prime(int n)
{
    if (n <= 1)
    {
        return 0;
    }
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Error with number of arguments\nPlease enter input file\n");
        return 1;
    }

    FILE* input_file = fopen(argv[1], "r+");
    if (!input_file)
    {
        printf("Error with opening file\n");
        return 1;
    }

    int hash_table_size = 128;

    Hash_table* hash_table;

    status_code st_create = create_hash_table(&hash_table, hash_table_size);
    if (st_create)
    {
        print_errors(st_create);
    }

    status_code st_read_define = read_define(input_file, hash_table);
    if (st_read_define != OK)
    {
        print_errors(st_read_define);
        free_table(hash_table);
        return 1;
    }

    int count = 0;

    status_code st_check = check_hash_table(hash_table, &count);
    while (st_check != OK)
    {
        int new_size = count * 2;

        while (!is_prime(new_size))
        {
            new_size++;
        }

        printf("%d\n", new_size);

        status_code st_change_size = resize_hash_table(&hash_table, new_size);
        if (st_change_size != OK)
        {
            print_errors(st_change_size);
            free_table(hash_table);
            return 1;
        }
    }

    status_code st_read_file = replace_in_file(hash_table, input_file);
    if (st_read_file != OK)
    {
        print_errors(st_read_file);
    }

    fclose(input_file);
    free_table(hash_table);
    return 0;
}
