#include <stdio.h>
#include <math.h>

enum status_code
{
    ok
};

double function(double x)
{
    return x * x - 4 * x + 6;
}

enum status_code dichotomy_method(double lower_bound, double upper_bound, double eps, double (*f)(double), double *result)
{
    double middle = 0.0;

    do 
    {
        middle = (upper_bound + lower_bound) / 2;

        if (fabs(f(middle)) < eps)
        {
            *result = middle;

        }

        else if (f(middle) * f(lower_bound) < 0)
        {
            upper_bound = middle;
            *result = middle;
        }

        else
        {
            lower_bound = middle;
            *result = middle;
        }
    } while (fabs(upper_bound - lower_bound) >= eps);

    return ok;
}

int main()
{
    double r = 0.0;
    double lower_bound;
    double upper_bound;
    double eps;

    printf("Enter the lower bound: \n");
    scanf("%lf", &lower_bound);
    printf("Enter the upper bound: \n");
    scanf("%lf", &upper_bound);
    printf("Enter eps: \n");
    scanf("%lf", &eps);

    enum status_code result = dichotomy_method(lower_bound, upper_bound, eps, function, &r);

    if (result == ok)
    {
        printf("Solution of the equation is: %f\n", r);
    }

    else
    {
        printf("Not a solution\n");
    }

    return 0;
}