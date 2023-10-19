#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

enum status_code
{
    ok,
    invalid_value
};

enum status_code power(double base, int expon, double *result) 
{
    enum status_code st; 
    if (expon == 0)
    {
        *result = 1.0;
        return ok;
    }

    else if (expon == 1)
    {
        *result = base;
        return ok;
    }

    else if (expon > 0)
    {
        st = power(base * base, expon / 2, result);
        if (st == invalid_value)
        {
            return invalid_value;
        }

        if (expon & 1)
        {
            *result *= base;
        }
    }
    else
    {
        st = power(base, -expon, result);
        if (st == invalid_value)
        {
            return invalid_value;
        }

        *result = 1 / *result;

    }

    return ok;
}

enum status_code geometric_mean_value(double *result, int count, ...)
{
    double multi = 1.0;
    va_list ptr;
    va_start(ptr, count);

    for (int i = 0; i < count; i++)
    {
        multi *= va_arg(ptr, double);
    }

    va_end(ptr);

    if (!(count & 1) && multi < 0)
    {
        return invalid_value;
    }

    *result = pow(fabs(multi), 1.0 / count);

    if (multi < 0)
    {
        *result *= -1.0;
    }

    return ok;
}

int main(int argc, char* argv[])
{
    double result1 = 0; 
    double result2 = 0;
    enum status_code status1, status2;

    status1 = power(2.0, -5, &result1);
    status2 = geometric_mean_value(&result2, 3, -2.0, 2.0, 2.0);

    if (status1 == ok)
    {
        printf("Power: %f\n", result1);
    }
    else
    {
        printf("error\n");
    }

    if (status2 == ok)
    {
        printf("Geometric mean value: %f\n", result2);
    }
    else
    {
        printf("error\n");
    }

    return 0;
}



































