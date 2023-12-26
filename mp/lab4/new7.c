#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef enum
{
    OK,
    ERROR_WITH_MEMORY_ALLOCATION,
    INVALID_INPUT,
    ERROR_WITH_COUNT_OF_ARGUMENTS,
    ERROR_WITH_OPENING_FILE,

} status_code;

void print_errors(int flag)
{
    switch(flag)
    {
        case ERROR_WITH_COUNT_OF_ARGUMENTS:
            printf("Error with count of arguments\n");
            break;
        
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

typedef struct 
{
    char* name;
    int value;

} MemoryCell;

typedef struct 
{
    MemoryCell** array;
    int size;
    int capacity;

} List;

List* create_list(int capasity)
{
    List* new_list = (List*)malloc(sizeof(List));
    if (!new_list)
    {
        return NULL;
    }

    new_list->array = (MemoryCell**)malloc(sizeof(MemoryCell*) * capasity);
    if (!new_list->array)
    {
        free(new_list);
        return NULL;
    }

    for (int i = 0; i < capasity; i++)
    {
        new_list->array[i] = NULL;
    }

    new_list->capacity = capasity;
    new_list->size = 0;
    return new_list;
}

MemoryCell* create_memory_cell(char* name, int value)
{
    if (!name)
    {
        return NULL;
    }

    MemoryCell* new_memory_cell = (MemoryCell*)malloc(sizeof(MemoryCell));
    if (!new_memory_cell)
    {
        return NULL;
    }

    new_memory_cell->name = strdup(name);
    new_memory_cell->value = value;
    return new_memory_cell;
}

void destroy_memory_cell(MemoryCell* memory_cell)
{
    free(memory_cell->name);
    free(memory_cell);
}

void destroy_list(List* list)
{
    for (int i = 0; i < list->size; i++)
    {
        free(list->array[i]);
    }

    free(list->array);
    free(list);
}

int compare_memory_cell(const void* a, const void* b) 
{
    const MemoryCell* a_1 = *((const MemoryCell**)a);
    const MemoryCell* a_2 = *((const MemoryCell**)b);
    return strcmp(a_1->name, a_2->name);
}

status_code insert_list(List* list, MemoryCell* memory_cell)
{
    if (list->size == list->capacity)
    {
        list->capacity *= 2;
        MemoryCell** new_array = (MemoryCell**)realloc(list->array, list->capacity * sizeof(MemoryCell*));
        if (!new_array)
        {
            return ERROR_WITH_MEMORY_ALLOCATION;
        }

        list->array = new_array;
    }
    list->array[list->size] = memory_cell;
    (list->size)++;
    qsort(list->array, list->size, sizeof(MemoryCell*), compare_memory_cell);
    return OK;
}

int my_pow(int base, int power)
{
    int result;
    if (power == 0)
    {
        return 1;
    }

    else if (power == 1)
    {
        return base;
    }

    else if (power % 2 == 0)
    {
        result = my_pow(base, power / 2);
        return result * result;
    }

    else
    {
        result = my_pow(base, power - 1);
        return base * result;
    }
}

int count_digits(char operator, int* first_digit, int second_digit)
{
    switch (operator)
    {
        case '+':
            *first_digit = *first_digit + second_digit;
            break;
        
        case '-':
            *first_digit = *first_digit - second_digit;
            break;
        
        case '*':
            *first_digit = *first_digit * second_digit;
            break;
        
        case '/':
            *first_digit = *first_digit / second_digit;
            break;
        
        case '%':
            *first_digit = *first_digit % second_digit;
            break;
        
        case '^':
            *first_digit = my_pow(*first_digit, second_digit);
            break;
        
        default:
            break;

    }

    return *first_digit;
}

int is_operator(char string)
{
    return (string == '+' || string == '-' || string == '*' || string == '%' || string == '/' || string == '^');
}

bool is_digit(char* string)
{
    if ((*string) > '0' && (*string) < '9')
    {
        return true;
    }

    return false;
}

int dechotom_search(List* list, char* name)
{
    int left_index = 0;
    int right_index = list->size;

    while (left_index < right_index)
    {
        int middle_index = (left_index + right_index) / 2;

        int compare = strcmp(name, list->array[middle_index]->name);

        if (compare > 0)
        {
            left_index = middle_index + 1;
        }

        else if (compare < 0)
        {
            right_index = middle_index;
        }

        else
        {
            return middle_index;
        }
    }
    return -1;
}

char* read_string(FILE* filename)
{
    int size = 2;
    char* res_string = (char*)malloc(sizeof(char) * size);
    if (!res_string)
    {
        return NULL;
    }

    int index = 0;
    char ch;

    while ((ch = fgetc(filename)) != EOF && ch != ';')
    {
        res_string[index++] = ch;

        if (index >= size - 1)
        {
            size *= 2;
            res_string = (char*)realloc(res_string, sizeof(char) * size);
            if (!res_string)
            {
                return NULL;
            }
        }
    }

    res_string[index] = ';';
    res_string[index + 1] = '\0';

    if(ch == EOF && index == 0)
    {
        free(res_string);
        return NULL;
    }

    return res_string;
}

void print_elem(List* list, int index)
{
    printf("The value of the variable %s is %d\n", list->array[index]->name, list->array[index]->value);
}

void print_all(List* list)
{
    for (int i = 0; i < list->size; i++)
    {
        printf("%s %d\n", list->array[i]->name, list->array[i]->value);
    }
}

status_code expression_parsing(char* string, List* list)
{
    char first_part[256];
    char second_part[256];
    char third_part[256];

    int index = 0;
    int first_index = 0;
    int second_index = 0;
    int third_index = 0;

    while (!isalnum(string[index]) && string[index] != '\0')
    {
        index++;
    }

    while (string[index] != ';' && string[index] != '=' && string[index] != '\0')
    {
        first_part[first_index] = string[index];
        first_index++;
        index++;
    }

    first_part[first_index] = '\0';
    int is_exist = 0;
    int index_1 = dechotom_search(list, first_part);

    if (index_1 != -1)
    {
        is_exist = 1;
    }

    if (string[index] == '=')
    {
        index++;

        while (string[index] != ';' && string[index] != '\0' && !is_operator(string[index]))
        {
            second_part[second_index] = string[index];
            second_index++;
            index++;
        }
        second_part[second_index] = '\0';

        if (is_digit(second_part))
        {
            if (is_exist)
            {
                list->array[index_1]->value = atoi(second_part);
            }
            else
            {
                MemoryCell* new_element = create_memory_cell(first_part, atoi(second_part));
                if (!new_element)
                {
                    return ERROR_WITH_MEMORY_ALLOCATION;
                }

                if (insert_list(list, new_element) != OK)
                {
                    return ERROR_WITH_MEMORY_ALLOCATION;
                }
                return OK;
            }
            return OK;
        }
        else
        {
            int index_2 = dechotom_search(list, second_part);
            if (index_2 != -1)
            {
                if (is_exist)
                {
                    list->array[index_1]->value = list->array[index_2]->value;
                    return OK;
                }
                else
                {
                    MemoryCell* new_element = create_memory_cell(first_part, list->array[index_2]->value);
                    if (!new_element)
                    {
                        return ERROR_WITH_MEMORY_ALLOCATION;
                    }

                    if (insert_list(list, new_element) != OK)
                    {
                        return ERROR_WITH_MEMORY_ALLOCATION;
                    }
                    return OK;
                }
            }
            else
            {
                return INVALID_INPUT;
            }

        }
        
    }

    if (is_operator(string[index]))
    {
        char operator = string[index];

        index++;

        while (string[index] != ';' && string[index] != '\0' && string[index] != EOF)
        {
            third_part[third_index] = string[index];
            third_index++;
            index++;
        }

        third_part[third_index] = '\0';

        int result;

        if (isdigit(second_part))
        {
            result = atoi(second_part);
        }

        else 
        {
            int index_2 = dechotom_search(list, second_part);
            if (index_2 != -1)
            {
                result = list->array[index_2]->value;
            }

            else
            {
                return INVALID_INPUT;
            }

            int third_part_digit;

            if (is_digit(third_part))
            {
                third_part_digit = atoi(third_part);
            }
            else
            {
                int index_3 = dechotom_search(list, third_part);
                if (index_3 != -1)
                {
                    third_part_digit = list->array[index_3]->value;
                }
                else
                {
                    return INVALID_INPUT;
                }
            }

            count_digits(operator, &result, third_part_digit);

            if (is_exist)
            {
                list->array[index_1]->value = result;
                return OK;
            }
            else
            {
                MemoryCell* new_element = create_memory_cell(first_part, result);
                if (!new_element)
                {
                    return ERROR_WITH_MEMORY_ALLOCATION;
                }

                if (insert_list(list, new_element) != OK)
                {
                    return ERROR_WITH_MEMORY_ALLOCATION;
                }

                return OK;
            }
        }
    }

    else if (string[index] == ';')
    {
        if (strlen(first_part) == 5 && (strcmp(first_part, "print") == 0))
        {
            print_all(list);
            return OK;
        }
        else
        {
            char* name = &(first_part[6]);
            int index = dechotom_search(list, name);
            if (index == -1)
            {
                return INVALID_INPUT;
            }

            print_elem(list, index);
            return OK;
        }
    }
}

int main()
{
    FILE* file = fopen("t7.txt", "r");
    if (!file)
    {
        printf("Error with opening file\n");
        return 1;
    }

    char* string;
    List* list = create_list(15);

    while (string = read_string(file))
    {
        status_code st_parsing = expression_parsing(string, list);
        if (st_parsing != OK)
        {
            fclose(file);
            free(string);
            print_errors(st_parsing);
        }
    }

    destroy_list(list);
    fclose(file);
    return 0;
}