#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#define TABLE_SIZE 128

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

//-----------------------------------------------------------------------------------------------------
// создам структуру, в которой лежит индекс элемента в хеш-таблице
//-----------------------------------------------------------------------------------------------------

typedef struct Variable_info
{
    int index;
} Variable_info;

//-----------------------------------------------------------------------------------------------------
// хеш-таблица
//-----------------------------------------------------------------------------------------------------

typedef struct
{
    char* key;
    int value; // значение переменной
    Variable_info* info;
} Hash_element;

typedef struct
{
    Hash_element** items;
} Hash_table;

Hash_table* create_table()
{
    Hash_table* table = (Hash_table*)malloc(sizeof(Hash_table));
    if (!table)
    {
        return NULL;
    }

    table->items = (Hash_element**)calloc(TABLE_SIZE, sizeof(Hash_element*));
    if (!table->items)
    {
        free(table);
        return NULL;
    }
    return table;
}

int hash_function(char* key)
{
    int len = strlen(key);
    int hash = 0;
    for (int i = 0; i < len; i++)
    {
        hash += key[i];
    }
    return hash % TABLE_SIZE;
}

void insert(Hash_table* table, char* key, Variable_info* value)
{
//    printf("%d\n", value->index);
//    printf("%s\n", key);
    int index = hash_function(key);

    Hash_element* new_element = (Hash_element*)malloc(sizeof(Hash_element));
    if (!new_element)
    {
        return;
    }

    new_element->key = strdup(key);
    if (!new_element->key)
    {
        free(new_element);
        return;
    }

    new_element->value = -1;
    new_element->info = value;

    table->items[index] = new_element;
}

int search(Hash_table* table, char* key)
{
    int index = hash_function(key);

    if (table->items[index] != NULL && strcmp(table->items[index]->key, key) == 0)
    {
        return table->items[index]->value;
    }
    else
    {
        return -1;
    }
}

//-----------------------------------------------------------------------------------------------------
// узел
//-----------------------------------------------------------------------------------------------------

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

status_code find_unknown_variables(char* string, Hash_table** hash_table)
{
    int len = strlen(string);
    int i = 0;

    char* array_for_variable = (char*)calloc(len + 1, sizeof(char));
    if (!array_for_variable)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    int i_array = 0;
    int variable_index = 0;

    while(string[i] != '\0')
    {
        if (is_operator(string[i]))
        {
            i++;
        }

        else if (isdigit(string[i]))
        {
            i++;
        }

        else if (isalpha(string[i]))
        {
            if (string[i] == 'c' && string[i + 1] == 'o' && string[i + 2] == 's')
            {
                i += 2;
            }

            else if (string[i] == 's' && string[i + 1] == 'i' && string[i + 2] == 'n')
            {
                i += 2;
            }

            else if (string[i] == 't' && string[i + 1] == 'g')
            {
                i += 1;
            }

            else if (string[i] == 'c' && string[i + 1] == 't' && string[i + 2] == 'g')
            {
                i += 2;
            }

            else if (string[i] == 'c' && string[i + 1] == 'h')
            {
                i += 1;
            }

            else if (string[i] == 'e' && string[i + 1] == 'x' && string[i + 2] == 'p')
            {
                i += 2;
            }

            else if (string[i] == 'l' && string[i + 1] == 'n')
            {
                i += 1;
            }

            else if (string[i] == 'l' && string[i + 1] == 'o' && string[i + 2] == 'g')
            {
                i += 2;
            }

            else if (string[i] == 'l' && string[i + 1] == 'g')
            {
                i += 1;
            }

            else if (string[i] == 'c' && string[i + 1] == 'h')
            {
                i += 1;
            }

            else
            {
                array_for_variable[i_array++] = string[i++];
                array_for_variable[i_array] = '\0';

                Variable_info* info_variable = (Variable_info*)malloc(sizeof(Variable_info));
                if (!info_variable)
                {
                    free(array_for_variable);
                    return ERROR_WITH_MEMORY_ALLOCATION;
                }

                info_variable->index = variable_index;
//                printf("%s\n", array_for_variable);
                insert(*hash_table, array_for_variable, info_variable);
                variable_index++;
                i_array = 0;
            }
        }
        else
        {
            printf("%s", string);
            return INVALID_INPUT;
        }
        i++;
    }
    free(array_for_variable);
    return OK;
}

status_code read_expression_and_find_variables(const char* filename, Hash_table* table)
{
    Variable_info* info;
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        return ERROR_WITH_OPENING_FILE;
    }

    char buffer[100];

    while (fscanf(file, "%s", buffer) == 1)
    {
//        printf("%s\n", buffer);
        status_code st = find_unknown_variables(buffer, &table);
        if (st != OK)
        {
            print_errors(st);
        }
        else
        {
            for (int i = 0; i < TABLE_SIZE; i++)
            {
                if (table->items[i] != NULL && table->items[i]->value == -1)
                {
                    printf("Unknown variable at index %d is %s\n", table->items[i]->info->index, table->items[i]->key);
                }
            }

        }
    }
    fclose(file);
}




int main()
{
    Hash_table* table = create_table();

    read_expression_and_find_variables("expression.txt", table);


    return 0;
}