#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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
        if (*str >= '0' && *str <= '9') 
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


double factorial(int n) 
{
    double result = 1.0;
    for (int i = 1; i <= n; i++) 
    {
        result *= i;
    }
    return result;
}

double a_function(double x, double eps) 
{
    double sum = 0.0;
    int n = 1;
    double res = 1.0;

    while (fabs(res) > eps) 
    {
        res = (pow(-1, n + 1) * pow(x, n + 1)) / factorial(n);
        sum += res;
        n++;
    }
    return sum;
}

double b_function(double x, double eps) 
{
    double sum = 0.0;
    int n = 0;
    double res = 1.0;

    while (fabs(res) > eps) 
    {
        res = (pow(-1, n) * pow(x, 2 * n)) / (pow(2, n) * factorial(n));
        sum += res;
        n++;
    }
    return sum;
}



double c_function(double x, double eps) 
{
    double sum = 0.0;
    int n = 1;
    double res = 1.0;

    while (fabs(res) > eps) 
    {
        res = pow(x, n) / n;
        sum += res;
        n++;
    }
    return sum;
}

double d_function(double x, double eps)
{
    double sum = 0.0;
    int n = 1;
    double res = 1.0;

    while (fabs(res) > eps) 
    {
        res = pow(-1, n + 1) * pow(n, -n);
        sum += res;
        n++;
    }
    return sum;
}


int main(int argc, char *argv[]) 
{
    if (argc != 3) 
    {
        printf("Error!\n");
        return 1;
    }
    
    if (!check_string(argv[1])) 
    {
        printf("Invalid epsilon\n");
        return 1;
    }
    
    if (!check_string(argv[2])) 
    {
        printf("Invalid x\n");
        return 1;
    }
    
    double eps = atof(argv[1]);
    double x = atof(argv[2]);

    if (eps <= 0) 
    {
        printf("Invalid epsilon\n");
        return 1;
    }   
    
    double result_a = a_function(x, eps);
    printf("Result a function: %lf\n", result_a);

    double result_b = b_function(x, eps);
    printf("Result b function: %lf\n", result_b);

    if (fabs(x) <= 1) 
    {
        double result_c = c_function(x, eps);
        printf("Result c function: %lf\n", result_c);
            
        double result_d = d_function(x, eps);
        printf("Result d function: %lf\n", result_d);
    }

    else 
    {
        printf("invalid x\n");
    }
    

    return 0;
}