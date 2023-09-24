#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

bool is_integer(const char *str) { 
    if (*str == '\0') {
        return false;
    }
    if (*str == '-' || *str == '+') {
        str++;
    }
    if (*str == '\0') {
        return false;
    }
    if (*str == '0' && *(str + 1) != '\0') {
        return false;
    }
    while (*str != '\0') {
        if (*str < '0' || *str > '9') {
            return false;
        }
        str++;
    }
    return true;
}

int h_function(int num, int* result) {

    if (num < 0) {
        num = -num;
    }

    for (int i = 0; i < 100; i++) {
        if (i % num == 0) {
            result[i] += i;
        }
    }
}

bool p_function(int num) {
    if (num > 1) {
        for (int i = 2; i < sqrt(num); i++)
            if (num % i == 0)
                return false;
        return true;
    }
    else
        return false;
}

int s_function(int num, int* array) {
    int count = 0;
    int last_digit;

    while (num != 0) {
        last_digit = num % 10;
        array[count] = last_digit;
        count++;
        num /= 10;
    }

    for (int i = count - 1; i <= 0; i--) {
        array[i] += i;
    }
    
    return count;
}

int e_function(long int num, int* array) {

    long long res;
    for (int i = 1; i <= 10; i++) {
        res = pow(num, i);
        array[i] += res;

    }
}

void a_function(long int num, long int *summ) {
    long int sum_num = 0;
    if (num < 1) {
        printf("Number out of range\n");
    }
    for (long int i = 1; i <= num; i++) {
        sum_num += i;
    }
    *summ += sum_num;
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
            if (argc < 3) {
                printf("Few arguments\n");
                return 0;
            }
            else {

                if (argv[2][1] == 'h') {
                    int result[100] = {0};
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

                else if (argv[2][1] == 'p') {
                    
                    if (p_function(num)) {
                        printf("This digit is prime\n");
                    }
                    else {
                        printf("This digit is composite\n");
                    }
                }

                else if (argv[2][1] == 's') {
                    int array[100] = {0};
                    int count = s_function(num, array);

                    for (int j = count - 1; j >= 0; j--) {
                        printf("%d ", array[j]);
                    }

                }

                else if (argv[2][1] == 'e') {
                    int array[10] = {0};
    
                    if (num < 0 || num > 10) {
                        printf("Number out of range\n");
                    }

                    else {
                        e_function(num, array);
                        for (int i = 0; i <= 10; i++) {
                            printf("%d ", array[i]);
                        }
                    }
                    printf("\n");
                }

                else if (argv[2][1] == 'a') {
                    long int summ = 0;
                    a_function(num, &summ);
                    printf("%ld\n", summ);
                }

                // else if (argv[2][1] == 'f') {
                //     f_function(num);
                // }

                else {
                    printf("Invalid flag\n");
                }
            }
        }
        else {
            printf("it's not an integer\n");
        }
        return 0;
    }
    return 0;
}

