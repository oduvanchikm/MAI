#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef enum
{
    OK,
    ERROR_WITH_MEMORY_ALLOCATION,
    INVALID_INPUT,
    ERROR_WITH_OPENING_FILE

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

        default:
            break;
    }
}

typedef struct Hash_items
{
    char* name;
    char* value;
    struct Hash_items* next;

} Hash_items;

typedef struct Hash_table
{
    int hash_size;
    int capacity;
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

status_code create_hash_table(Hash_table** hash_table, int capacity, int size_of_hash_table)
{
    (*hash_table) = (Hash_table*)malloc(sizeof(Hash_table));
    if (!(*hash_table))
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    (*hash_table)->hash_size = size_of_hash_table;
    (*hash_table)->capacity = capacity;

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

void destroy_table(Hash_table* hash_table)
{
    for (int i = 0; i < hash_table->hash_size; i++)
    {
        if (hash_table->items[i] != NULL)
        {
            Hash_items * current = hash_table->items[i];
            while(current != NULL)
            {
                Hash_items * previous = current;
                current = current->next;
                free(previous->name);
                free(previous->value);
                free(previous);
            }
            free(current);
        }
    }
    free(hash_table->items);
    free(hash_table);
}

status_code resize_hash_table(Hash_table* hash_table, Hash_table** new_hash_table)
{
    status_code st_creat = create_hash_table(new_hash_table, hash_table->capacity * 2, hash_table->hash_size * 2);
    if (st_creat == ERROR_WITH_MEMORY_ALLOCATION)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    for (int i = 0; i < hash_table->hash_size; i++)
    {
        Hash_items* current_hash_table = hash_table->items[i];

        while (current_hash_table)
        {
            Hash_items* next = current_hash_table->next;
            int new_index = hash_function(current_hash_table->name);
            current_hash_table->next = (*new_hash_table)->items[new_index];
            (*new_hash_table)->items[new_index] = current_hash_table;
            current_hash_table = next;
        }
    }

    destroy_table(hash_table);
    return OK;
}

void print_hash_table(Hash_table* hash_table)
{
    for (int i = 0; i < hash_table->hash_size; i++)
    {
        if (hash_table->items[i] != NULL)
        {
            Hash_items * current = hash_table->items[i];
            while (current != NULL)
            {
                printf("%s ", current->value);
                current = current->next;
            }
            printf("\n");
        }
    }
}

status_code insert_in_hash_table(Hash_table* hash_table, char* name, char* value)
{
    int index = hash_function(name) % hash_table->hash_size;

    Hash_items* new_item = (Hash_items*)malloc(sizeof(Hash_items));
    if (!new_item)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    new_item->name = strdup(name);
    new_item->value = strdup(value);
    new_item->next = NULL;

    new_item->next = hash_table->items[index];
    hash_table->items[index] = new_item;

    return OK;
}

char* find_word(Hash_table* hash_table, char *key)
{
    unsigned long hash_value = hash_function(key);
    unsigned long hash = hash_value % hash_table->hash_size;

    Hash_items* items = hash_table->items[hash];
    while(items != NULL)
    {
        if(strcmp(items->name, key) == 0)
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
        if (insert_in_hash_table(hash_table, def_name, value) != OK)
        {
            return ERROR_WITH_MEMORY_ALLOCATION;
        }
        fscanf(file, "%s", define);
    }

    fseek(file, ftell(file) - strlen(define), SEEK_SET);

    return OK;
}

status_code all_functions(Hash_table* hash_table, FILE* file)
{
    int start_index = ftell(file);
    char str[256];

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file) - start_index + 1;

    fseek(file, start_index, SEEK_SET);

    char* buffer = (char*)malloc(file_size);
    if (buffer == NULL)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    int index_buffer = 0;
    char c = fgetc(file);
    int flag = 0;

    while(c != EOF && !isalnum(c))
    {
        if (index_buffer == file_size)
        {
            char* temp = realloc(buffer,file_size * 2);
            if (!temp)
            {
                return ERROR_WITH_MEMORY_ALLOCATION;
            }

            buffer = temp;
            file_size *= 2;
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

    while (!flag && fscanf(file, "%s", str) == 1)
    {
        if (index_buffer == file_size)
        {
            char* temp = realloc(buffer, file_size * 2);
            if (!temp)
            {
                return ERROR_WITH_MEMORY_ALLOCATION;
            }

            buffer = temp;
            file_size *= 2;
        }

        char *value = find_word(hash_table, str);
        if (value != NULL)
        {
            if (index_buffer + strlen(value) >= file_size)
            {
                char *temp = realloc(buffer, file_size * 2);
                if (!temp)
                {
                    return ERROR_WITH_MEMORY_ALLOCATION;
                }

                buffer = temp;
                file_size *= 2;
            }

            for (int j = 0; j < strlen(value); j++)
            {
                buffer[index_buffer] = value[j];
                index_buffer++;
            }
        }

        else
        {
            if (index_buffer + strlen(str) >= file_size)
            {
                char *temp = realloc(buffer, file_size * 2);
                if (!temp)
                {
                    return ERROR_WITH_MEMORY_ALLOCATION;
                }

                buffer = temp;
                file_size *= 2;
            }
            index_buffer += sprintf(&(buffer[index_buffer]), "%s", str);
        }

        c = fgetc(file);

        while (c != EOF && !isalnum(c))
        {
            if (index_buffer == file_size)
            {
                char *temp = realloc(buffer, file_size * 2);
                if (!temp)
                {
                    return ERROR_WITH_MEMORY_ALLOCATION;
                }
                buffer = temp;
                file_size *= 2;
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

    while(( c = fgetc(file)) != EOF )
    {
        fprintf(file, "%c", ' ');
    }

    free(buffer);

    return OK;
}

status_code check(Hash_table* hash_table, int* count)
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
        printf("Wrong count of arguments\n");
        return 0;
    }

    FILE* input_file = fopen(argv[1], "r+");
    if (!input_file)
    {
        printf("Error with opening file\n");
        return 0;
    }

    int current_size = 128;

    Hash_table* table;
    int capacity = 10;

    create_hash_table(&table, capacity, current_size);

    if (read_define(input_file, table) != OK)
    {
        print_errors(read_define(input_file, table));
        destroy_table(table);
        fclose(input_file);
        return 0;
    }

    int count = 0;

    while (check(table, &count) != OK)
    {
        int new_size = (int)(count * 2);

        while (!is_prime(new_size))
        {
            new_size++;
        }

        printf("%d\n", new_size);

        Hash_table* new_hash_table;
        if (resize_hash_table(table, &new_hash_table) != OK)
        {
            print_errors(resize_hash_table(table, &new_hash_table));
            destroy_table(table);
            fclose(input_file);
            return 1;
        }
    }

    if (all_functions(table, input_file) != OK)
    {
        print_errors(all_functions(table, input_file));
    }

    fclose(input_file);
    destroy_table(table);
    return 0;
}
