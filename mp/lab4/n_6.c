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
    NEGATIVE_DIGIT,
    WRONG_COUNT_OF_BRACKETS,
    OVERFLOW,

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

int pop(Stack** stack)
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


int peek(Stack *stack)
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

//-----------------------------------------------------------------------------------------------------
// other
//-----------------------------------------------------------------------------------------------------

int priority(const char data)
{
    if (data == '~')
    {
        return 3;
    }

    else if (data == '?' || data == '!' || data == '+' || data == '&')
    {
        return 2;
    }

    else if (data == '|' || data == '-' || data == '<' || data == '=')
    {
        return 1;
    }

    else
    {
        return 0;
    }
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

bool valid_infix_expression(const char* string)
{

}

int is_operand(const char c)
{
    return (c == '1' || c == '0');
}

int is_operator(const char c)
{
    return (c == '+' || c == '-' || c == '<' || c == '=' || c == '|' || c == '~' || c == '!' || c == '?' || c == '&' || c == '>');
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
        if (isalpha(postfix[i]) || is_operand(postfix[i]))
        {
            node_operand = create_node(postfix[i]);
            push_tree(stack, node_operand);
        }

        else if (is_operator(postfix[i]))
        {
            if (is_empty_tree(stack))
            {
                free(stack);
                *error = INVALID_INPUT;
                return INVALID_INPUT;
            }

            node_operator = create_node(postfix[i]);
            if (postfix[i] == '~')
            {
                node_operator->left = pop_tree(&stack);
                push_tree(stack, node_operator);
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
                push_tree(stack, node_operator);
            }
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

status_code validate_infix_expression(const char* infix)
{
    int i = 0;
    while (infix[i] != '\0')
    {
        if (is_operand(infix[i]) || isalpha(infix[i]))
        {
            if (is_operand(infix[i + 1]) || (!is_operator(infix[i + 1]) && infix[i + 1] != ')' && infix[i + 1] != '\0'))
            {
                return INVALID_INPUT;
            }
        }
        else if (is_operator(infix[i]))
        {
            if ((infix[i] == '-' || infix[i] == '+' || infix[i] == '<') && infix[i + 1] != '>')
            {
                return INVALID_INPUT;
            }
            else if ((!(infix[i] == '-' || infix[i] == '+' || infix[i] == '<') && !is_operand(infix[i + 1]) && !isalpha(infix[i + 1]) && infix[i + 1] != '(') || infix[i + 1] == '\0')
            {
                return INVALID_INPUT;
            }
        }
        else if (strchr("01&|~-+><!?()\n", infix[i]) == NULL && !isalpha(infix[i]))
        {
            return INVALID_INPUT;
        }
        i++;
    }

    if (!check_brackets(infix))
    {
        return WRONG_COUNT_OF_BRACKETS;
    }

    return OK;
}

status_code infix_to_postfix(const char* infix, char** postfix, int* error)
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack)
    {
        *error = ERROR_WITH_MEMORY_ALLOCATION;
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    initialize(stack);

    int len = my_strlen(infix);
    *postfix = (char*)malloc(sizeof(char) * (len + 1));
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
        if (isspace(infix[i]))
        {
            continue;
        }

        if (infix[i] == '~' && is_last_add_operator)
        {
            binary_minus = 1;
            is_last_add_operator = true;
        }

        else if (isalpha(infix[i]) || infix[i] == '1' || infix[i] == '0')
        {
            if (isalnum(infix[i + 1]))
            {
                free(*postfix);
                free(stack);
                *error = INVALID_INPUT;
                return INVALID_INPUT;
            }

            (*postfix)[postfix_size] = infix[i];
            postfix_size++;

            if (binary_minus == 1)
            {
                (*postfix)[postfix_size] = '~';
                postfix_size++;
                binary_minus = 0;
            }

            (*postfix)[postfix_size] = ' ';
            postfix_size++;
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

            if (!is_empty(stack) && peek(stack) == '(')
            {
                pop(&stack);
            }

            is_last_add_operator = false;
        }

        else if (infix[i] == '-' && infix[i + 1] == '>')
        {
            push(stack, '-');
            i++;
        }

        else if (infix[i] == '+' && infix[i + 1] == '>')
        {
            push(stack, '+');
            i++;
        }

        else if (infix[i] == '<' && infix[i + 1] == '>')
        {
            push(stack, '<');
            i++;
        }

        else if (is_operator(infix[i]))
        {
            while (!is_empty(stack) && priority(peek(stack)) >= priority(infix[i]))
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
            free(*postfix);
            free(stack);
            return INVALID_INPUT;
        }
    }

    while (!is_empty(stack))
    {
        if (peek(stack) == '(' || peek(stack) == ')')
        {
            *error = INVALID_INPUT;
            free(stack);
            return INVALID_INPUT;
        }

        (*postfix)[postfix_size] = pop(&stack);
        postfix_size++;

        (*postfix)[postfix_size] = ' ';
        postfix_size++;
    }

    (*postfix)[postfix_size] = '\0';
    free(stack);
    *error = OK;
    return OK;
}

status_code read_file(FILE* input_file, char** string, int* error)
{
    int capacity = 10;

    *string = (char*) malloc(sizeof(char) * (capacity + 1));
    if (!(*string))
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    int index = 0;
    char symbol = fgetc(input_file);

    while (symbol != EOF)
    {
        if (index == capacity - 1)
        {
            capacity *= 2;
            char *tmp = realloc(*string, capacity * sizeof(char));
            if (!tmp)
            {
                free(*string);
                return ERROR_WITH_MEMORY_ALLOCATION;
            }
            *string = tmp;
        }

        (*string)[index] = symbol;

        index++;
        symbol = fgetc(input_file);

        if (symbol == '\n')
        {
            *error = INVALID_INPUT;
            return INVALID_INPUT;
        }
    }

    (*string)[index] = '\0';

    status_code st_validation = validate_infix_expression(*string);
    if (st_validation != OK)
    {
        print_errors(st_validation);
    }

    fclose(input_file);
    return OK;
}

void print_error(int error)
{
    printf("Problem: ");

    switch (error)
    {
        case INVALID_INPUT:
            printf("invalid expression\n");
            break;

        case WRONG_COUNT_OF_BRACKETS:
            printf("wrong count of brackets\n");
            break;

        case NEGATIVE_DIGIT:
            printf("negative digits\n");
            break;

        case OVERFLOW:
            printf("overflowed\n");
            break;
    }
    printf("\n");
}

status_code all_functions(char* filename)
{
    Node* tree_result;
    char* infix_expression = NULL;
    char* postfix_expression = NULL;
    int error;

    FILE *input_file = fopen(filename, "r");
    if (!input_file)
    {
        return ERROR_WITH_OPENING_FILE;
    }

    status_code st_read = read_file(input_file, &infix_expression, &error);
    if (st_read != OK)
    {
        print_error(st_read);
    }

    status_code st_infix_to_postfix = infix_to_postfix(infix_expression, &postfix_expression, &error);
    if (st_infix_to_postfix != OK)
    {
        print_error(st_infix_to_postfix);
    }

    status_code st_build_tree = build_expression_tree(postfix_expression, &error, &tree_result);
    if (st_build_tree != OK)
    {
        print_error(st_build_tree);
    }

//    print_tree(tree_result, 0);


}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Error with number of arguments\n");
        return 0;
    }

    status_code st = all_functions(argv[1]);
    if (st == OK)
    {
        printf("good\n");
    }
    else
    {
        print_error(st);
    }

    return 0;

}





