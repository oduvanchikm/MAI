#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include "lab.h"


void print_errors(int flag)
{
    switch (flag)
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
    FILE* file = fopen("t1.txt", "w");
    if (!file)
    {
        printf("Error with opening file\n");
        return 0;
    }
    int x;

    overfprintf(file, "Roman: %Ro \n", 56);
    overfprintf(file, "Zeckendorf: %Zr \n", 56);
    overfprintf(file, "gooo %%%d %n %.001f\n", 65, &x, 0.4874587);
    overfprintf(file, "System low: %Cv\n", 4375687, 16);
    overfprintf(file, "System high: %CV\n", 455439, 7);
    overfprintf(file, "System 10 low: %to\n", "aa", 32);
    overfprintf(file, "System 10 high: %TO\n", "123A", 16);
    overfprintf(file, "Bytes signed int: %mi\n", 45);
    overfprintf(file, "Bytes signed unsighted int: %mu\n", 485);
    overfprintf(file, "Bytes signed double: %md\n", 45.546);
    overfprintf(file, "Bytes signed float: %mf\n", 45.3463);
    overfprintf(file, "%n\n", &x);

    char buffer[256];

    // oversprintf(buffer, "Roman: %Ro", 56);
    oversprintf(buffer, "Zeckendorf: %Zr\n", 100);
    // oversprintf(buffer, "System low: %Cv\n", 4375687, 16);
    // oversprintf(buffer, "System high: %CV\n", 455439, 7);
    // oversprintf(buffer, "System 10 low: %to\n", "aa", 32); 
    // oversprintf(buffer, "System 10 high: %TO\n", "123A", 16);
    // oversprintf(buffer, "Bytes signed int: %mi\n", 45);
    // oversprintf(buffer, "Bytes signed unsighted int: %mu\n", 485);
    // oversprintf(buffer, "Bytes signed double: %md\n", 45.546);
    // oversprintf(buffer, "Bytes signed float: %mf\n", 45.3463);
    // oversprintf(buffer, "%n\n", &x);

    char mas[150];
    oversprintf(mas, "I want%%%d", 52);
    printf("%s\n", mas);

    printf("%s\n", buffer);

    // char mas[150];
    // oversprintf(mas, "%Ro", 1004);
    // printf("%s\n", mas);

    fclose(file);
    return 0;
}