#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

bool is_integer(const char *str) 
{ 
    int length = strlen(str);
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

int h_function(int num, int* result) 
{

    if (num < 0) 
    {
        num = -num;
    }

    for (int i = 0; i < 100; i += num) 
    {
        if (i % num == 0) 
        {
            result[i] += i;
        }
    }
}

bool p_function(int num) 
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

int s_function(int num, int* array)
{
    int count = 0;
    int last_digit;

    if (num < 0) 
    {
        num = -num;
    }

    if (num < 10 && num >= 0) 
    {
        array[0] = num;
        return 1;
    }


    while (num != 0) 
    {
        last_digit = num % 10;
        array[count] = last_digit;
        count++;
        num /= 10;
    }

    for (int i = count - 1; i <= 0; i--) 
    {
        array[i] += i;
    }
    
    return count;
}

void free_table(long long ***table, int n) 
{
    if (*table) {
        for (int i = 0; i < n; i++) {
            if ((*table)[i]) {
                free((*table)[i]);
                (*table)[i] = NULL;
            }
        }
        free(*table);
        *table = NULL;
    }
}

int fill_table(int num, long long*** table) {
    (*table) = (long long**)malloc(10 * sizeof(long long*));
    if (!(*table)) {
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        (*table)[i] = (long long*)malloc(num * sizeof(long long));
        if (!(*table)[i]) {
            free_table(table, i);
            return 1;
        }
    }

    for (int i = 0; i < 10; i++) {
        long long res = 1;
        for (int j = 0; j < num; j++) {
            res *= (i + 1);
            (*table)[i][j] = res;
        }
    }

    return 0;
}

void a_function(long long num, long long *sum) {
    long long sum_num = 0;
    if (num > 0) {
        for (long int i = 1; i <= num; i++) {
            sum_num += i;
        }
        *sum += sum_num;
    }
}


unsigned long long factorial(unsigned int num, unsigned long long result) {
    for (unsigned int i = 2; i <= num; i++) {
        if (result > ULLONG_MAX / i) {
            return 0;
        }
        result *= i;
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("The number of arguments doesn't fit\n");
    }
    else {
        if (is_integer(argv[1])) {
            long int num = atoi(argv[1]);

            if (strlen(argv[2]) != 2 || argv[2][0] != '-' && argv[2][0] != '/') {
                printf("Invalid flag\n");
                return 0;
            }

            else {

                if (argv[2][1] == 'h') {
                    int result[100] = {0};
                    if (num < INT_MAX) {
                        h_function(num, result);
                    
                        if (num == 0) {
                            printf("0\n");

                        }

                        for (int i = 0; i < 100; i++) {
                            if (result[i] != 0) {
                                printf("%d ", result[i]);
                            }
                        }
                    }

                    else {
                        printf("overflow\n");
                    }

                }

                else if (argv[2][1] == 'p') {
                    
                    if (num < INT_MAX) {
                        if (p_function(num)) {

                            printf("This digit is prime\n");
                        }
                        else {

                            printf("This digit is composite\n");
                        }
                    }
                    else {
                        printf("overflow\n");
                    }

                }

                else if (argv[2][1] == 's') {
                    if (num < INT_MAX) {
                        int array[100] = {0};
                        int count = s_function(num, array);

                        for (int j = count - 1; j >= 0; j--) {
                            printf("%d ", array[j]);
                        }
                    }
                    else {
                        printf("overflow\n");
                    }

                }

                else if (argv[2][1] == 'e') {

                    long long** table = NULL;

                    fill_table(num, &table);

                    if (num > 0 && num <= 10) {
                        for (int i = 0; i < 10; i++) {
                            for (int j = 0; j < num; j++) {
                                printf("%lli ", table[i][j]);
                            }
                            printf("\n");
                        }
                        free_table(&table, num);
                        return 0;
                    }

                    else {
                        printf("overflow\n");
                    }
                    
                }

                else if (argv[2][1] == 'a') {
                    if (num != 0) {
                        if (num < INT_MAX) {
                            long long summ = 0;
                            a_function(num, &summ);
                            if (summ > LLONG_MAX - num) {

                                printf("Error\n");
                                return 0;
                            }
                            else {
                                printf("%ld\n", summ);
                            }
                        }
                        else {
                            printf("overflow\n");
                        }
                        
                    }

                    else {
                        printf("Error\n");
                    }
                    
                }

                else if (argv[2][1] == 'f') {
                    if (num > 0) {
                        if (num < INT_MAX) {
                            unsigned long long result = 1;
                            long long f = factorial(num, result);
                            printf("%lli", f);
                        }
                    
                        else {
                            printf("overflow\n");
                        }
                    }
                    else {
                        printf("error\n");
                    }
                }

                else {
                    printf("Invalid flag\n");
                }
            }
        }
        else {
            printf("it's not an int\n");
        }
        return 0;
    }
    return 0;
}