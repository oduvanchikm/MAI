#ifndef n_6_h
#define n_6_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>

typedef enum
{
    OK,
    ERROR,
    INVALID_ARGUMENT,
    NEGATIVE_NUMBER,
    ERROR_WITH_MEMORY_ALLOCATION

} status_code;

void overfscanf(FILE* file, const char* format, ...);
void oversscanf(char* buffer, const char* format, ...);
status_code from_roman_to_int(const char* str, int* result);
void print_errors(int flag);
status_code zeckendorf(const char* string, unsigned int* result);
status_code flag_cv(int *result, char *number, int base, int flag);

#endif