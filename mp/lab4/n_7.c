#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct
{
    int value;
    char *name;

} MemoryCell;

typedef struct
{
    MemoryCell **data;
    int size;
    int capasity;

} List;

typedef enum
{
    OK,
    ERROR_WITH_MEMORY_ALLOCATION,
    INVALID_INPUT,

} status_code;

void print_error(int flag)
{
    switch (flag)
    {
        case ERROR_WITH_MEMORY_ALLOCATION:
            printf("Error with memory allocation\n");
            break;

        case INVALID_INPUT:
            printf("Invalid input\n");
            break;

        default:
            break;
    }
}

bool check_is_digit(const char* string)
{
    int len = strlen(string);

    for (int i = 0; i < len; i++)
    {
        if (!isdigit(string[i]))
        {
            return false;
        }
    }
    return true;
}

List* create_list(int capasity)
{
    List* result = (List*)malloc(sizeof(List));
    if (!result)
    {
        return NULL;
    }

    result->data = malloc(sizeof(MemoryCell*) * capasity);
    if (!result->data)
    {
        free(result);
        return NULL;
    }

    for (int i = 0; i < capasity; i++)
    {
        result->data[i] = NULL;
    }

    result->capasity = capasity;
    result->size = 0;
    return result;
}

MemoryCell* create_MemoryCell(char *name, int value)
{
    MemoryCell* res = (MemoryCell*)malloc(sizeof(MemoryCell));
    if (!res)
    {
        return NULL;
    }

    res->name = strdup(name);
    res->value = value;
    return res;
}

int comparator(const void *memory_cell_1, const void *memory_cell_2)
{
    const MemoryCell *m1 = *((const MemoryCell **)memory_cell_1);
    const MemoryCell *m2 = *((const MemoryCell **)memory_cell_2);
    return strcmp(m1->name, m2->name);
}

status_code insert_in_array(List* all_array, MemoryCell* elem)
{
    if (all_array->size + 1 >= all_array->capasity)
    {
        all_array->capasity *= 2;
        MemoryCell **temp = realloc(all_array->data, sizeof(MemoryCell*) * all_array->capasity);
        if (!temp)
        {
            all_array->capasity /= 2;
            return ERROR_WITH_MEMORY_ALLOCATION;
        }

        all_array->data = temp;
    }

    all_array->data[all_array->size] = elem;
    (all_array->size)++;
    qsort(all_array->data, all_array->size, sizeof(MemoryCell*), comparator);

    return OK;
}
char* get_expression(FILE *file)
{
    int size = 10;
    char *string = (char*)malloc(size * sizeof(char));
    if (!string)
    {
        return NULL;
    }

    char c = fgetc(file);
    int i = 0;
    while (c != EOF && c != ';')
    {
        if (i >= size)
        {
            size *= 2;
            char *temp = realloc(string, size);
            if (!temp)
            {
                free(string);
                return NULL;
            }
            string = temp;
        }
        string[i] = c;
        i++;
        c = fgetc(file);
    }

    if (i == 0)
    {
        free(string);
        return NULL;
    }

    string[i] = ';';
    string[i + 1] = '\0';
    return string;
}
int dechotomy_search(List* lists, char* key)
{
    int low = 0;
    int high = lists->size;
    int mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (lists->data[mid] == NULL)
        {
            return -1;
        }
        MemoryCell* elem = lists->data[mid];

        if (strcmp(key, elem->name) == 0)
        {
            return mid;
        }

        else if (strcmp(key, elem->name) > 0)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}

int is_operator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%');
}

void print_all(List *lists)
{
    printf("All variables:\n");

    for (int i = 0; i < lists->size; i++)
    {
        printf("%s %d\n", lists->data[i]->name, lists->data[i]->value);
    }
}

void print_elem(List* all_data, int index)
{
    printf("Value of variable %s is %d\n", all_data->data[index]->name, all_data->data[index]->value);
}

