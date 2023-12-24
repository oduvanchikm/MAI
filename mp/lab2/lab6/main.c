#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include "n_6.h"

void print_errors(int flag)
{
    switch(flag)
    {
        case ERROR_WITH_MEMORY_ALLOCATION:
            printf("Error with memory allocation\n");
            break;

        case INVALID_ARGUMENT:
            printf("This is wrong\n");
            break;

        default:
            break;
    }
}

int main()
{
    char *buffer = "L 10010011  \n 77777 23A";
    int number_ro, number_cv, number_CV;
    int base_1 = 8;
    int base_2 = 16;

    unsigned int number_zr;

    oversscanf(buffer, "rggbhajheoqerufurequfgeu%Ro %Zr %Cv %CV", &number_ro, &number_zr, &number_cv, base_1, &number_CV, base_2);
    printf("Roman: %d, zeckendorf: %u, in base 10(low): %d, in base 10(high): %d\n", number_ro, number_zr, number_cv, number_CV);
    return 0;
}