#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>

enum status_code 
{
    OK,
    WRONG_BASE,
    INVALID_PARAMETER,
    ERROR_WITH_MEMORY_ALLOCATION
};

void print_errors(int flag) 
{
    switch (flag) 
    {
        case WRONG_BASE:
            printf("Error: Wrong base\n");
            break;
        
        case INVALID_PARAMETER:
            printf("Error: Invalid parameter\n");
            break;

        case ERROR_WITH_MEMORY_ALLOCATION:
            printf("Error: Memory allocation error\n");
            break;
    }
}

bool checking_valid_number(char *digits, int base) 
{
    int i = 0;

    if (!digits)
    {
        return false;
    }

    if(digits[i] == '-') 
    {
        i = 1;
    }

    if (base >= 10)
    {
        while(digits[i])
        {
            if (digits[i] - 'A' + 10 >= base) 
            {
                return false;
            }
            i++;
        }
    }
    else 
    {
        while(digits[i])
        {
            if (digits[i] - '0' >= base) 
            {
                return false;
            }
            i++;
        }
    }
    return true;
}

enum status_code remove_zero(char* str) 
{
    int i = 0;
    int j = 0;
    while (str[i] == '0' || str[i] == '-') 
    {
        if(str[i] == '-') 
        {
            str[j++] = '-';
        }

        i++;
    }
    while (str[i]) 
    {
        if(str[i] >= '0' && str[i] <= '9') 
        {
            str[j++] = str[i];
        }
        i++;
    }

    str[j] = '\0';

    return OK;
}

enum status_code add_two_digits(char *num1, char *num2, int base, char** result) 
{
    if (num1 == NULL || num2 == NULL)
    {
        return INVALID_PARAMETER;
    }

    if (!(checking_valid_number(num1, base)) || !(checking_valid_number(num2, base)))
    {
        return INVALID_PARAMETER;
    }

    int len1 = strlen(num1);
    int len2 = strlen(num2);

    int carry = 0;

    int max_len = (len1 > len2 ? len1 : len2) + 1;

    *result = (char*)malloc((max_len + 1) * sizeof(char));

    if(*result == NULL)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    (*result)[max_len] = '\0';

    for (int i = max_len - 1; i >= 0; i--)
    {
        int a = (len1 - 1 >= 0) ? num1[len1 - 1] - '0' : 0;
        int b = (len2 - 1 >= 0) ? num2[len2 - 1] - '0' : 0;

        int sum = a + b + carry;
        (*result)[i] = (sum % base) + '0';
        carry = sum / base;
        len1--;
        len2--;
    }

    remove_zero(*result);
    return OK;
}

enum status_code sum_in_base(int base, int count, char** result, ...) 
{
    va_list args;

    va_start(args, result);

    if (count <= 0)
    {
        return INVALID_PARAMETER;
    }

    char* first_num = (char*)malloc(2 * sizeof(char));

    if (first_num == NULL)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    first_num[1] = '\0';

    for (int i = 0; i < count; i++) 
    {
        char* num = va_arg(args, char*);

        enum status_code st = add_two_digits(first_num, num, base, result);

        if (st != OK)
        {
            va_end(args);
            return st;
        }

        char *tmp = first_num;
        first_num = *result;
        free(tmp);
    }

    return OK;
}

int main() 
{
    char *result = 0;
    char* num1 = "-0005A";
    char* num2 = "0005";

    enum status_code sum;
    sum = sum_in_base(16, 2, &result, num1, num2);

    if (sum == OK) 
    {
        printf("Result: %s\n", result);
    } 
    else 
    {
        print_errors(sum);
    }
    
    free(result);

    return 0;
}

