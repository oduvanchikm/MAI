#include <stdio.h>
#include <stdlib.h>

typedef struct Employee
{
    int id;
    char name[256]; 
    char surname[256];
    double salary;
} Employee;


enum status_flag
{
    FLAG_A,
    FLAG_D
};

enum status_code
{
    OK,
    ERROR_WITH_MEMORY_ALLOCATION,
    INVALID_VALUE,
    ERROR_WITH_OPENING_FILE
};

// сравнение сотрудников по убыванию: 
// 1) сравнение по зарплате
// 2) сравнение по фамилии
// 3) сравнение по именам
// 4) сравнение по id.

int compare_employees(const void *a, const void *b)
{
    double eps = 0.0001;

    const Employee* w_1 = (const Employee*)a;
    const Employee* w_2 = (const Employee*)b;

    double diff_salary = w_1->salary - w_2->salary;

    if (w_1->salary != w_2->salary)
    {
        return (diff_salary > eps) ? 1 : -1;
    }

    int surname_diff = strcmp(w_1->surname, w_2->surname);

    if (surname_diff != 0)
    {
        return surname_diff;
    }

    int name_diff = strcmp(w_1->name, w_2->name);

    if (name_diff != 0)
    {
        return name_diff;
    }

    return w_1->id - w_2->id;
}

enum status_code read_from_file(const char *file_input, Employee **result, int *count_of_employees)
{
    FILE *file = fopen(file_input, "r");
    
    if (!file)
    {
        return ERROR_WITH_OPENING_FILE;
    }

    *result = (Employee*)malloc(sizeof(Employee) * (*count_of_employees));

    if (!(*result))
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        Employee employee;

        sscanf(buffer, "%u %s %s %f", &employee.id, &employee.name, &employee.surname, &employee.salary);

        *result = realloc(*result, (*count_of_employees + 1) * sizeof(Employee));

        if (!(*result))
        {
            fclose(file);
            ERROR_WITH_MEMORY_ALLOCATION;
        }

        (*result)[*count_of_employees] = employee;
        (*count_of_employees)++;
    }

    fclose(file);
    return OK;
}

enum status_code write_employers_in_file(const char *file_output, Employee *result, int count_of_employees)
{
    FILE *file = fopen(file_output, "w");
    
    if (!file)
    {
        return ERROR_WITH_OPENING_FILE;
    }

    for (int i = 0; i < count_of_employees; i++)
    {
        fprintf(file, "%u %s %s %f\n", result[i].id, result[i].name, result[i].surname, result[i].salary);
    }

    fclose(file);
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Invalid number of arguments.\n");
        printf("Enter a input file, flag -a|/a or -d|/d and output file.\n");
        return 1;
    }

    FILE* input_file = fopen(argv[1], "r");
    FILE* output_file = fopen(argv[3], "w");

    if (!input_file || !output_file)
    {
        printf("Error with opening file.\n");
        return 1;
    }

    if ((argv[2][0] != '/' || argv[2][0] != '-') && strlen(argv[2]) != 2)
    {
        printf("Invalid arguments.\n");
        printf("Enter '/' or '-' for flag or enter only 2 elements\n");
        return 1; 
    }

    if (argv[2][1] != 'a' || argv[2][1] != 'd')
    {
        printf("Invalid arguments.\n");
        printf("You enter a wrong flag\n");
        return 1;
    }

    Employee *employees = NULL;
    int count_of_employees;

    qsort(employees, count_of_employees, sizeof(Employee), compare_employees);

    switch (argv[2][1])
    {
        case 'a':

            break;

        case 'd':
            break;
    }


}