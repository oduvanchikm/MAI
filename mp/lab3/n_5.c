#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct
{
    unsigned int ID;
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

status_code print_student(Student student)
{
    printf("%u ", student.ID);
    printf("%s ", student.name);
    printf("%s ", student.surname);
    printf("%s ", student.group);
    printf("%c %c %c %c %c\n", student.mark[0], student.mark[1], student.mark[2], student.mark[3], student.mark[4]);
    return OK;
}

status_code print_students(Student* students, int count_of_students)
{
    int i = 0;
    if (students == NULL || students[i].ID == -1 || count_of_students == 0)
    {
        printf("Студентов нет\n");
//        return OK;
    }
    while (i < count_of_students)
    {
        print_student(students[i]);
        i++;
    }
    return OK;
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

bool is_mark(char mark)
{
    if (mark < '1' || mark > '5')
    {
        return false;
    }

    return true;
}

int compare_by_id(const void* a, const void* b)
{
    unsigned id_1 = ((Student*)a)->ID;
    unsigned id_2 = ((Student*)b)->ID;
    if (id_1 == id_2)
    {
        return 0;
    }
    return id_1 < id_2 ? -1 : 1;
}

int compare_by_surname(const void* a, const void* b)
{
    char* surname_1 = ((Student*)a)->surname;
    char* surname_2 = ((Student*)b)->surname;
    return strcmp(surname_1, surname_2);
}

int compare_by_name(const void* a, const void* b)
{
    char* name_1 = ((Student*)a)->name;
    char* name_2 = ((Student*)b)->name;
    return strcmp(name_1, name_2);
}

int compare_by_group(const void* a, const void* b)
{
    char* group_1 = ((Student*)a)->group;
    char* group_2 = ((Student*)b)->group;
    return strcmp(group_1, group_2);
}

Student search_by_id(unsigned int id, Student* result)
{
    int i = 0;
    while (result[i].ID != -1)
    {
        if (result[i].ID == id)
        {
            return result[i];
        }
        i++;
    }
    Student student;
    student.ID = -1;
    return student;
}

//Student* search_by_name(Student* students, int *amount_students, const char* name)
//{
//    for (int i = 0; i < amount_students; i++)
//    {
//        if (strcmp(students[i].name, name) == 0)
//        {
//            return &students[i];
//        }
//    }
//    return NULL;
//}

status_code search_by_surname(Student* students, int amount_students, const char* surname, Student **result)
{
    for (int i = 0; i < amount_students; i++)
    {
        if (strcmp(students[i].surname, surname) == 0)
        {
            *result = &students[i];
            return OK;
        }
    }
    return INVALID_INPUT;
}

status_code search_by_group(Student* students, int count, char* group, Student** result)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].group, group) == 0)
        {
            *result = &students[i];
            return OK;
        }
    }
    *result = NULL;
    return INVALID_INPUT;
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

//        if (!(isdigit((*result)[i].ID)) || !(isalpha((*result)[i].name)) || !(isalpha((*result)[i].surname)))
//        {
//            return INVALID_INPUT;
//        }

        for (int j = 0; j < 5; j++)
        {
            if (fscanf(filename, " %c", &((*result)[i].mark[j])) != 1 || !is_mark((*result)[i].mark[j]))
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

    Student *result;
    int count_of_student;

    status_code st_info = info_from_file(input_file, &result, &count_of_student);

    if (st_info != OK)
    {
        print_errors(st_info);
        fclose(input_file);
        fclose(output_file);
        return 0;
    }

    int c;
    print_menu();
    if (scanf("%d", &c) != 1)
    {
        printf("Wrong number of option\nPlease, enter again\n");
    }
    int flag_sort;
    int flag_search;
    Student *students;
    Student* st = NULL;
    Student *stud;

    while (c > 0 && c <= 4)
    {
        switch(c)
        {
            case 1:
                printf("\tFind a student\n");
                printf("You can search students by\n1. ID\n2. Name\n3. Surname\n4. Group\n");
                if (scanf("%d", &flag_search) != 1)
                {
                    printf("Wrong number of search\nPlease, enter again\n");
                }
                switch (flag_search)
                {
                    case 1:
                        printf("Enter ID:\n");
                        int id;
                        if (scanf("%d", &id) != 1 || id < 1 || id > 5)
                        {
                            printf("Error with enter ID\n");
                        }
                        print_student(search_by_id(id, result));
                        break;

//                    case 2:
//                        printf("Enter name:\n");
//                        char name[50];
//                        scanf("%s", name);
//                        Student* search = search_by_name(stud, count_of_student, name);
//                        print_students(search, count_of_student);
//
//                        break;
//                    case 3:
//                        printf("Enter surname:\n");
//                        char surname[50];
//                        scanf("%s", surname);
//
//                        if (!isalpha(surname[0]))
//                        {
//                            printf("Error with enter name\n");
//                        }
//                        else
//                        {
//                            status_code result_sur = search_by_surname(students, count_of_student, name, &st);
//                            if (result_sur == OK && st != NULL)
//                            {
//                                print_student(*st);
//                            }
//                            else
//                            {
//                                printf("Student not found\n");
//                            }
//                        }
//                        break;
//
//                    case 4:
//                        printf("Enter group:\n");
//                        char group[50];
//                        scanf("%s", group);
//                        status_code result_gr = search_by_group(students, count_of_student, name, &st);
//                        if (result_gr == OK && st != NULL)
//                        {
//                            print_student(*st);
//                        }
//                        else
//                        {
//                            printf("Student not found\n");
//                        }
//                        break;
//                    default:
//                        break;
                }
                break;

            case 2:
                printf("\tSort students\n");
                printf("You can sort students by\n1. ID\n2. Name\n3. Surname\n4. Group\n");
                scanf("%d", &flag_sort);
                if (flag_sort < 1 || flag_sort > 5)
                {
                    printf("Wrong number of sort\nPlease, enter again\n");
                }
                if (flag_sort == 1)
                {
                    qsort(students, count_of_student, sizeof(Student), compare_by_id);
                }

                else if (flag_sort == 2)
                {
                    qsort(students, count_of_student, sizeof(Student), compare_by_name);
                }

                else if (flag_sort == 3)
                {
                    qsort(students, count_of_student, sizeof(Student), compare_by_surname);
                }

                else if (flag_sort == 4)
                {
                    qsort(students, count_of_student, sizeof(Student), compare_by_group);
                }

                for (int i = 0; i < count_of_student; i++){
                    printf("\tId: %d, name: %s, surname: %s, group: %s, grades: %c %c %c %c %c\n",
                           students[i].ID, students[i].name, students[i].surname, students[i].group,
                           students[i].mark[0], students[i].mark[1], students[i].mark[2],
                           students[i].mark[3], students[i].mark[4]);
                }

            case 3:
                printf("erjr\n");
                break;

            case 4:
                printf("fgjrhg\n");
                break;

            default:
                break;
        }
    }
    fclose(input_file);
    fclose(output_file);
    return 0;
}


