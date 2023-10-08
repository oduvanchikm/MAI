#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>
#define M_PI 3.14159265358979323846

// checking that digit is a float

bool check_string(char *str) 
{
    if (strlen(str) > 10) 
    {
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

// factorial

long long factorial(long long n) 
{
    long long result = 1;
    if (n < 0)
    {
        return -1;
    }

    if (n == 0 || n == 1)
    {
        return 1;
    }
    for (int i = 2; i <= n; i++) 
    {
        if (i > LLONG_MAX / n) 
        {
            return -3;
        }
        result *= i;
    }
    return result;
}

// checking for the prime

bool is_prime(int num)
{
    if (num > 1) 
    {
        for (int i = 2; i < sqrt(num); i++)
            if (num % i == 0)
                return false;
        return true;
    }
    else
        return false;
}

// limits 

double e_limits(double eps)
{
    double new_sum = 1.0 + eps;
    double old_sum = 0.0;
    int n = 0;

    while (fabs(new_sum - old_sum) > eps)
    {
        n++;
        old_sum = new_sum;
        new_sum = pow(1.0 + 1.0 / n, n);

    }
    return new_sum;
}

double pi_limits(double eps)
{
    long long n = 1;
    double new_sum = 1.0 + eps;
    double old_sum = 0.0;
    while (fabs(new_sum - old_sum) > eps)
    {
        old_sum = new_sum;
        new_sum = (pow(pow(2, n) * factorial(n), 4)) / (n * pow(factorial(2 * n), 2));
        n++;
    }
    return new_sum;
}

double ln_limits(double eps)
{
    double new_sum = 1.0 + eps;
    double old_sum = 0.0;
    long long n = 1;

    while (fabs(new_sum - old_sum) > eps)
    {
        old_sum = new_sum;
        new_sum = n * (pow(2, 1.0 / n) - 1);
        n++;

    }
    return new_sum;
}

double sqrt2_limits(double eps)
{
    long long n = 1;
    double new_sum = 0;
    double old_sum = -0.5;

    while (fabs(new_sum - old_sum) > eps)
    {
        old_sum = new_sum;
        new_sum = old_sum - (pow(old_sum, 2) / 2) + 1;
        n++;

    }
    return new_sum;
}

// C function 

double combination(int m, int k)
{
    if (k == 0 || k == m || m == 0) 
        return 1;
    return factorial(m) / (factorial(k) * factorial(m - k));
}

double gamma_limits(double eps)
{
    long long m = 2;
    long long k = 1;
    double new_sum = 1.0 + eps;
    double old_sum = 0;

    while (fabs(new_sum - old_sum) > eps)
    {
        old_sum = new_sum;

        for (int i = 2; i <= m; ++i) 
        {
            double c = combination(m, i);
            new_sum += c * (pow(-1, k) / k) * log(factorial(k));
            k++;
        }
        m++;
    }
    return new_sum;
}


// rows

double e_row(double eps)
{
    double new_res = 1.0 + eps;
    double old_res = 0.0;
    int n = 1;
    double fact = 1;

    while (fabs(new_res - old_res) > eps)
    {
        old_res = new_res;
        fact *= n;
        new_res += 1.0 / fact;
        n++;
    }
    return new_res;
}

double pi_row(double eps)
{
    double cur = 1;
    double sum = 0;
    double n = 1;

    while (fabs(cur) >= eps)
    {
        cur = pow(-1, n - 1) / (2 * n - 1);
        sum += cur;
        n++;
    }
    return 4 * sum;
}

double ln_row(double eps)
{
    double cur = 1;
    double sum = 0;
    double n = 1;

    while (fabs(cur) >= eps)
    {
        cur = pow(-1, n - 1) / n;
        sum += cur;
        n++;
    }
    return sum;
}

double sqrt2_row(double eps)
{
    double res_1 = 1;
    double res_2 = pow(2.0, 0.25);  // подставляем 2
    double res_3 = 1;

    while (fabs(res_3 - res_1) >= eps)
    {
        res_1 = res_3;
        res_3 *= res_2;
        res_2 = pow(res_2, 0.5);
    }
    return res_3;
}

double gamma_row(double eps)
{
    double sum = 0.0;
    for (int k = 2; k <= INT_MAX; k++)
    {
        double term = 1.0 / floor(pow(k, 2)) - 1.0 / k;
        sum += term;
        if (fabs(term) < eps)
            break;
    }
    return -pow(M_PI, 2) / 6 + sum;
}

// equation

double e_equation(double eps)
{
    return exp(1.0);
}

double pi_equation(double eps)
{
    return acos(-1.0); 
}

double ln_equation(double eps)
{
    return log(2.0);
}

double sqrt2_equation(double eps)
{
    return sqrt(2.0);
}


double gamma(double t)
{
    int p = 2;
    double mult = 1;

    while (p <= t)
    {
        if (is_prime(p))
        {
            mult *= (1.0 - 1.0 / p);
        }
        p++;
    }
    return mult;
}

double gamma_equation(double eps)
{
    double x = 1;
    double t = 0;
    double an = log(t) * gamma(t);
    double an_1 = log(t + 1) * gamma(t + 1);

    while (fabs(an_1 - an) > eps)
    {
        t++;
        an = an_1;
        an_1 = log(t + 1) * gamma(t + 1);
    }

    return exp(x * (-1)) - an;

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

    printf("The result limit e = %lf\n", e_limits(eps));
    printf("The result row e = %lf\n", e_row(eps));
    printf("The result equation e = %lf\n", e_equation(eps));
    printf("\n");

    printf("The result limit pi = %f\n", pi_limits(eps));
    printf("The result row pi = %lf\n", pi_row(eps));
    printf("The result equation pi = %lf\n", pi_equation(eps));
    printf("\n");

    printf("The result limit ln2 = %lf\n", ln_limits(eps));
    printf("The result row ln2 = %lf\n", ln_row(eps));
    printf("The result equation ln2 = %lf\n", ln_equation(eps));
    printf("\n");

    printf("The result limit sqrt2 = %lf\n", sqrt2_limits(eps));
    printf("The result row sqrt2 = %lf\n", sqrt2_row(eps));
    printf("The result equation sqrt2 = %lf\n", sqrt2_equation(eps));
    printf("\n");

    printf("The result limit gamma = %lf\n", gamma_limits(eps));
    printf("The result row gamma = %lf\n", gamma_row(eps));
    printf("The result equation gamma = %lf\n", gamma_equation(eps));
    
    return 0;
}