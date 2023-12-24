#ifndef lab_h
#define lab_h

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

typedef enum
{
    OK,
    INVALID_ARGUMENT,
    ERROR_WITH_MEMORY_ALLOCATION

} status_code;

status_code roman_digits_flag(int num, char **result);
int fibonacci(int n);
status_code zecedorf_representation(unsigned int num, char **result);
int my_strlen(int number, int base);
status_code decemal_to_other_base_l(char **result, int number, int base);
status_code decemal_to_other_base_h(char **result, int number, int base);
bool is_low(char string);
bool is_high(char string);
int other_base_to_ten_h(char *number, int base);
int other_base_to_ten_l(char *number, int base);
status_code print_dump_memory(char **result, void *num, size_t size);
void overfprintf(FILE *file, const char *format, ...);
void oversprintf(char *buffer, const char *format, ...);
void print_errors(int flag);

#endif