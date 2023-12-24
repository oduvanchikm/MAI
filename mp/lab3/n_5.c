#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct
{
    unsigned int id;
    char name[256];
    char surname[256];
    char group[256];
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

bool is_mark(char mark)
{
    if (mark < '1' || mark > '5')
    {
        return false;
    }

    return true;
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
    printf("4. Input average mark for student\n");
    printf("5. Exit\n");
    printf("Enter:\n");
}

void print_in_file_best_students(FILE* file, Student* students, int count_of_students)
{
    double all_average = 0.0;
    double grade_average = 0.0;
    for (int i = 0; i < count_of_students; i++)
    {
        grade_average = average_grade(&students[i]);
        all_average += grade_average;
    }

    all_average = all_average / count_of_students;
    fprintf(file, "Average all: %f\n", all_average);

    for (int i = 0; i < count_of_students; i++)
    {
        grade_average = average_grade(&students[i]);
        if (grade_average > all_average)
        {
            fprintf(file, "%s %s %f\n", students[i].name, students[i].surname, grade_average);
        }
    }
}

int compare_students_by_group(const void* a, const void* b)
{
    Student* student_1 = (Student*)a;
    Student* student_2 = (Student*)b;

    return (strcmp(student_1->group, student_2->group));
}

int compare_students_by_id(const void* a, const void* b)
{
    Student* student_1 = (Student*)a;
    Student* student_2 = (Student*)b;

    return student_1->id - student_2->id;
}

int compare_students_by_surname(const void* a, const void* b)
{
    Student* student_1 = (Student*)a;
    Student* student_2 = (Student*)b;

    return (strcmp(student_1->surname, student_2->surname));
}

int compare_students_by_name(const void* a, const void* b)
{
    Student* student_1 = (Student*)a;
    Student* student_2 = (Student*)b;

    return (strcmp(student_1->name, student_2->name));
}

int find_student_by_name(Student* students, int count_of_students, char* buffer)
{
    for(int i = 0; i < count_of_students; i++)
    {
        if(strcmp(students[i].name, buffer) == 0)
        {
            return i;
        }
    }

    return -1;
}

int find_student_by_group(Student* students, int count_of_students, char* buffer)
{
    for(int i = 0; i < count_of_students; i++)
    {
        if(strcmp(students[i].group, buffer) == 0)
        {
            return i;
        }
    }

    return -1;
}

int find_student_by_surname(Student* students, int count_of_students, char* buffer)
{
    for(int i = 0; i < count_of_students; i++)
    {
        if(strcmp(students[i].surname, buffer) == 0)
        {
            return i;
        }
    }

    return -1;
}

Student search_by_id(unsigned int id, Student* result)
{
    int i = 0;
    while (result[i].id != -1)
    {
        if (result[i].id == id)
        {
            return result[i];
        }
        i++;
    }
    Student student;
    student.id = -1;
    return student;
}

status_code info_from_file(FILE *filename, Student **result, int *number_of_students)
{
    *number_of_students = 9;

    *result = (Student*)malloc(sizeof(Student) * (*number_of_students + 1));
    if (!(*result))
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    int i = 0;
    while (fscanf(filename, "%d %s %s %s", &((*result)[i].id), ((*result)[i].name), ((*result)[i].surname), ((*result)[i].group)) == 4)
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

       if (!(isdigit((*result)[i].id)) || !(isalpha((*result)[i].name)) || !(isalpha((*result)[i].surname)))
       {
           return INVALID_INPUT;
       }

        for (int j = 0; j < 5; j++)
        {
            if ((fscanf(filename, " %c", &((*result)[i].mark[j]))) != 1 || !is_mark((*result)[i].mark[j]))
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
        *result = (Student*)realloc(*result, (i + 1) * sizeof(Student));
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

bool valid_option(int c)
{
    if (c > 4 && c < 1)
    {
        return false;
    }

    return true;
}

status_code print_student(Student student)
{
    printf("%d ", student.id);
    printf("%s ", student.name);
    printf("%s ", student.surname);
    printf("%s ", student.group);
    printf("%c %c %c %c %c\n", student.mark[0], student.mark[1], student.mark[2], student.mark[3], student.mark[4]);
    return OK;
}

status_code print_students(Student* students, int count_of_students)
{
    int i = 0;
    if (students == NULL || students[i].id == -1 || count_of_students == 0)
    {
        printf("There are no students\n");
    }
    while (i < count_of_students)
    {
        print_student(students[i]);
        i++;
    }
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

    if (strcmp(argv[1], argv[2]) == 0)
    {
        printf("I must enter different files\n");
        return 0;
    }

    Student* students = NULL;
    int count_of_students = 0;

    status_code st_info = info_from_file(input_file, &students, &count_of_students);

    if (st_info != OK)
    {
        print_errors(st_info);
        fclose(input_file);
        fclose(output_file);
        return 0;
    }

    int res_id = 0;
    int res_surname = 0;
    int res_name = 0;
    int res_group = 0;
    int c;
    int flag_search;
    int flag_sort = 0;
    char buffer[256];
    print_menu();
    scanf("%d", &c);

    switch(c)
    {
        case 1:
            printf("\tFind a student\n");
            printf("You can search students by\n1. ID\n2. Name\n3. Surname\n4. Group\n");
            scanf("%d", &flag_search);
            if (!valid_option(flag_search))
            {
                printf("Wrong number of option\nPlease, enter again\n");
            }

            switch(flag_search)
            {
                case 1:
                    printf("Enter ID:\n");
                    int id;
                    if (scanf("%d", &id) != 1)
                    {
                        printf("Error with enter ID\n");
                    }
                    print_student(search_by_id(id, students));
                    break;
                
                case 2:
                    printf("Enter name:\n");
                    scanf("%s", buffer);
                    res_name = find_student_by_name(students, count_of_students, buffer);
                    print_students(students, res_name);
                    break;
                
                case 3:
                    printf("Enter surname:\n");
                    scanf("%s", buffer);
                    res_surname = find_student_by_surname(students, count_of_students, buffer);
                    print_students(students, res_surname);
                    break;
                
                case 4:
                    printf("Enter gruop:\n");
                    scanf("%s", buffer);
                    res_group = find_student_by_group(students, count_of_students, buffer);
                    print_students(students, res_group);
                    break;

                default:
                    printf("Wrong action\n");
                    break;
            }
            break;

        case 2:
            printf("\tSort students\n");
            printf("You can sort students by\n1. ID\n2. Name\n3. Surname\n4. Group\n");
            scanf("%d", &flag_sort);
            switch(flag_sort)
            {
                case 1:
                    qsort(students, count_of_students, sizeof(Student), compare_students_by_id);
                    printf("Sorted by ID\n");
                    print_students(students, count_of_students);
                    break;

                case 2:
                    qsort(students, count_of_students, sizeof(Student), compare_students_by_name);
                    printf("Sorted by name\n");
                    print_students(students, count_of_students);
                    break;

                case 3:
                    qsort(students, count_of_students, sizeof(Student), compare_students_by_surname);
                    printf("Sorted by surname\n");
                    print_students(students, count_of_students);
                    break;

                case 4:
                    qsort(students, count_of_students, sizeof(Student), compare_students_by_group);
                    printf("Sorted by group\n");
                    print_students(students, count_of_students);
                    break;
                
                default:
                    printf("Invalid input\n");
                    break;
            }

            break;

        case 3:
            printf("\tEnter best students\n");
            printf("The program will output to a file the average score for all exams of all students and the best students\n");
            print_in_file_best_students(output_file, students, count_of_students);
            printf("Data is in the output file\n");
            break;

        case 4:
            printf("\tAverage mark for student\n");
            printf("Enter ID:\n");
            int id;
            if (scanf("%d", &id) != 1)
            {
                printf("Error with enter ID\n");
            }
            else
            {
                Student stud = search_by_id(id, students);
                if (stud.id != -1)
                {
                    double middle_mark = average_grade(&stud);
                    fprintf(output_file, "%s %s %s %f\n", stud.name, stud.surname, stud.group, middle_mark);
                    printf("Data is in the output file\n");
                }
                else
                {
                    printf("Student with ID %d not found\n", id);
                }
            }
            break;
            
        default:
            printf("Invalid option\n");
            break;
    }
    return 0;
}