status_code read_one_str(char* string, List* all_data)
{
    char first_part[256];
    char second_part[256];
    char third_part[256];
    int index = 0;
    int index_for_first_part = 0;

    while (!isalnum(string[index]))
    {
        index++;
    }

    while (string[index] != ';' && string[index] != '=')
    {
        first_part[index_for_first_part] = string[index];
        index++;
        index_for_first_part++;
    }

    first_part[index_for_first_part] = '\0';

    int is_exist = 0;
    int index_1 = dechotomy_search(all_data, first_part);
    if (index_1 != -1)
    {
        is_exist = 1;
    }

    if (string[index] == '=')
    {
        index++;
        int index_for_second_part = 0;
        while (string[index] != ';' && !is_operator(string[index]))
        {
            second_part[index_for_second_part] = string[index];
            index++;
            index_for_second_part++;
        }

        second_part[index_for_second_part] = '\0';

        if (string[index] == ';')
        {
            if (check_is_digit(second_part))
            {
                if (is_exist)
                {
                    all_data->data[index_1]->value = atoi(second_part);
                }

                else
                {
                    MemoryCell* new_el = create_MemoryCell(first_part, atoi(second_part));
                    if (!new_el)
                    {
                        return ERROR_WITH_MEMORY_ALLOCATION;
                    }

                    if (insert_in_array(all_data, new_el) != OK)
                    {
                        return ERROR_WITH_MEMORY_ALLOCATION;
                    }
                    return OK;
                }
                return OK;
            }

            else
            {
                int index_2 = dechotomy_search(all_data, second_part);

                if (index_2 != -1)
                {
                    if (is_exist)
                    {
                        all_data->data[index_1]->value = all_data->data[index_2]->value;
                        return OK;
                    }

                    else
                    {
                        MemoryCell *new_al = create_MemoryCell(first_part, all_data->data[index_2]->value);
                        if (insert_in_array(all_data, new_al) != OK)
                        {
                            return ERROR_WITH_MEMORY_ALLOCATION;
                        }
                        return OK;
                    }
                }
                else
                    return INVALID_INPUT;
            }
        }
        if (is_operator(string[index]))
        {
            char operator = string[index];
            index++;

            int index_for_third_part = 0;

            while (string[index] != ';' && string[index] != '\0' && string[index] != EOF)
            {
                third_part[index_for_third_part] = string[index];
                index++;
                index_for_third_part++;
            }

            third_part[index_for_third_part] = '\0';

            int result;
            if (check_is_digit(second_part))
            {
                result = atoi(second_part);
            }

            else
            {
                int index_2 = dechotomy_search(all_data, second_part);
                if (index_2 != -1)
                {
                    result = all_data->data[index_2]->value;
                }
                else
                    return INVALID_INPUT;
            }
            int third_part_int;

            if (check_is_digit(third_part))
            {
                third_part_int = atoi(third_part);
            }

            else
            {
                int index_3 = dechotomy_search(all_data, third_part);
                if (index_3 != -1)
                {
                    third_part_int = all_data->data[index_3]->value;
                }
                else
                    return INVALID_INPUT;
            }
            switch (operator)
            {
                case '+':
                    result += third_part_int;
                    break;

                case '-':
                    result -= third_part_int;
                    break;

                case '*':
                    result *= third_part_int;
                    break;

                case '/':
                    result /= third_part_int;
                    break;

                case '%':
                    result %= third_part_int;
                    break;

                default:
                    break;
            }

            if (is_exist)
            {
                all_data->data[index_1]->value = result;
                return OK;
            }

            else
            {
                MemoryCell *new_el = create_MemoryCell(first_part, result);
                if (new_el == NULL)
                {
                    return ERROR_WITH_MEMORY_ALLOCATION;
                }
                if (insert_in_array(all_data, new_el) != OK)
                {
                    return ERROR_WITH_MEMORY_ALLOCATION;
                }
                return OK;
            }
        }
    }

    if (string[index] == ';')
    {
        if (strlen(first_part) == 5)
        {
            print_all(all_data);
            return OK;
        }

        else
        {
            char* name = &(first_part[6]);
            int index = dechotomy_search(all_data, name);
            if (index == -1)
            {
                return INVALID_INPUT;
            }
            print_elem(all_data, index);
            return OK;
        }
    }
}

void free_all(List* data)
{
    for (int i = 0; i < data->capasity; i++)
    {
        if (data->data[i] != NULL)
        {
            free(data->data[i]->name);
        }
        free(data->data[i]);
    }

    free(data->data);
    free(data);
}

int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Error with opening file\n");
        return 1;
    }

    List *all_data = create_list(10);
    char *line;

    while (line = get_expression(file))
    {
        status_code st = read_one_str(line, all_data);
        if (st != OK)
        {
            print_error(st);
            free_all(all_data);
            free(line);
            fclose(file);
            return 1;
        }

        free(line);
    }

    free_all(all_data);
    fclose(file);
    return 0;
}