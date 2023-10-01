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

double a_function(double x, double eps) // по тейлору y = exp(x)
{
    double y = exp(x);
    double sum = 0;
    while (fabs(sum) > eps) 
    {
        x--;
        y = exp(x);
    }
    sum += y;
    return sum;
}

double b_function(double x, double eps) // по тейлору y = cos(x)
{
    double y = cos(x);
    double sum = 0;
    while (fabs(sum) > eps) 
    {
        x--;
        y = cos(x);
    }
    sum += y;
    return sum;
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

double c_function(double x, double eps) 
{
    double sum = 0.0;
    int n = 0;
    double res = 1.0;

    while (fabs(res) > eps) 
    {
        res = (pow(3, 3 * n) * pow(factorial(n), 3) * pow(x, 2 * n)) / factorial(3 * n);
        sum += res;
        n++;
    }
    return sum;
}

unsigned long long doubleFactorial(unsigned long long n) {
    if (n <= 1) 
    {
        return 1;
    }
    
    return n * doubleFactorial(n - 2);
}

double d_function(double x, double eps)
{
    double sum = 0.0, term;
    int n = 1;
    
    do 
    {
        term = pow(-1, n) * doubleFactorial(2 * n - 1) * pow(x, 2 * n) / doubleFactorial(2 * n);
        sum += term;
        n++;
    } 
    while (fabs(term) > eps);
    
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

    if (abs(x) < 1) 
    {
        double result_c = c_function(x, eps);
        printf("Result c function: %lf\n", result_c);
            
        double result_d = d_function(x, eps);
        printf("Result d function: %lf\n", result_d);
    }
    else 
    {
        printf("Invalid x\n");
        return 1;
    } 
    return 0;
}