#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

typedef enum
{
    OK,
    ERROR_WITH_MEMORY_ALLOCATION,
    INVALID_INPUT,
    ERROR_WITH_COUNT_OF_ARGUMENTS,
    ERROR_WITH_OPENING_FILE,
    NEGATIVE_DIGIT,
    WRONG_COUNT_OF_BRACKETS,
    OVERFLOW

} status_code;

void print_errors(int flag)
{
    switch (flag)
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
    char data;
    struct Node* left;
    struct Node* right;
} Node;

//-----------------------------------------------------------------------------------------------------
// stack for char
//-----------------------------------------------------------------------------------------------------

typedef struct Stack_node_char
{
    char data;
    struct Stack_node_char* next;

} Stack_node_char;

typedef struct Stack
{
    Stack_node_char* top;

} Stack;

void initialize(Stack* stack)
{
    stack->top = NULL;
}

void push(Stack *stack, char data)
{
    Stack_node_char *new_node = (Stack_node_char*)malloc(sizeof(Stack_node_char));
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
        return -1;
    }

    Stack_node_char *out = (*stack)->top;
    char value = out->data;
    (*stack)->top = (*stack)->top->next;
    free(out);
    return value;
}


char peek(Stack *stack)
{
    if (stack->top == NULL)
    {
        return -1;
    }

    return stack->top->data;
}

int is_empty(Stack *stack)
{
    return stack->top == NULL;
}

//-----------------------------------------------------------------------------------------------------
// stack for tree
//-----------------------------------------------------------------------------------------------------

typedef struct Stack_node_tree
{
    Node* data;
    struct Stack_node_tree* next;

} Stack_node_tree;

typedef struct Stack_tree
{
    Stack_node_tree* top;

} Stack_tree;

void initialize_tree(Stack_tree* stack)
{
    stack->top = NULL;
}

void push_tree(Stack_tree *stack, Node* data)
{
    Stack_node_tree *new_node = (Stack_node_tree*)malloc(sizeof(Stack_node_tree));
    if (!new_node)
    {
        return;
    }

    new_node->data = data;
    new_node->next = stack->top;
    stack->top = new_node;
}

Node* pop_tree(Stack_tree** stack)
{
    if (!(*stack))
    {
        return NULL;
    }

    Stack_node_tree *out = (*stack)->top;
    Node* value = out->data;
    (*stack)->top = (*stack)->top->next;
    free(out);
    return value;
}

int is_empty_tree(Stack_tree* stack)
{
    return stack->top == NULL;
}

int my_strlen(const char *string)
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

bool check_brackets(const char* string)
{
    int value = 0;
    int len = my_strlen(string);

    for (int i = 0; i < len; i++)
    {
        if (string[i] == '(')
        {
            value++;
        }
        else if (string[i] == ')')
        {
            value--;
        }
    }

    if (value != 0)
    {
        return false;
    }

    return true;
}

Node* create_node(char data)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node)
    {
        return NULL;
    }

    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

int is_operator(char c)
{
    return ((c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '^') || (c == '&') ||
            (c == '|') || (c == '<') || (c == '=') || (c == '!') || (c == '#'));
}

// для упрощения: sin - i, sh - s, cos - o, ctg - c, ch - h, ln - n, log2 - l, lg - g, tg - t, exp - e

int is_standart_elem_functions(char c)
{
    return ((c == 'i') || (c == 's') || (c == 'o') || (c == 'c') || (c == 'h') || (c == 'n') ||
            (c == 'l') || (c == 'g') || (c == 't') || (c == 'e'));
}

