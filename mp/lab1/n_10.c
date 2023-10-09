#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <stdbool.h>

#define SIZE 33

bool checking_base(int base)
{
    if (base < 2 || base > 36)
    {
        return false;
    }

    return true;
}

void* ten_to_other_base(int base, int number)
{
    int sign = 1;

    if (number < 0)
    {
        number *= -1;
    }

    int r;
    static char buf[SIZE];
    char* ptr = buf + SIZE - 1;
    *ptr = '\0';

    while(number > 0)
    {
        r = number % base;
        *--ptr = (r > 9)? r - 10 + 'A' : r + '0';
        number /= base;
    }

    return ptr;
}

int other_base_to_ten(char* number, int base) 
{
    if (!number)
    {
        return 0;
    }
    int symbol = 1;
    char *ptr = NULL;
    int result = 0;

    if (*number == '-')
    {
        symbol = -1;
        ptr = number + 1;
    }
    else
    {
        ptr = number;
    }
    while (*ptr)
    {
        result = result * base + (isdigit(*ptr) ? *ptr  - '0' : *ptr - 'A' + 10);
        ptr++;
    }
    return result * symbol;
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
                return 0;
            }
            i++;
        }
    }
    else {
        while(digits[i])
        {
            if (digits[i] - '0' >= base) 
            {
                return 0;
            }
            i++;
        }
    }
    return 1;
}

int main()
{
    int base;
    int flag = 0;

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
        flag = 1;
        
        int num = other_base_to_ten(digits, base); 
        int abs_num = abs(num);

        if (abs_num > max_digit)
        {
            max_digit = abs_num;
        }

    }

    char res[256];
    int len = 0;
    int max_elem = max_digit;

    if (flag == 1)
    {
        printf("The maximum element in base 10: %d\n", max_elem);

        printf("Max value in base 9: %s\n", ten_to_other_base(9, max_elem));
        printf("Max value in base 18: %s\n", ten_to_other_base(18, max_elem));
        printf("Max value in base 27: %s\n", ten_to_other_base(27, max_elem));
        printf("Max value in base 36: %s\n", ten_to_other_base(36, max_elem));
    }

    
    
    return 0;
}