#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

bool check_string(char *str) 
{
    if (strlen(str) > 10) {
        return false;
    }
    
    int count = 0;
    
    if (*str == '\0') 
    {
        return false;
    }
    
    if (*str == '-' || *str == '+')
    {
        str++;
        if (*str == '\0') 
        {
            return false;
        }
    }
    
    while (*str) 
    {
        if (isdigit(*str)) 
        {
            str++;
            if (*str == '.') 
            {
                count += 1;
                str++;
                if (*str == '\0')
                {
                    return false;
                }
            }
        }
        else 
        {
            return false;
        }
    }
    
    if (count == 0 || count > 1)
    {
        return false;
    }
    
    return true;
}

double a_function(double x) // 0.822467
{
    return log(1 + x) / x;
}

double b_function(double x) // 0.8556243918921488
{
    return exp(-(pow(x, 2) / 2));
}

double c_function(double x) // 1
{
    if (x >= 1 || x <= 0)
        return -1;
    return log(1 / (1 - x));
}

double d_function(double x) // 0.7834305107121345
{
    return pow(x, x);
}

double right_rectangle(double a, double b, double n, double (*f)(double), double eps)
{
    double h = (b - a) / n;
    double new_sum = 0.1 + eps;
    double old_sum = 0.0;

    while (fabs(new_sum - old_sum) > eps)
    {
        old_sum = new_sum;
        new_sum = 0.0;
        for (int i = 1; i <= n; i++)
        {
            double x = a + i * h;
            new_sum += f(x);
        }
    }

    double result = h * new_sum;
    return result;
}

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        printf("Error\n");
        return 1;
    }
    
    if (!check_string(argv[1])) 
    {
        printf("Invalid epsilon\n");
        return 1;
    }
    
    double eps = atof(argv[1]);

    if (eps <= 0) 
    {
        printf("Invalid epsilon\n");
        return 1;
    }   

    double integral_result_1 = right_rectangle(0, 1, 6, a_function, eps);
    double integral_result_2 = right_rectangle(0, 1, 6, b_function, eps);
    double integral_result_3 = right_rectangle(0, 1, 10, c_function, eps);
    double integral_result_4 = right_rectangle(0, 1, 6, d_function, eps);

    printf("First integral result: %lf\n", integral_result_1);
    printf("Second integral result: %lf\n", integral_result_2);
    printf("Third integral result: %lf\n", integral_result_3);
    printf("Fourth integral result: %lf\n", integral_result_4);

    return 0;
}