status_code build_expression_tree(const char* postfix, int* error, Node** tree_result)
{
    Node* node_operand = NULL;
    Node* node_operator = NULL;
    Stack_tree* stack = (Stack_tree*)malloc(sizeof(Stack_tree));
    if (!stack)
    {
        *error = ERROR_WITH_MEMORY_ALLOCATION;
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    initialize_tree(stack);

    int len = my_strlen(postfix);

    for (int i = 0; i < len; i++)
    {
        if (isdigit(postfix[i]))
        {
            node_operand = create_node(postfix[i]);
            push_tree(stack, node_operand);
        }

        else if (is_operator(postfix[i]) || is_standart_elem_functions(postfix[i]))
        {
            if (is_empty_tree(stack))
            {
                free(stack);
                *error = INVALID_INPUT;
                return INVALID_INPUT;
            }

            node_operator = create_node(postfix[i]);
            if (is_standart_elem_functions(postfix[i]))
            {
                if (is_empty_tree(stack))
                {
                    free(stack);
                    *error = INVALID_INPUT;
                    return INVALID_INPUT;
                }

                node_operator->left = pop_tree(&stack);
            }
            else
            {
                if (postfix[i] == '~')
                {
                    node_operator->left = pop_tree(&stack);
                }
                else
                {
                    if (is_empty_tree(stack))
                    {
                        free(stack);
                        *error = INVALID_INPUT;
                        return INVALID_INPUT;
                    }

                    node_operator->right = pop_tree(&stack);
                    node_operator->left = pop_tree(&stack);
                }
            }

            push_tree(stack, node_operator);
        }

        else if (isspace(postfix[i]))
        {
            continue;
        }

        else
        {
            free(stack);
            *error = INVALID_INPUT;
            return INVALID_INPUT;
        }
    }

    *tree_result = pop_tree(&stack);
    free(stack);

    return OK;
}

void print_tree(Node* root, int level)
{
    if (root == NULL)
    {
        return;
    }

    print_tree(root->right, level + 1);
    for (int i = 0; i < level; i++)
    {
        printf("    ");
    }
    printf("%c\n", root->data);
    print_tree(root->left, level + 1);
}

void free_tree(Node *root)
{
    if(!root)
    {
        return;
    }

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int get_priority(const char operator)
{
    switch (operator)
    {
        case '!':
        case '#':
        case '&':
            return 1;

        case '|':
        case '<':
        case '=':
            return 2;

        case '+':
        case '-':
            return 3;

        case '*':
        case '/':
        case '%':
        case '~':
            return 4;

        case '^':
            return 5;

        case 'i':
        case 's':
        case 'o':
        case 'c':
        case 'h':
        case 'n':
        case 'l':
        case 'g':
        case 't':
        case 'e':
            return 6;

        default:
            return 7;
    }
}

// sin - i, sh - s, cos - o, ctg - c, ch - h, ln - n, log - l, lg - g, tg - t, exp - e

status_code infix_to_postfix(const char *infix, char **postfix, int* error)
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack)
    {
        *error = ERROR_WITH_MEMORY_ALLOCATION;
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    initialize(stack);

    int len = my_strlen(infix);
    *postfix = (char *) malloc((len * 2 + 1) * sizeof(char));
    if (!(*postfix))
    {
        free(stack);
        *error = ERROR_WITH_MEMORY_ALLOCATION;
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

            if (binary_minus == 1)
            {
                (*postfix)[postfix_size] = '~';
                postfix_size++;
                binary_minus = 0;
            }

            (*postfix)[postfix_size] = ' ';
            postfix_size++;
            i--;
            is_last_add_operator = false;

        }

        else if (infix[i] == 's')
        {
            if (infix[i + 1] == 'i' && infix[i + 2] == 'n')
            {
                push(stack, 'i');
                i += 2;
            }

            else if (infix[i + 1] == 'h')
            {
                push(stack, 'h');
                i++;
            }
        }

        else if (infix[i] == 'c')
        {
            if (infix[i + 1] == 'o' && infix[i + 2] == 's')
            {
                push(stack, 'o');
                i += 2;
            }

            else if (infix[i + 1] == 't' && infix[i + 2] == 'g')
            {
                push(stack, 'c');
                i += 2;
            }

            else if (infix[i + 1] == 'h')
            {
                push(stack, 'h');
                i++;
            }
        }

        else if (infix[i] == 'l')
        {
            if (infix[i + 1] == 'n')
            {
                push(stack, 'n');
                i++;
            }

            else if (infix[i + 1] == 'o' && infix[i + 2] == 'g')
            {
                push(stack, 'l');
                i += 2;
            }

            else if (infix[i + 1] == 'g')
            {
                push(stack, 'g');
                i++;
            }
        }

        else if (infix[i] == 't' && infix[i + 1] == 'g')
        {
            push(stack, 't');
            i++;
        }

        else if (infix[i] == 'e' && infix[i + 1] == 'x' && infix[i + 2] == 'p')
        {
            push(stack, 'e');
            i += 2;
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

            if (!is_empty(stack) && peek(stack) == '(')
            {
                pop(&stack);
            }
            is_last_add_operator = false;
        }

        else if (infix[i] == '<' && infix[i + 1] == '>')
        {
            push(stack, '<');
            i++;
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
    while (!is_empty(stack))
    {
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
    free(stack);
    return OK;
}

double my_pow(double base, int power)
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

double solve_expression(Node* root, int* error)
{
    if (!root)
    {
        return INVALID_INPUT;
    }

    if (isdigit(root->data))
    {
        return root->data - '0';
    }

    double left_node = solve_expression(root->left, error);
    double right_node = solve_expression(root->right, error);

    switch (root->data)
    {
        case '!':
            return !(int)left_node & (int)right_node;

        case '&':
            return (int)left_node & (int)right_node;

        case '|':
            return (int)left_node | (int)right_node;

        case '<':
            return (int)left_node ^ (int)right_node;

        case '=':
            return (int)left_node == (int)right_node;

        case '+':
            if (left_node + right_node > INT_MAX)
            {
                *error = OVERFLOW;
                return OVERFLOW;
            }
            else
            {
                return left_node + right_node;
            }

        case '-':
            if (left_node - right_node < INT_MIN)
            {
                *error = OVERFLOW;
                return OVERFLOW;
            }
            else
            {
                return left_node - right_node;
            }

        case '*':
            if (left_node == 0 || right_node == 0)
            {
                return 0;
            }

            else if (left_node > INT_MAX / right_node || right_node > INT_MAX / left_node)
            {
                *error = OVERFLOW;
                return OVERFLOW;
            }

            else
            {
                return left_node * right_node;
            }

        case '/':
            if (right_node == 0)
            {
                *error = INVALID_INPUT;
                return INVALID_INPUT;
            }
            else
            {
                if (left_node / right_node > INT_MAX || left_node / right_node < INT_MIN)
                {
                    *error = OVERFLOW;
                    return OVERFLOW;
                }
                else
                {
                    return left_node / right_node;
                }
            }

        case '%':
            if (right_node == 0)
            {
                *error = INVALID_INPUT;
                return INVALID_INPUT;
            }
            else
            {
                if ((int)left_node % (int)right_node > INT_MAX || (int)left_node % (int)right_node < INT_MIN)
                {
                    *error = OVERFLOW;
                    return OVERFLOW;
                }
                else
                {
                    return (int)left_node % (int)right_node;
                }
            }

        case '~':
            if (left_node == 0)
            {
                return 0;
            }
            else
            {
                return !left_node;
            }

        case 'i':
            return sin(left_node);

        case 's':
            return sinh(left_node);

        case 'o':
            return cos(left_node);

        case 'c':
            if (sin(left_node) == 0)
            {
                *error = INVALID_INPUT;
                return INVALID_INPUT;
            }
            else
            {
                return cos(left_node) / sin(left_node);
            }

        case 'h':
            return cosh(left_node);

        case 'n':
            return log(left_node);

        case 'l':
            return log2(left_node);

        case 'g':
            return log10(left_node);

        case 't':
            if (cos(left_node) == 0)
            {
                *error = INVALID_INPUT;
                return INVALID_INPUT;
            }
            else
            {
                return sin(left_node) / cos(left_node);
            }

        case 'e':
            return exp(left_node);

        default:
            *error = INVALID_INPUT;
            return INVALID_INPUT;
    }
}

void print_result(char* string, char*  postfix_expression, double result)
{
    printf("Expression: %s\n", string);
    printf("Postfix: %s\n", postfix_expression);
    printf("Result: %f\n", result);
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

//status_code validate_infix_expression(char* string, int* error)
//{
//
//}

status_code file_works(FILE *input_file, FILE *output_file)
{
    Node* tree_result;
    int symbol = fgetc(input_file);
    int capacity = 10;
    int error;

    char* string = (char*)malloc(capacity * sizeof(char));
    if (!string)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    int flag = 1;
    int index = 0;
    int line_of_expression = 0;
    int length = 0;

    while (flag && !feof(input_file))
    {
        char *postfix_expression = NULL;
        index = 0;

        while (symbol != EOF)
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
            if(symbol == '\n')
            {
                break;
            }
        }

        if (symbol == EOF)
        {
            flag = 0;
        }

        string[index] = '\0';

        length = my_strlen(string);
        if (length > 0)
        {
            if (length == 1 && isspace(string[0]))
            {
                line_of_expression++;
                free(postfix_expression);
                continue;
            }

            if (!check_brackets(string))
            {
                error = WRONG_COUNT_OF_BRACKETS;
                print_error_in_file(output_file, error, line_of_expression, string);
                printf("Wrong expression, invalid input\n");
                break;
            }

            status_code st_infix_to_postfix_expression = infix_to_postfix(string, &postfix_expression, &error);
            if (st_infix_to_postfix_expression == ERROR_WITH_MEMORY_ALLOCATION)
            {
                flag = 0;
                print_errors(st_infix_to_postfix_expression);
                break;
            }

            else if (st_infix_to_postfix_expression == INVALID_INPUT)
            {
                print_error_in_file(output_file, error, line_of_expression, string);
                printf("Wrong expression, invalid input\n");
                break;
            }

            else
            {
                status_code st_build_binary_expression_tree = build_expression_tree(postfix_expression, &error, &tree_result);
                if (st_build_binary_expression_tree == ERROR_WITH_MEMORY_ALLOCATION)
                {
                    flag = 0;
                    free(postfix_expression);
                    print_errors(st_infix_to_postfix_expression);
                    break;
                }

                else if (st_build_binary_expression_tree == INVALID_INPUT)
                {
                    print_error_in_file(output_file, error, line_of_expression, string);
                    printf("Wrong expression, invalid input\n");
                    break;
                }

                else
                {
                    double result_solve_expression = solve_expression(tree_result, &error);
                    if (result_solve_expression == INVALID_INPUT)
                    {
                        print_error_in_file(output_file, error, line_of_expression, string);
                        printf("Wrong expression, invalid input\n");
                        break;
                    }

                    else if (result_solve_expression == OVERFLOW)
                    {
                        print_error_in_file(output_file, error, line_of_expression, string);
                        printf("Wrong expression, overflowed\n");
                        break;
                    }

                    else
                    {
                        print_tree(tree_result, 0);
                        print_result(string, postfix_expression, result_solve_expression);
                    }
                }
            }
        }
        line_of_expression++;
        free(postfix_expression);
    }
    free_tree(tree_result);
    free(string);
    return OK;
}

char *error_file(char *filename)
{
    char *prefix = "error_";
    char *output = NULL;
    output = (char*) malloc(my_strlen(prefix) + my_strlen(filename) + 1);
    if (!output)
    {
        return NULL;
    }
    sprintf(output, "error_%s", filename);
    return output;
}

status_code all_functions(int argc, char* argv[])
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

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Error with count of arguments\n");
        return 0;
    }

    status_code st = all_functions(argc, argv);
    if (st == OK)
    {
        printf("have done\n");
    }
    else
    {
        printf("rer\n");
    }
}