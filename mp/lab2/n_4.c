#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


enum status_code
{
    OK,
    ERROR_WITH_MEMORY_ALLOCATION,
    INVALID_VALUE
};

typedef struct
{
    double x, y;

} point;

void print_errors(int flag)
{
    switch (flag)
    {
    case INVALID_VALUE:
        printf("Invalid value\n");
        break;

    case ERROR_WITH_MEMORY_ALLOCATION:
        printf("Error with memory allocation\n");
        break;

    default:
        break;
    }
}

enum status_code value_of_polynomial(double* result, double a, int degree, ...)
{
    va_list args;

    va_start(args, degree);

    if (degree >= 0)
    {
        for (int i = 0; i <= degree; i++)
        {
            *result = *result * a + va_arg(args, double);
        }
    }

    else
    {
        if (a == 0)
        {
            return INVALID_VALUE;
        }

        for (int i = 0; i >= degree; i--)
        {
            *result = *result / a + va_arg(args, double);
        }
    }

    va_end(args);
    return OK;
}

enum status_code is_convex(int n, ...)
{
    if (n < 3)
    {
        return INVALID_VALUE;
    }
    va_list args;
    va_start(args, n);

    point* points = va_arg(args, point*);

    va_end(args);

    int NEG = 0;

    for (int a = 0; a < n; a++)
    {
        int b = (a + 1) % n;

        int c = (a + 2) % n;

        double xA = points[a].x;
        double yA = points[a].y;
        double xB = points[b].x;
        double yB = points[b].y;
        double xC = points[c].x;
        double yC = points[c].y;

        double POS = (xB - xA) * (yC - yB) - (yB - yA) * (xC - xB);

        if (POS > 0)
        {
            POS++;
        }
        else if (POS < 0)
        {
            NEG++;
        }

        if (POS > 0 && NEG > 0)
        {
            return INVALID_VALUE;
        }
    }
    return OK;
}

int main()
{
    double result = 0;

    double a = 1.0;

    int degree = 3;

    enum status_code result_pol = value_of_polynomial(&result, a, degree, 4.0, 5.0, 1.0, 6.0);

    if (result_pol != OK)
    {
        print_errors(result_pol);
    }

    if (result_pol == OK)
    {
        printf("The result of polynom is %f\n", result);
    }

    int n = 3;

    point point[3] = {{1, 2}, {4, 2}, {7, 2}};

    enum status_code polygon_res = is_convex(n, point[0], point[1], point[2]);

    if (polygon_res == INVALID_VALUE)
    {
        printf("No, this polygon is not convex\n");
    }
    else if (polygon_res == OK)
    {
        printf("Yes, this polygon is convex\n");
    }
    
    // free(result);
    return 0;
}


