#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>

typedef enum
{
    OK, 
    ERROR_WITH_MEMORY_ALLOCATION,
    INVALID_INPUT,

} status_code;

typedef struct 
{
    char* string;
    int length;
} String;

void print_errors(int flag)
{
    switch(flag)
    {
        case ERROR_WITH_MEMORY_ALLOCATION:
            printf("Failed to allocate memory\n");
            break;
        
        case INVALID_INPUT:
            printf("Incorrect input or incorrect values\n");
            break;

        default:
            break;
    }
}


status_code create_string(char* input, String *new_string) 
{
    if (!input)
    {
        new_string->length = 0;
        new_string->string = NULL;
        return OK;
    }

    int len = strlen(input);

    new_string->string = (char*)malloc((len + 1) * sizeof(char));

    if (!new_string->string) 
    {
        new_string->length = 0;
        new_string->string = NULL;
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    new_string->length = len;
    strcpy(new_string->string, input);
    return OK;
}

status_code delete_string(String *string)
{
    if (!string->string)
    {
        return INVALID_INPUT;
    }

    free(string->string);
    string->string = NULL;
    string->length = 0; 
    return OK;
}

int compare_string(const String* string_1, const String* string_2) 
{
    if (string_1->length < string_2->length) 
    {
        return -1;
    } 
    else if (string_1->length > string_2->length) 
    {
        return 1;
    } 
    else 
    {
        return strcmp(string_1->string, string_2->string);
    }
}

int is_equal_string(const String* string_1, const String* string_2) 
{
    return strcmp(string_1->string, string_2->string) == 0;
}

status_code copy_string(const String* first, String* second) 
{
    if (!first || !second)
    {
        return INVALID_INPUT;
    }

    free(second->string);
    // second->length = first->length;
    second->string = (char*)malloc((first->length + 1) * sizeof(char));

    if (!second->string)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }
    
    strcpy(second->string, first->string);

    return OK;
}

String* copy_in_newstring(const String* string) 
{
    int len = string->length;

    String* copy = malloc(sizeof(String) * (len + 1));

    if (!copy)
    {
        return NULL;
    }

    copy->length = string->length;
    copy->string = (char*)malloc((copy->length + 1) * sizeof(char));

    if (!copy->string)
    {
        free(copy);
        return NULL;
    }

    strcpy(copy->string, string->string);

    return copy;
}

status_code concat_string(String* string_1, const String* string_2) 
{
    int length = string_1->length + string_2->length;

    char* new_string = (char*)malloc((length + 1) * sizeof(char));

    if (!new_string)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    strcpy(new_string, string_1->string);
    strcat(new_string, string_2->string);
    
    free(string_1->string);
    string_1->length = length;
    string_1->string = new_string;
    return OK;
}

int main() 
{
    String str_1, str_2;

    create_string("3487594789239432", &str_1);
    create_string("348759fojrfrffr", &str_2);

    printf("String 1: %s\n", str_1.string);
    printf("String 2: %s\n", str_2.string);
    
    printf("Comparison result: %d\n", compare_string(&str_1, &str_2));
    printf("Equality result: %d\n", is_equal_string(&str_1, &str_2));
    
    String* copy = copy_in_newstring(&str_1);

    printf("Copy in new string: %s\n", copy->string);

    free(copy);

    status_code concat_status = concat_string(&str_1, &str_2);
    if (concat_status == OK) 
    {
        printf("Concatenated result str_1 and str_2: %s\n", str_1.string);
    } 
    else 
    {
        print_errors(concat_status);
    }

    status_code copy_status = copy_string(&str_1, &str_2);
    if (copy_status == OK) 
    {
        printf("Copied result from str_1 to str_2: %s\n", str_2.string);
    } 
    else 
    {
        print_errors(copy_status);
    }
    
    delete_string(&str_1);
    delete_string(&str_2);
    
    return 0;
}
