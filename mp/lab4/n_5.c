#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>

typedef enum
{
    OK,
    ERROR_WITH_MEMORY_ALLOCATION,
    INVALID_INPUT,
    ERROR_WITH_COUNT_OF_ARGUMENTS,
    ERROR_WITH_OPENING_FILE,
    EMPTY,
    NEGATIVE_DIGIT,
    WRONG_COUNT_OF_BRACKETS,
    OVERFLOW,
    STATUS

} status_code;

void print_info(char* filename, char* string, char* postfix, int result)
{
    printf("Filename: %s\n", filename);
    printf("Expression in infix form: %s\n", string);
    printf("Expression in postfix form: %s\n", postfix);
    printf("Result of expression: %d\n", result);
}

void print_errors(int flag)
{
    switch(flag)
    {
        case ERROR_WITH_COUNT_OF_ARGUMENTS:
            printf("Error with count of arguments\n");
            break;
        
        case ERROR_WITH_MEMORY_ALLOCATION:
            printf("Error with memory allocation\n");
            break;
        
        case INVALID_INPUT:
            printf("Invalid input\n");
            break;

        case ERROR_WITH_OPENING_FILE:
            printf("Error with opening file\n");
            break;

        case NEGATIVE_DIGIT:
            printf("It's a negativ digit\n");
            break;

        case WRONG_COUNT_OF_BRACKETS:
            printf("Wrong count of brackets\n");
            break;

        case OVERFLOW:
            printf("It's very big digit\n");
            break;
        
        default:
            break;
    }
}

typedef struct Node 
{
    int data;
    struct Node* next;

} Node;

typedef struct 
{
    Node* top;

} Stack;

void initialize(Stack* stack) 
{
    stack->top = NULL;
}

void push(Stack* stack, int data) 
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node)
    {
        return;
    }

    new_node->data = data;
    new_node->next = stack->top;
    stack->top = new_node;
}

char pop(Stack** stack)
{
    if (*stack == NULL)
    {
        return INVALID_INPUT;
    }

    Node* out = (*stack)->top;
    char value = out->data;
    (*stack)->top = (*stack)->top->next;
    free(out);
    return value;
}


char peek(Stack* stack)
{
    if (stack->top == NULL) 
    {
        return EMPTY;
    }

    return stack->top->data;
}

int is_empty(Stack* stack) 
{
    return stack->top == NULL;
}

bool is_operator(const char c)
{
    return ((c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '^') || (c == '%') || (c == '~'));
}

int get_priority(const char operator)
{
    switch (operator)
    {
//        case '(':
//        case ')':
//            return 1;

        case '+':
        case '-':
            return 1;

        case '*':
        case '/':
        case '%':
        case '~':
            return 2;

        case '^':
            return 3;

        default:
            return 4;
    }
}

int my_pow(int base, int power)
{
    int result = 0;

    if (power == 0)
    {
        return 1;
    }

    else if (power == 1)
    {
        return base;
    }

    else
    {
        if (power % 2 == 0)
        {
            result = my_pow(base, power / 2);
            return result * result;
        }
        else
        {
            return my_pow(base, power - 1) * base;
        }
    }
}

int my_strlen(const char* string)
{
    if (!(*string))
    {
        return 0;
    }
    int count = 0;

    while (*string)
    {
        string++;
        count++;
    }
    return count;
}

status_code infix_to_postfix(const char* infix, char** postfix)
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    initialize(stack);

    int len = my_strlen(infix);
    *postfix = (char*)malloc((len + 1) * sizeof(char));
    if (!(*postfix))
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    int postfix_size = 0;

    for (int i = 0; i < len; i++)
    {
        if (isspace((infix[i])))
        {
            continue;
        }

        else if (infix[i] == '-' && (i == 0 || infix[i - 1] == '('))
        {
            (*postfix)[postfix_size] = '~';
            postfix_size++;
        }

        else if (isdigit((infix[i])))
        {
            while (isdigit(infix[i]))
            {
                (*postfix)[postfix_size] = infix[i];
                postfix_size++;
                i++;
            }
            (*postfix)[postfix_size] = ' ';
            postfix_size++;
            i--;
        }

        else if (infix[i] == '(')
        {
            push(stack, infix[i]);
        }

        else if (infix[i] == ')')
        {
            while (!is_empty(stack) && peek(stack) != '(')
            {
                (*postfix)[postfix_size] = pop(&stack);
                postfix_size++;

                (*postfix)[postfix_size] = ' ';
                postfix_size++;
            }

            if (!is_empty(stack))
            {
                pop(&stack);
            }
            else
            {
                return WRONG_COUNT_OF_BRACKETS;
            }
        }

        else if (is_operator(infix[i]))
        {
            while (!is_empty(stack) && get_priority(peek(stack)) >= get_priority(infix[i]))
            {
                (*postfix)[postfix_size] = pop(&stack);
                postfix_size++;
                (*postfix)[postfix_size] = ' ';
                postfix_size++;
            }
            push(stack, infix[i]);
        }
        else
        {
            return INVALID_INPUT;
        }
    }
    while (!is_empty(stack))
    {
        if (peek(stack) == '(' || peek(stack) == ')')
        {
            return INVALID_INPUT;
        }
        (*postfix)[postfix_size] = pop(&stack);
        postfix_size++;

        (*postfix)[postfix_size] = ' ';
        postfix_size++;
    }
    (*postfix)[postfix_size] = '\0';

    return OK;
}

