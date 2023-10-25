#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>


enum status_code
{
    OK,
    INVALID_INPUT,
    ERROR_WITH_MEMORY_ALLOCATION,
    OVERFLOW,
    WRONG_BASE,
    INVALID_VALUE
};

void print_errors(int flag) 
{
    switch(flag) 
    {
        case INVALID_VALUE:
            printf("Invalid value\n");
            break;

        case ERROR_WITH_MEMORY_ALLOCATION:
            printf("Error with memory allocation\n");
            break;

        case OVERFLOW:
            printf("Overflow\n");
            break;

        case WRONG_BASE:
            printf("This base is wrong\n");
            break;

        default:
            break;
    }
}


