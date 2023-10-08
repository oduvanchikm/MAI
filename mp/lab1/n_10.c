#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

#define SIZE 33


bool checking_base(int base)
{
    if (base < 2 || base > 36)
    {
        return false;
    }

    return true;
}

void ten_to_other_base(int base, int num, char* res, int* len)
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
        num/=base;
    }

    *len = length;
    res[i] = '\0';
}

int other_base_to_ten(int digit, int base) 
{
    char str[100];
    snprintf(str, sizeof str, "%d", digit);
    int res = 0;
    int symbol = 1;
    char *ptr = str;

    if (str == NULL || *str == '\0') 
    {
        return 0;
    }

    if (*str == '-')
    {
        symbol = -1;
        ptr = str + 1;
    }

    while (*ptr && base > 0)
    {
        int num;
        if (isdigit(*ptr))
        {
            num = *ptr - '0';
        }
        else if (isalpha(*ptr))
        {
            num = (*ptr - 'A') + 10;
        }
        else
        {
            break;
        }
        res = res * base + num;
        ptr++;
    }

    return res * symbol;
}

int check_base_integers(char *digits, int base)
{
    int i = 0;
    if (!digits)
        return 0;
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
                return -1;
            }
            i++;
        }
    }
    else {
        while(digits[i])
        {
            if (digits[i] - '0' >= base) 
            {
                return -1;
            }
            i++;
        }
    }
    return 1;
}

int main()
{
    int base;

    printf("Enter the base of the number system: ");
    scanf("%d", &base);

    if (!checking_base(base))
    {
        printf("Error, invalid base\n");
        return 1;
    }
    char digits[100];
    int max_digit = INT_MIN;

    while (1)
    {
        printf("Enter digit:\n");
        scanf("%s", digits);

        if (strcmp(digits, "stop") == 0 || strcmp(digits, "Stop") == 0)
        {
            break;
        }

        if (!check_base_integers(digits, base))
        {
            printf("Invalid integer for base %d\n", base);
            return 1;
        }
        
        int num = other_base_to_ten(atoi(digits), base); 

        if (num > max_digit)
        {
            max_digit = num;
        }

    }

    char res[256];
    int len = 0;

    printf("The maximum element in base = %d: %d\n", base, max_digit);
    int max_elem = max_digit;

    printf("The maximum element in base 10: %d\n", max_elem);

    printf("Max value in base = 9: ");
    ten_to_other_base(9, max_elem, res, &len); 


    printf("Max value in base = 18: ");
    ten_to_other_base(18, max_elem, res, &len); 


    printf("Max value in base = 27: ");
    ten_to_other_base(27, max_elem, res, &len); 


    printf("Max value in base = 36: ");
    ten_to_other_base(36, max_elem, res, &len);


    return 0;
}