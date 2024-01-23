#include <stdio.h>
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
    overfprintf(file, "Roman: %Ro Zek: %Zr %TO %CV \n %d %c", 56, 100, "123AA", 16, 123, 16, 555, 'c');
    char buffer[256];
    oversprintf(buffer, "Roman: %Ro Zek: %Zr %TO %CV \n%d %c", 56, 100, "123AA", 16, 123, 16, 555, 'c');
    printf("%s\n", buffer);
    fclose(file);
    return 0;
}