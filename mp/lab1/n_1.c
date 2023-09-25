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

    for (int i = 0; i < 100; i += num) {
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

    if (num < 10) {
        array[0] = num;
        return 1;
    }

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

int e_function(long int num, long long* array) {

    long long res;
    for (int i = 1; i <= 10; i++) {
        res = pow(num, i);
        array[i] += res;

    }
}

enum summ_numbers_status_code {
    snsc_ok,
    snsc_overflow,
    snsc_invalid_parametrs,
};

enum summ_numbers_status_code summ_of_numbers(unsigned int num, unsigned long *result) {
    if (num == 0 || result == NULL) {
        return snsc_invalid_parametrs;
    }
    unsigned long sum = 0;
    for (unsigned int i = 1; i <= num; i++) {
        if (sum + i < sum) {
            return snsc_overflow;
        }
        sum += i;
    }
    *result = sum;
    return snsc_ok;
}

enum factorial_status_codes {
    fsc_ok,
    fsc_overflow,
    fsc_invalid_parameter
};

enum factorial_status_codes factorial(unsigned int num, unsigned long *result) {
    if (num > 20) {
        return fsc_invalid_parameter;
    }

    if (num == 0 || num == 1) {
        *result = 1;
        return fsc_ok;
    }

    unsigned long temp_result;
    enum factorial_status_codes recursive_status_code = factorial(num - 1, &temp_result);

    if (recursive_status_code == fsc_ok) {
        if (ULONG_MAX / num < temp_result) {
            return fsc_overflow;
        }
        *result = num * temp_result;
    }

    return recursive_status_code;
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
                    long long array[10] = {0};
    
                    if (num < 0 || num > 10) {
                        printf("Number out of range\n");
                    }

                    else {
                        e_function(num, array);
                        for (int i = 0; i <= 10; i++) {
                            printf("%d ", array[i]);
                        }
                    }
                }

                else if (argv[2][1] == 'a') {
                    unsigned int num;
                    unsigned long result;
                    enum summ_numbers_status_code status = summ_of_numbers(num, &result);
                    if (status == snsc_ok) {
                        printf("Sum of numbers from 1 to %u is %lu\n", num, result);
                    } else if (status == snsc_overflow) {
                        printf("Overflow\n");
                    } else {
                        printf("Invalid parameters\n");
                    }
                }

                else if (argv[2][1] == 'f') {
                    long long value;
                    unsigned long factorial_result;
                    switch (factorial(value, &factorial_result)) {
                        case fsc_ok:
                            printf("%u! = %lu\n", value, factorial_result);
                            break;
                        case fsc_overflow:
                            printf("Overflow");
                            break;
                        case fsc_invalid_parameter:
                            printf("Invalid parameter");
                            break;
                    }
                }

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