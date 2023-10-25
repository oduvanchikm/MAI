#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>


enum status_code
{
    OK,
    OVERFLOW,
    ERROR_WITH_MEMORY_ALLOCATION,
    INVALID_VALUE
};

void print_errors(int flag) {
    switch (flag)
    {
    case ERROR_WITH_MEMORY_ALLOCATION:
        printf("error with allocation memory\n");
        break;

    case OVERFLOW:
        printf("Overflow\n");
        break;

    case INVALID_VALUE:
        printf("Invalid value\n");
        break;
    }
}

double factorial(int n)
{
    double fact = 1;
    for(int i = 1; i <= n; i++)
    {
        fact *= i;
    }
    return fact;
}

enum status_code decomposition_of_polynomial(double eps, double a, int degree, double** result, ...)
{
    va_list arg;

    va_start(arg, result);

    double* array_for_coefficient = (double*)malloc((degree + 1) * sizeof(double));

    if (!array_for_coefficient)
    {
        free(array_for_coefficient);

        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    *result = (double*)malloc((degree + 1) * sizeof(double));

    if (!*result)
    {
        free(result);
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    for (int i = 0; i <= degree; i++) 
    {
        (*result)[i] = 0.0;
    }

    int power = 1;

    for (int i = 0; i <= degree; i++)
    {
        double c = va_arg(arg, double);
        array_for_coefficient[i] = power * c;
        power *= a;
    }

    va_end(arg);


    (*result)[0] = array_for_coefficient[0];

    for (int i = 1; i <= degree; i++)
    {
        double prev_result = (*result)[i];
        (*result)[i] = array_for_coefficient[i] / factorial(i) - a * (*result)[i - 1];
        if (fabs((*result)[i] - prev_result) < eps) 
        {
            free(array_for_coefficient);
            return INVALID_VALUE;
        }
    }

    free(array_for_coefficient);
    return OK;
}

int main()
{
    double* result;
    int degree = 3;
    int coef = decomposition_of_polynomial(0.00001, 2.0, degree, &result, 1.0, 3.0, -5.0, 2.0);
    if (coef != OK) 
    {
        print_errors(coef);
    }
    else
    {
        for(int i = 0; i <= 3; i++) 
        {
            printf("g%d: %f \n", i, result[i]);
        }
        printf("\n");
    }

    free(result);
    return 0;
}