status_code solve_expression(char* postfix, int* result)
{
    int number = 0;
    int number_1 = 0;
    int number_2 = 0;

    int len = my_strlen(postfix);
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    initialize(stack);

    for (int i = 0; i < len; i++)
    {
        if (isdigit(postfix[i]))
        {
            number = number * 10 + (postfix[i] - '0');
        }
        else if (postfix[i] == ' ' && isdigit(postfix[i - 1]))
        {
            push(stack, number);
            number = 0;
        }
        else if (postfix[i] == '~')
        {
            number = pop(&stack);
            push(stack, -number);
        }
        else if (postfix[i] == ' ')
        {
            continue;
        }
        else
        {
            number_2 = pop(&stack);
            number_1 = pop(&stack);
            if ((number_1 >= INT_MAX && number_2 >= INT_MAX) || (number_1 <= INT_MIN && number_2 <= INT_MIN))
            {
                return OVERFLOW;
            }
            switch(postfix[i])
            {
                case '+':
                    push(stack, number_1 + number_2);
                    break;
                case '-':
                    push(stack, number_1 - number_2);
                    break;
                case '*':
                    push(stack, number_1 * number_2);
                    break;
                case '/':
                    if (number_2 != 0)
                    {
                        push(stack, number_1 / number_2);
                    }
                    else
                    {
                        return NEGATIVE_DIGIT;
                    }
                    break;
                case '%':
                    if (number_2 != 0)
                    {
                        push(stack, number_1 % number_2);
                    }
                    else
                    {
                        return NEGATIVE_DIGIT;
                    }
                    break;
                case '^':
                    push(stack, my_pow(number_1, number_2));
                    break;
                default:
                    return INVALID_INPUT;
            }
        }
    }
    *result = stack->top->data;
    return OK;
}

status_code read_string(FILE* file, char** string)
{
    int index = 0;
    int capacity = 10;
    *string = (char*)malloc(capacity * sizeof(char));
    if (!(*string))
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }
    int symbol = fgetc(file);

    while (symbol != EOF)
    {
        if (index == capacity - 1)
        {
            capacity *= 2;
            char* tmp = realloc(*string, capacity * sizeof(char));
            if (!tmp)
            {
                free(*string);
                return ERROR_WITH_MEMORY_ALLOCATION;
            }
            *string = tmp;
        }
        (*string)[index] = (char)symbol;
        index++;
//        if (symbol == '\n')
//        {
//            (*string)[index] = '\0';
//            (*number_of_string)++;
//            index = 0;
//            return OK;
//        }
//        (*string)[index] = '\0';
        symbol = fgetc(file);
    }
    (*string)[index] = '\0';
    return OK;
}

char* error_file(char* filename)
{
    char* prefix = "error_";
    char* output = NULL;
    output = (char*)malloc(my_strlen(prefix) + my_strlen(filename) + 1);
    if (!output)
    {
        return NULL;
    }
    sprintf(output, "error_%s", filename);
    return output;
}

