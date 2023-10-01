#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


bool check_string(char *str) 
{ 
    if (strlen(str) > 6) 
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

bool is_integer(const char *str) 
{ 
    if (strlen(str) > 10) 
    {
        return false;
    }
    if (*str == '\0') 
    {
        return false;
    }

    if (*str == '-' || *str == '+') 
    {
        str++;
    }

    if (*str == '0' && *(str + 1) != '\0') 
    {
        return false;
    }

    while (*str) 
    {
        if (*str < '0' || *str > '9') 
        {
            return false;
        }
        
        str++;
    }
    return true;
}

bool checking_for_the_multiplicity(int n, int m) 
{
    if (m == 0) {
        return false;
    }
    if (n % m == 0) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}

void heap_permutation(double new_array[][3], double array[], int n, int *count)
{
    if (n == 1) 
    {
        for (int i = 0; i < 3; i++) 
        {
            new_array[*count][i] = array[i];
        }
        (*count)++;
        return;
    }
    for (int i = 0; i < n; i++)
    {
        heap_permutation(new_array, array, n - 1, count);
        if (n % 2 == 0) 
        {
            double temp = array[i];
            array[i] = array[n - 1];
            array[n - 1] = temp;
        }       
        else 
        {
            double temp = array[0];
            array[0] = array[n - 1];
            array[n - 1] = temp;
        }
    }
}

double findMax(double a, double b, double c) {
    double max = a;

    if (b > max) {
        max = b;
    }
    
    if (c > max) {
        max = c;
    }

    return max;
}

double findMin(double a, double b, double c) {
    double min = a;

    if (b < min) {
        min = b;
    }

    if (c < min) {
        min = c;
    }

    return min;
}


bool right_triangle(double a, double b, double c, double eps)
{
    double max_elem = findMax(a, b, c);
    double min_elem = findMin(a, b, c);
    double middle_elem = (a + b + c) - max_elem - min_elem;

    if (fabs(min_elem * min_elem + middle_elem * middle_elem - max_elem * max_elem) < eps) 
    {
        return true;  
    } else 
    {
        return false;
    }
}


int main(int argc, char *argv[]) 
{

    if (strlen(argv[1]) != 2 || argv[1][0] != '-' && argv[1][0] != '/') 
    {
        printf("Invalid flag\n");
        return 0;
    }
    else 
    {

        if (argv[1][1] == 'q') 
        {
            if (argc != 6) 
            {
                printf("Invalid parameter\n");
            }
            else 
            {
                if ((check_string(argv[2])) && (check_string(argv[3])) && (check_string(argv[4])) && (check_string(argv[5]))) 
                {
                    int count = 0;
                    double new_array[100][3] = {0.0};
                    double array[3];
                    double num_1 = atof(argv[3]);
                    double num_2 = atof(argv[4]);
                    double num_3 = atof(argv[5]);
                    double eps = atof(argv[2]);

                    array[0] = num_1;
                    array[1] = num_2;
                    array[2] = num_3;

                    heap_permutation(new_array, array, 3, &count);

                    for (int i = 0; i < count; i++)
                    {
                        double discriminant = pow(new_array[i][1], 2) - 4 * new_array[i][0] * new_array[i][2];
                        if (discriminant > eps) 
                        {
                            double x_1 = (-new_array[i][1] + sqrt(discriminant)) / (2 * new_array[i][0]);
                            double x_2 = (-new_array[i][1] - sqrt(discriminant)) / (2 * new_array[i][0]);
                            printf("For permutation %lf %lf %lf:\n", new_array[i][0], new_array[i][1], new_array[i][2]);
                            printf("Result: %lf, %lf\n", x_1, x_2);
                            printf("\n");
                        }
                        else if (fabs(discriminant) < eps) 
                        {
                            double x = -new_array[i][1] / (2 * new_array[i][0]);
                            printf("For permutation %lf %lf %lf:\n", new_array[i][0], new_array[i][1], new_array[i][2]);
                            printf("Result: %lf\n", x);
                            printf("\n");
                        } 
                        else 
                        {
                            printf("For permutation %lf %lf %lf:\n", new_array[i][0], new_array[i][1], new_array[i][2]);
                            printf("The solution is a complex number\n");
                            printf("\n");
                        }
                    }
                                }

                                else 
                                {
                                    printf("error\n");
                                }
                            }
                        }


        else if (argv[1][1] == 'm') 
        {
            if (argc != 4) 
            {
                printf("Invalid parameter\n");
            }
            else 
            {
                if (is_integer(argv[2]) && is_integer(argv[3])) 
                {
                    
                    int digit_1 = atoi(argv[2]);
                    int digit_2 = atoi(argv[3]);


                    if (checking_for_the_multiplicity(digit_1, digit_2)) 
                    {
                        printf("The %d is multiple %d\n", digit_1, digit_2);
                    }
                    else 
                    {
                        printf("The %d is not multiple %d\n", digit_1, digit_2);
                    }  
                }
                else 
                {
                    printf("error\n");
                }
            }
        }

        else if (argv[1][1] == 't') 
        {
            if (argc != 6) 
            {
                printf("Invalid parameter\n");
            }
            else 
            {
                if ((check_string(argv[2])) && (check_string(argv[3])) && (check_string(argv[4])) && (check_string(argv[5]))) 
                {
                    double eps = atof(argv[2]);
                    double num_2 = atof(argv[3]);
                    double num_3 = atof(argv[4]);
                    double num_4 = atof(argv[5]);

                    if (right_triangle(num_2, num_3, num_4, eps)) 
                    {
                        printf("It is a right triangle\n");
                    }

                    else 
                    {
                        printf("It is not a right triangle\n");
                    }
                }
                else 
                {
                    printf("errord\n");
                }
            }  
        }
        else 
        {
            printf("Iinvalid flag\n");
        }
    }
}