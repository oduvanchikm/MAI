#ifndef POLISH_H
#define POLISH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>

bool is_operator(const char c);
int get_priority(const char operator);
int my_pow(int base, int power);
int my_strlen(const char* string);
status_code infix_to_postfix(const char* infix, char** postfix);
status_code solve_expression(char* postfix, int* result);
status_code read_string(FILE* file, char** string);
char* error_file(char* filename);
status_code file_works(char* argv[], int argc);

#endif