#include "main.h"

void print_errors(int flag)
{
    switch(flag)
    {
        case ERROR_WITH_COUNT_OF_ARGUMENTS:
            printf("Error with count of arguments\n");
            break;

        case ERROR_WITH_MEMORY_ALLOCATION:
            printf("Error with memory allocation\n");
            break;

        case INVALID_INPUT:
            printf("Invalid input\n");
            break;

        case ERROR_WITH_OPENING_FILE:
            printf("Error with opening file\n");
            break;

        case NEGATIVE_DIGIT:
            printf("It's a negativ digit\n");
            break;

        case WRONG_COUNT_OF_BRACKETS:
            printf("Wrong count of brackets\n");
            break;

        case OVERFLOW:
            printf("It's very big digit\n");
            break;

        default:
            break;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Error with number of arguments\nEnter input files\n");
        return 0;
    }

    status_code st = file_works(argv, argc);
    if (st == OK)
    {
        printf("g\n");
    }
    else
    {
        printf("wrong\n");
    }
    return 0;
}