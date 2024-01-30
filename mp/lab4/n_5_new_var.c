#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>

typedef enum {
    OK,
    ERROR_WITH_MEMORY_ALLOCATION,
    INVALID_INPUT,
    ERROR_WITH_COUNT_OF_ARGUMENTS,
    ERROR_WITH_OPENING_FILE,
    NEGATIVE_DIGIT,
    WRONG_COUNT_OF_BRACKETS,
    OVERFLOW,

} status_code;

void print_errors(int flag) {
    switch (flag) {
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

typedef struct Node {
    int data;
    struct Node *next;

} Node;

typedef struct {
    Node *top;

} Stack;

void initialize(Stack *stack) {
    stack->top = NULL;
}

void push(Stack *stack, int data) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    if (!new_node) {
        return;
    }

    new_node->data = data;
    new_node->next = stack->top;
    stack->top = new_node;
}

int pop(Stack **stack) {
    if (*stack == NULL) {
        return -1;
    }

    Node *out = (*stack)->top;
    int value = out->data;
    (*stack)->top = (*stack)->top->next;
    free(out);
    return value;
}


int peek(Stack *stack) {
    if (stack->top == NULL) {
        return -1;
    }

    return stack->top->data;
}

int is_empty(Stack *stack) {
    return stack->top == NULL;
}

bool is_operator(const char c) {
    return ((c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '^') || (c == '%') || (c == '~'));
}

int get_priority(const char operator) {
    switch (operator) {
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

int my_pow(int base, int power) {
    int result = 0;

    if (power == 0) {
        return 1;
    } else if (power == 1) {
        return base;
    } else {
        if (power % 2 == 0) {
            result = my_pow(base, power / 2);
            return result * result;
        } else {
            return my_pow(base, power - 1) * base;
        }
    }
}

int my_strlen(const char *string) {
    if (!(*string)) {
        return 0;
    }
    int count = 0;

    while (*string) {
        string++;
        count++;
    }
    return count;
}

status_code infix_to_postfix(const char *infix, char **postfix, int* error)
{
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    if (!stack)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    initialize(stack);

    int len = my_strlen(infix);
    *postfix = (char *) malloc((len + 1) * sizeof(char));
    if (!(*postfix))
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    int postfix_size = 0;
    bool is_last_add_operator = true;
    int binary_minus = 0;

    for (int i = 0; i < len; i++)
    {
        if (isspace((infix[i])))
        {
            continue;
        }
        else if (infix[i] == '-' && is_last_add_operator)
        {
            binary_minus = 1;
            is_last_add_operator = true;
        }
        else if (isdigit((infix[i])))
        {
            while (isdigit(infix[i]))
            {
                (*postfix)[postfix_size] = infix[i];
                postfix_size++;
                i++;
            }

            if (binary_minus == 1) {
                (*postfix)[postfix_size] = '~';
                postfix_size++;
                binary_minus = 0;
            }

            (*postfix)[postfix_size] = ' ';
            postfix_size++;
            i--;
            is_last_add_operator = false;

        }
        else if (infix[i] == '(')
        {
            push(stack, infix[i]);
            is_last_add_operator = true;
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
                *error = WRONG_COUNT_OF_BRACKETS;
                return WRONG_COUNT_OF_BRACKETS;
            }
            is_last_add_operator = false;
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
            is_last_add_operator = true;
        }
        else
        {
            *error = INVALID_INPUT;
            return INVALID_INPUT;
        }
    }
    while (!is_empty(stack)) {
        if (peek(stack) == '(' || peek(stack) == ')')
        {
            *error = INVALID_INPUT;
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

status_code solve_expression(char *postfix, int *result, int* error)
{
    int number = 0;
    int number_1 = 0;
    int number_2 = 0;

    int len = my_strlen(postfix);
    Stack* stack = (Stack*) malloc(sizeof(Stack));
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
        else if ((postfix[i] == ' ' || postfix[i] == '~') && isdigit(postfix[i - 1]))
        {
            push(stack, number);
            number = 0;
            if (postfix[i] == '~')
            {
                number = pop(&stack);
                push(stack, (-1 * number));
                number = 0;
            }
        }
        else if (isspace(postfix[i]))
        {
            continue;
        }
        else
        {
            number_2 = pop(&stack);
            number_1 = pop(&stack);

            if ((number_1 >= INT_MAX && number_2 >= INT_MAX) || (number_1 <= INT_MIN && number_2 <= INT_MIN))
            {
                *error = OVERFLOW;
                return OVERFLOW;
            }

            switch (postfix[i])
            {
                case '+':
                    if (number_1 + number_2 > INT_MAX)
                    {
                        *error = OVERFLOW;
                        return OVERFLOW;
                    }
                    else
                    {
                        push(stack, number_1 + number_2);
                    }
                    break;

                case '-':
                    if (number_1 - number_2 < INT_MIN)
                    {
                        *error = OVERFLOW;
                        return OVERFLOW;
                    }
                    else
                    {
                        push(stack, number_1 - number_2);
                    }
                    break;

                case '*':
                    if ((number_1 > INT_MAX / number_2 || number_1 < INT_MIN / number_2))
                    {
                        *error = OVERFLOW;
                        return OVERFLOW;
                    }
                    else
                    {
                        push(stack, number_1 * number_2);
                    }
                    break;
                case '/':
                    if (number_2 != 0)
                    {
                        if ((number_1 / number_2 > INT_MAX) || (number_1 / number_2 < INT_MIN))
                        {
                            *error = OVERFLOW;
                            return OVERFLOW;
                        }
                        else
                        {
                            push(stack, number_1 / number_2);
                        }
                    }
                    else
                    {
                        *error = NEGATIVE_DIGIT;
                        return NEGATIVE_DIGIT;
                    }
                    break;

                case '%':
                    if (number_2 != 0)
                    {
                        if ((number_1 % number_2 > INT_MAX) || (number_1 % number_2 < INT_MIN))
                        {
                            *error = OVERFLOW;
                            return OVERFLOW;
                        }
                        else
                        {
                            push(stack, number_1 % number_2);
                        }
                    }
                    else
                    {
                        *error = NEGATIVE_DIGIT;
                        return NEGATIVE_DIGIT;
                    }
                    break;

                case '^':
                    if (my_pow(number_1, number_2) > INT_MAX)
                    {
                        *error = OVERFLOW;
                        return OVERFLOW;
                    }
                    else
                    {
                        push(stack, my_pow(number_1, number_2));
                    }

                default:
                    *error = INVALID_INPUT;
                    return INVALID_INPUT;
            }
        }
    }
    *result = stack->top->data;
    return OK;
}

bool valid_characters(const char *string)
{
    int len_string = my_strlen(string);

    for (int i = 0; i < len_string; i++)
    {
        if (string[i] < '0' && string[i] > '9' && string[i] != '(' && string[i] != ')' && !is_operator(string[i]) &&
            string[i] != ' ')
        {
            return false;
        }
    }
    return true;
}

char *error_file(char *filename)
{
    char *prefix = "error_";
    char *output = NULL;
    output = (char *) malloc(my_strlen(prefix) + my_strlen(filename) + 1);
    if (!output)
    {
        return NULL;
    }
    sprintf(output, "error_%s", filename);
    return output;
}

int is_number(char c)
{
    return (c >= '0' && c <= '9');
}

status_code validation(const char* string)
{
    int len_string = my_strlen(string);

    bool is_digit = false;
    bool is_oper = false;
    bool is_brackets = false;

    for (int i = 0; i < len_string; i++)
    {
        if (isspace(string[i]))
        {
            continue;
        }

        if (isdigit(string[i]))
        {
            is_digit = true;
            is_oper = false;
            is_brackets = false;
        }

        else if (is_operator(string[i]))
        {
            if (is_oper)
            {
                return INVALID_INPUT;
            }

            is_digit = false;
            is_oper = true;
        }
        else if (!isspace(string[i]))
        {
            return INVALID_INPUT;
        }
    }

    if (!is_digit)
    {
        return INVALID_INPUT;
    }

    return OK;
}

void print_result(char* string, char*  postfix_expression, int result)
{
    printf("Expression: %s\n", string);
    printf("Postfix: %s\n", postfix_expression);
    printf("Result: %d\n", result);
}

void print_error_in_file(FILE* output_file, int error, int line_of_expression, char* string)
{
    fprintf(output_file, "Expression: %s\n", string);
    fprintf(output_file, "In string number: %d\n", line_of_expression);
    fprintf(output_file, "Problem: ");

    switch (error)
    {
        case INVALID_INPUT:
            fprintf(output_file, "invalid expression\n");
            break;

        case WRONG_COUNT_OF_BRACKETS:
            fprintf(output_file, "wrong count of brackets\n");
            break;

        case NEGATIVE_DIGIT:
            fprintf(output_file, "negative digits\n");
            break;

        case OVERFLOW:
            fprintf(output_file, "overflowed\n");
            break;

    }
    fprintf(output_file, "\n");
}

status_code file_works(FILE *input_file, FILE *output_file)
{
    int symbol = fgetc(input_file);
    int capacity = 10;
    int error;

    char* string = (char*) malloc(capacity * sizeof(char));
    if (!string)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    int flag = 1;
    int index = 0;
    int line_of_expression = 0;

    while (flag)
    {
        char *postfix_expression = NULL;
        index = 0;

        while (symbol != EOF && symbol != '\n')
        {
            if (index == capacity - 1)
            {
                capacity *= 2;
                char *tmp = realloc(string, capacity * sizeof(char));
                if (!tmp)
                {
                    free(string);
                    return ERROR_WITH_MEMORY_ALLOCATION;
                }
                string = tmp;
            }
            string[index] = (char)symbol;
            index++;
            symbol = fgetc(input_file);
        }

        if (symbol == EOF)
        {
            flag = 0;
        }

        string[index] = '\0';

        if (my_strlen(string) != 0)
        {
            if (!valid_characters(string))
            {
                error = INVALID_INPUT;
                print_error_in_file(output_file, error, line_of_expression, string);
                printf("Wrong expression, wrong characters\n");
            }

//            status_code st_validation = validation(string);
//            if (st_validation == INVALID_INPUT)
//            {
//                fprintf(output_file, "Expression: %s\n", string);
//                fprintf(output_file, "In string number: %d\n", line_of_expression);
//                fprintf(output_file, "Problem: wrong characters\n");
//                printf("Wrong expression, wrong characters\n");
//            }

            printf("infix: %s\n", string);

            status_code st_postfix_expression = infix_to_postfix(string, &postfix_expression, &error);
            if (st_postfix_expression == ERROR_WITH_MEMORY_ALLOCATION)
            {
                flag = 0;
                print_errors(st_postfix_expression);
                break;

            }
            else if (st_postfix_expression == WRONG_COUNT_OF_BRACKETS)
            {
                print_error_in_file(output_file, error, line_of_expression, string);
                printf("Wrong expression, wrong count of brackets\n");
            }
            else if (st_postfix_expression == INVALID_INPUT)
            {
                print_error_in_file(output_file, error, line_of_expression, string);
                printf("Wrong expression, invalid input\n");
            }
            else
            {
                int result;
                status_code st_solve_expression = solve_expression(postfix_expression, &result, &error);
                if (st_solve_expression == ERROR_WITH_MEMORY_ALLOCATION)
                {
                    flag = 0;
                    print_errors(st_solve_expression);
                    break;
                }
                else if (st_solve_expression == OVERFLOW)
                {
                    print_error_in_file(output_file, error, line_of_expression, string);
                    printf("Wrong expression, overflow\n");
                }
                else if (st_solve_expression == INVALID_INPUT)
                {
                    print_error_in_file(output_file, error, line_of_expression, string);
                    printf("Wrong expression, invalid input\n");
                }
                else if (st_solve_expression == NEGATIVE_DIGIT)
                {
                    print_error_in_file(output_file, error, line_of_expression, string);
                    printf("Wrong expression, negative digit\n");
                }
                else
                {
                    print_result(string, postfix_expression, result);
                }
            }
        }
        else
        {
//            здесь надо дописать
        }
        line_of_expression++;
        free(postfix_expression);
    }
    free(string);
    return OK;
}

status_code all_functions(int argc, char *argv[])
{
    FILE *input_file = NULL;
    FILE *output_file = NULL;
    char *new_out_file = NULL;
    char filename[100];

    for (int i = 1; i < argc; i++)
    {
        input_file = fopen(argv[i], "r");
        if (!input_file)
        {
            return ERROR_WITH_OPENING_FILE;
        }

        printf("Input file: %s\n", argv[i]);

        strcpy(filename, argv[i]);
        new_out_file = error_file(filename);
        output_file = fopen(new_out_file, "a");
        if (!output_file)
        {
            fclose(input_file);
            return ERROR_WITH_OPENING_FILE;
        }

        status_code st = file_works(input_file, output_file);

        if (st != OK)
        {
            print_errors(st);
        }

        fclose(input_file);
        fclose(output_file);
        free(new_out_file);
    }
    return OK;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Error with number of arguments\nEnter input files\n");
        return 0;
    }

    status_code st = all_functions(argc, argv);
    if (st == OK)
    {
        printf("The program has finished its work\n");
    }
    else
    {
        printf("Something went wrong\n");
    }
    return 0;
}