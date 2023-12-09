#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct 
{
    unsigned int ID;
    // char name[256];
    // char surname[256];
    // char group[256];
    char *name;
    char *surname;
    char *group;
    unsigned char *mark;
} Student;

typedef enum
{
    OK,
    ERROR_WITH_MEMORY_ALLOCATION,
    ERROR_WITH_OPENING_FILE,
    INVALID_INPUT
} status_code;

void print_errors(char flag)
{
    switch(flag)
    {
        case ERROR_WITH_MEMORY_ALLOCATION:
            printf("Error with memory allocation\n");
            break;
        
        case ERROR_WITH_OPENING_FILE:
            printf("File can't open\n");
            break;
        
        case INVALID_INPUT:
            printf("Invalid input\n");
            break;
         
        default:
            break;
    }
}

double average_grade(Student *student)
{
    double result = 0.0;

    for (int i = 0; i < 5; i++)
    {
        int mark = student->mark[i] - '0';
        result += mark;
    }

    return result / 5;
}

void print_menu()
{
    printf("\tMENU\n");
    printf("Please choose an option:\n");
    printf("1. Find a student\n");
    printf("2. Sort students\n");
    printf("3. Input best students\n");
    printf("4. Exit\n");
    printf("Enter:\n");
}

// status_code info_from_file(FILE *filename, Student **result, int *number_of_students)
// {
//     fscanf(filename, "%d", number_of_students);
//     // *number_of_students = 9;

//     *result = (Student*)malloc((*number_of_students) * sizeof(Student));

//     if (!(*result))
//     {
//         return ERROR_WITH_MEMORY_ALLOCATION;
//     }
//     int i = 0;


//     while ((fscanf(filename, "%u %s %s %s", &((*result)[i].ID), ((*result)[i].name), ((*result)[i].surname), ((*result)[i].group))) != EOF)
//     {
//         (*result)[i].mark = (unsigned char*)malloc(sizeof(unsigned char) * 5);

//         if (!(*result)[i].mark)
//         {
//             for (int j = 0; j < i; j++)
//             {
//                 free((*result)[j].mark);
//             }
//             free(*result);
//             return ERROR_WITH_MEMORY_ALLOCATION;
//         }

//         int num_of_marks_read = 0;

//         for (int j = 0; j < 5; j++)
//         {
//             if (fscanf(filename, "%c", &((*result)[i].mark[j])) != 1)
//             {
//                 free((*result)[i].mark);
//                 for (int k = 0; k < i; k++)
//                 {
//                     free((*result)[k].mark);
//                 }
//                 free(*result);
//                 // printf("err\n");
//                 return INVALID_INPUT;
//             }

//             if (!isdigit((*result)[i].mark[j]))
//             {
//                 free((*result)[i].mark);
//                 for (int k = 0; k < i; k++)
//                 {
//                     free((*result)[k].mark);
//                 }
//                 free(*result);
//                 printf("err\n");
//                 return INVALID_INPUT;
//             }
//             num_of_marks_read++;
//         }
//         for (int j = num_of_marks_read; j < 5; j++)
//         {
//             (*result)[i].mark[j] = '2';
//         }
//         i++;
//     }
//     return OK;
// }

status_code info_from_file(FILE *filename, Student **result, int *number_of_students)
{
    *result = (Student*)malloc(sizeof(Student));
    if (!(*result)) {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    int i = 0;
    while (fscanf(filename, "%d %s %s %s", &((*result)[i].ID), ((*result)[i].name), ((*result)[i].surname), ((*result)[i].group)) == 4)
    {
        (*result)[i].mark = (unsigned char*)malloc(sizeof(unsigned char) * 5);
        if (!(*result)[i].mark) 
        {
            for (int j = 0; j <= i; j++) 
            {
                free((*result)[j].mark);
            }
            free(*result);
            return ERROR_WITH_MEMORY_ALLOCATION;
        }

        for (int j = 0; j < 5; j++)
        {
            if (fscanf(filename, " %c", &((*result)[i].mark[j])) != 1 || !isdigit((*result)[i].mark[j]))
            {
                for (int k = 0; k <= i; k++) 
                {
                    free((*result)[k].mark);
                }
                free(*result);
                return INVALID_INPUT;
            }
        }
        i++;
        *result = (Student*)realloc(*result, (i+1) * sizeof(Student));
        if (!(*result)) 
        {
            for (int j = 0; j < i; j++) 
            {
                free((*result)[j].mark);
            }
            free(*result);
            return ERROR_WITH_MEMORY_ALLOCATION;
        }
    }

    *number_of_students = i;
    return OK;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Invalid number of arguments\nPlease enter an input file and output file\n");
        return 0;
    }

    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w");

    if (!input_file || !output_file)
    {
        printf("Error with opening file\n");
        fclose(input_file);
        fclose(output_file);
        return 0;
    }
    Student *result;
    int count_of_student;

    status_code st_info = info_from_file(input_file, &result, &count_of_student);

    if (st_info != OK)
    {
        print_errors(st_info);
    }

    else
    {
        for (int i = 0; i < count_of_student; i++)
        {
            fprintf(output_file, "Id: %u\nName: %s\nSurname: %s\nGroup: %s\nMarks: ", result[i].ID, result[i].name, result[i].surname, result[i].group);
            for (int j = 0; j < 5; j++)
            {
                fprintf(output_file, "%c ", result[i].mark[j]);
            }
            fprintf(output_file, "\n");
        }
    }

    fclose(input_file);
    fclose(output_file);
    return 0;
}


