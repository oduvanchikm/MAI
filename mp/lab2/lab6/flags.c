#include "n_6.h"

void from_int_to_other(int base, int num, char *res, int *len)
{
    int length = 0;
    int r = 0;
    int i = 0;
    while (num > 0)
    {
        r = num % base;
        res[i] = (r > 9) ? r - 10 + 'A' : r + '0';
        i++;
        length++;
        num /= base;
    }
    *len = length;
    res[i] = '\0';
}

status_code from_roman_to_int(const char* str, int* result) 
{
    int length = (int) strlen(str);

    if (!length)
    {
        return  INVALID_ARGUMENT;
    }

    *result = 0;
    int position = length - 1;
    for (int i = length - 1; i >= 0; --i)
    {
        if (str[i] != 'I' && str[i] != 'V' && str[i] != 'X' && str[i] != 'L' && str[i] != 'C' && str[i] != 'D' && str[i] != 'M')
        {
            position = i;
        }
    }


    for (int i = position; i >= 0; --i)
    {
        char curr = str[i];
        switch (curr)
        {
            case 'I':
                if (str[i + 1] == 'X' || str[i + 1] == 'V')
                {
                    (*result)--;
                }
                else
                {
                    (*result)++;
                }
                break;

            case 'V':
                (*result) += 5;
                break;

            case 'X':
                if (str[i+1] == 'L' || str[i+1] == 'C')
                {
                    (*result) -= 10;
                }
                else
                {
                    (*result) += 10;
                }
                break;

            case 'L':
                (*result) += 50;
                break;

            case 'C':
                if (str[i + 1] == 'D' || str[i+1] == 'M')
                {
                    (*result) -= 100;
                }
                else
                {
                    (*result) += 100;
                }
                break;

            case 'M':
                (*result) += 1000;

            default:
                break;
        }
    }

    return OK;
}

status_code zeckendorf(const char* string, unsigned int* result)
{
    int len = (int)strlen(string);
    if (!len)
    {
        return INVALID_ARGUMENT;
    }

    unsigned number_1 = 0;
    unsigned number_2 = 1;
    unsigned current = 0;

    *result = 0;
    for (int i = 0; i < len - 1; i++)
    {
        char c = string[i];
        if (c == '1')
        {
            (*result) += current;
        }

        number_1 = number_2;
        number_2 = current;
        current = number_1 + number_2;
    }
    return OK;
}

status_code flag_cv(int *result, char *number, int base, int flag) 
{
    if (base < 2 || base > 36) 
    {
        base = 10;
    }

    if (strcmp(number, "0") == 0) 
    {
        *result = 0;
        return OK;
    }

    int length = strlen(number);
    int power = 1;
    *result = 0;

    for (int i = length - 1; i >= 0; i--) 
    {
        int digit;
        if (isdigit(number[i])) 
        {
            digit = number[i] - '0';
        } 
        else 
        {
            if (flag == 0) 
            {
                if (isalpha(number[i])) 
                {
                    digit = tolower(number[i]) - 'a' + 10;
                } 
                else 
                {
                    return INVALID_ARGUMENT;
                }
            } 
            else if (flag == 1)
            {
                digit = number[i] - 'a' + 10;
            }
        }

        if (digit >= base) 
        {
            return INVALID_ARGUMENT;
        }

        *result += (digit * power);
        power *= base;
    }

    return OK;
}
