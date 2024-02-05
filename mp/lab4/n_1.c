#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define HASH_SIZE 128

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

Hash_items* find_word(Hash_table* hash_table, char* name)
{
    int index = hash_function(name) % hash_table->hash_size;
    Hash_items* macro = hash_table->items[index];

    while (macro != NULL && strcmp(name, macro->name) != 0)
    {
        macro = macro->next;
    }

    return macro;
}

bool check_string_with_define(const char* line)
{
//    printf("%s\n", line);
    int count_of_spaces = 0;
    int i = 0;
    while (line[i])
    {
        if (line[i] == ' ')
        {
            count_of_spaces++;
        }
        i++;
    }

    if (count_of_spaces != 2)
    {
        return false;
    }

    char first_part[8];
    int index_for_first_part = 0;
    int j = 0;
    while (line[j] != ' ')
    {
        first_part[index_for_first_part++] = line[j++];
    }
    first_part[index_for_first_part] = '\0';
//    printf("%s\n", first_part);

    if (strcmp(first_part, "#define") != 0)
    {
        return false;
    }

    char second_part[256];
    int index_for_second_part = 0;
    j++;

    while (line[j] != ' ')
    {
        second_part[index_for_second_part++] = line[j++];
    }
    second_part[index_for_second_part] = '\0';
//    printf("%s\n", second_part);

    for (int k = 0; second_part[k]; k++)
    {
        if (!isalnum(second_part[k]))
        {
            return false;
        }
    }
    return true;
}

status_code process(const char* file_path, Hash_table* hash_table)
{
    FILE *file = fopen(file_path, "r+");
    if (!file)
    {
        return ERROR_WITH_OPENING_FILE;
    }

    char line[256];
    char new_text[256];
    new_text[0] = '\0';
    printf("erere\n");


    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (check_string_with_define(line))
        {
            char def_name[256];
            char value[256];
            if (sscanf(line, "#define %s %s", def_name, value) == 2)
            {
                status_code st = insert_in_hash_table(hash_table, def_name, value);
                if (st != OK)
                {
                    fclose(file);
                    return ERROR_WITH_MEMORY_ALLOCATION;
                }
            }
        }
        else
        {
            char word[256];
            char *buffer = line;
            new_text[0] = '\0';
            while (sscanf(buffer, "%s", word) == 1)
            {
                Hash_items *items = find_word(hash_table, word);
                if (items)
                {
                    strcat(new_text, items->value);
                    strcat(new_text, " ");
                }
                else
                {
                    strcat(new_text, word);
                    strcat(new_text, " ");
                }
                buffer += strlen(word) + 1;
            }
            printf("%s", new_text);
            fprintf(file, "%s\n", new_text);
        }
    }
    fclose(file);
    return OK;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("error with number of arguments\n");
        return 0;
    }

    Hash_table *hash_table = NULL;
    int size_of_table = 10;
    int capacity = 10;

    status_code st = create_hash_table(&hash_table, capacity, size_of_table);
    if (st == OK) {
        status_code st_file = process(argv[1], hash_table);
        if (st_file != OK) {
            printf("Error processing file\n");
        } else {
            printf("File processed successfully\n");
        }

        destroy_table(hash_table);
    } else {
        printf("Error creating hash table\n");
    }

    return 0;
}