status_code file_works(char* argv[], int argc)
{
    char* string = NULL;
    char* postfix = NULL;
    int digit;
    int str_count = 0;
    status_code st_read_string;
    status_code st_postfix;
    status_code calculate_result;
    FILE* file = NULL;
    FILE* output_file = NULL;
    char filename[100];
    char* output = NULL;
//    int infix_len = 0;
//    int postfix_len = 0;

    for (int i = 1; i < argc; i++)
    {
        file = fopen(argv[i], "r");
        if (!file)
        {
            return ERROR_WITH_OPENING_FILE;
        }
        int flag = 1;
        while (flag)
        {
            st_read_string = read_string(file, &string);
            if (strlen(string) == 0)
            {
                str_count++;
                continue;
            }

            switch(st_read_string)
            {
                case ERROR_WITH_MEMORY_ALLOCATION:
                    flag = 0;
                    print_errors(flag);
                    break;

                case OK:
                    st_postfix = infix_to_postfix(string, &postfix);
                    switch (st_postfix)
                    {
                        case ERROR_WITH_MEMORY_ALLOCATION:
                            flag = 0;
                            print_errors(st_postfix);
                            break;

                        case WRONG_COUNT_OF_BRACKETS:
                            if (!output_file)
                            {
                                strcpy(filename, argv[i]);
                                output = error_file(filename);
                                output_file = fopen(output, "a");
                                if (!output_file)
                                {
                                    return ERROR_WITH_OPENING_FILE;
                                }
                            }
                            fprintf(output_file,
                                    "Expression: %s\nIn string number: %d\nProblem: wrong bracket balance\n",
                                    string, str_count);
                            break;

                        case INVALID_INPUT:
                            if (!output_file)
                            {
                                strcpy(filename, argv[i]);
                                output = error_file(filename);
                                output_file = fopen(output, "a");
                                if (!output_file)
                                {
                                    return ERROR_WITH_OPENING_FILE;
                                }
                            }
                            fprintf(output_file, "Expression: %s\nIn string number: %d\nProblem: invalid input\n",
                                    string,
                                    str_count);
                            break;

                        case OK:
                            calculate_result = solve_expression(postfix, &digit);
                            switch (calculate_result)
                            {
                                case OVERFLOW:
                                    if (!output_file)
                                    {
                                        strcpy(filename, argv[i]);
                                        output = error_file(filename);
                                        output_file = fopen(output, "a");
                                        if (!output_file)
                                        {
                                            return ERROR_WITH_OPENING_FILE;
                                        }
                                    }
                                    fprintf(output_file, "Expression: %s\nIn string number: %d\nProblem: overflow\n",
                                            string,
                                            str_count);
                                    break;

                                case ERROR_WITH_MEMORY_ALLOCATION:
                                    flag = 0;
                                    free(postfix);
                                    free(string);
                                    print_errors(calculate_result);
                                    break;

                                case NEGATIVE_DIGIT:
                                    if (!output_file)
                                    {
                                        strcpy(filename, argv[i]);
                                        output = error_file(filename);
                                        output_file = fopen(output, "a");
                                        if (!output_file) {
                                            return ERROR_WITH_OPENING_FILE;
                                        }
                                    }
                                    fprintf(output_file,
                                            "Expression: %s\nIn string number: %d\nProblem: negative digit\n",
                                            string, str_count);
                                    break;

                                case INVALID_INPUT:
                                    if (!output_file)
                                    {
                                        strcpy(filename, argv[i]);
                                        output = error_file(filename);
                                        output_file = fopen(output, "a");
                                        if (!output_file) {
                                            return ERROR_WITH_OPENING_FILE;
                                        }
                                    }
                                    fprintf(output_file,
                                            "Expression: %s\nIn string number: %d\nProblem: invalid input\n",
                                            string, str_count);
                                    break;

                                case OK:
                                    //                        infix_len = my_strlen(string);
                                    //                        postfix_len = my_strlen(postfix);
                                    //                        for (int i = 0; i < infix_len; i++)
                                    //                        {
                                    //                            if (string[i] == '~')
                                    //                            {
                                    //                                string[i] = '-';
                                    //                            }
                                    //                        }
                                    //                        for (int j = 0; j < postfix_len; j++)
                                    //                        {
                                    //                            if (postfix[j] == '~')
                                    //                            {
                                    //                                postfix[j] = '-';
                                    //                            }
                                    //                        }
                                    printf("Expression: %s\n", string);
                                    printf("Postfix: %s\n", postfix);
                                    printf("Result: %d\n", digit);
                            }
                    }

            }
            str_count++;
            free(string);
            free(postfix);
        }
        fclose(file);
    }
    fclose(output_file);
    return OK;
}


int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Error with number of arguments\nEnter input files\n");
        return 0;
    }

    status_code st = file_works(argv, argc);
    if (st == OK)
    {
        printf("g\n");
    }
    else
    {
        printf("wrong\n");
    }
    return 0;
}

