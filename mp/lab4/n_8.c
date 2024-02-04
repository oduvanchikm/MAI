#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

// sin - i, sh - s, cos - o, ctg - c, ch - h, ln - n, log - l, lg - g, tg - t, exp - e

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

int main()
{
    char infix[] = "cos6+sh9*8&9";
    char* postfix = NULL;
    int error;
    Node* tree_result = NULL;

    status_code st = infix_to_postfix(infix, &postfix, &error);
    if (st == OK)
    {
        printf("%s\n", postfix);
        status_code st_build = build_expression_tree(postfix, &error, &tree_result);
        if (st_build == OK)
        {
            print_tree(tree_result, 0);
        }

        else
        {
            print_errors(st_build);
        }
    }
    else
    {
        printf("rer\n");
    }
}