#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

typedef enum
{
    OK,
    ERROR_WITH_MEMORY_ALLOCATION,
    INVALID_INPUT,
    ERROR_WITH_COUNT_OF_ARGUMENTS,
    ERROR_WITH_OPENING_FILE,
    EMPTY

} status_code;


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
        ERROR_WITH_MEMORY_ALLOCATION;
    }

    new_node->data = data;
    new_node->next = stack->top;
    stack->top = new_node;
}

int pop(Stack* stack) 
{
    if (stack->top == NULL) 
    {
        return EMPTY;
    }
    int data = stack->top->data;
    Node* temp = stack->top;
    stack->top = stack->top->next;

    free(temp);

    return data;
}

int is_empty(Stack* stack) 
{
    return stack->top == NULL;
}

bool is_operator(char c) 
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%');
}

int get_priority(char operator) 
{
    if (operator == '^') 
    {
        return 3;
    }
    else if (operator == '*' || operator == '/' || operator == '%') 
    {
        return 2;
    }
    else if (operator == '+' || operator == '-') 
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

// char* infix_to_postfix(char* expression) // Shunting Yard algorithm
// {
//     Stack stack;
//     stack.top = NULL;

//     int len = strlen(expression);

//     char *postfix = malloc(len * 2);

//     if (!postfix)
//     {
//         return;
//     }

//     int digit = 0;
//     for (int i = 0; expression[i] != '\0'; i++)
//     {
//         char c = expression[i];

//         if (c >= '0' && c <= '9')
//         {
//             postfix[digit++] = c;
//         }

//         else if (is_operator(c))
//         {
//             if (is_empty(&stack))
//             {
//                 push(&stack, c);
//             }
//             else
//             {
//                 char temp = pop(&stack);
//                 if (get_priority(temp) <= get_priority(c))
//                 {
//                     push(&stack, c);
//                     push(&stack, temp); 
//                 }
//                 else
//                 {
//                     push(&stack, temp);
//                     push(&stack, c);
//                 }
//             }
//         }

//         else if (c == '(')
//         {
//             push(&stack, c);
//         }
//         else if (c == ')')
//         {
//             char temp = pop(&stack);

//             while (!is_empty(&stack) && temp != '(') 
//             {
//                 postfix[digit++] = pop(&stack);
//             }

//             if (!is_empty(&stack) && temp != '(') 
//             {
//                 free(postfix);
//                 return NULL;
//             } 
//             else 
//             {
//                 pop(&stack);
//             }
//         }
//     }
    
//     while (!is_empty(&stack))
//     {
//         postfix[digit++] = pop(&stack);
//     }
    
//     postfix[digit] = '\0';
//     return postfix;
// }

char* infix_to_postfix(char* expression) 
{
    Stack stack;
    initialize(&stack);

    int len = strlen(expression);

    char *postfix = (char*)malloc(len + 1);

    if (!postfix)
    {
        return NULL;
    }

    int digit = 0;

    for (int i = 0; expression[i] != '\0'; i++)
    {
        char c = expression[i];

        if (c >= '0' && c <= '9')
        {
            postfix[digit++] = c;
        }

        else if (is_operator(c))
        {
            if (is_empty(&stack))
            {
                push(&stack, c);
            }
            else
            {
                char temp = pop(&stack);
                if (get_priority(temp) <= get_priority(c))
                {
                    push(&stack, c);
                    push(&stack, temp); 
                }
                else
                {
                    push(&stack, temp);
                    push(&stack, c);
                }
            }
        }

        else if (c == '(')
        {
            push(&stack, c);
        }

        else if (c == ')')
        {
            char temp = pop(&stack);

            while (!is_empty(&stack) && temp != '(') 
            {
                postfix[digit++] = pop(&stack);
            }

            if (!is_empty(&stack) && temp != '(') 
            {
                free(postfix);
                return NULL;
            } 
            else 
            {
                pop(&stack);
            }
        }
    }
}


int check_balance(char* expression) 
{
    Stack stack;
    stack.top = NULL;

    int len = strlen(expression);
    for (int i = 0; i < len; i++)
    {
        char c = expression[i];
        if (c == '(')
        {
            push(&stack, c);
        }
        else if (c == ')')
        {
            if (is_empty(&stack) || pop(&stack) != '(')
            {
                return 0;
            }
        }
    }
    
    return is_empty(&stack);
}

int solve_expression(char* expression) 
{
    Stack stack;
    int i = 0;
    while (expression[i]) 
    {
        if (isdigit(expression[i])) 
        {
            push(&stack, expression[i] - '0');
        }
        else 
        {
            double operator1 = pop(&stack);
            double operator2 = pop(&stack);
            switch (expression[i]) 
            {
                case '+': 
                    push(&stack, operator1 + operator2);
                    break;

                case '-': 
                    push(&stack, operator1 - operator2);
                    break;

                case '*': 
                    push(&stack, operator1 * operator2);
                    break;

                case '/': 
                    push(&stack, operator1 / operator2);
                    break;

                case '^': 
                    push(&stack, pow(operator1, operator2));
                    break;
            }
        }
        i++;
    }
    return pop(&stack);
}

int main(int argc, char* argv[]) 
{
    if (argc < 2)
    {
        printf("Error with number of arguments\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) 
    {
        FILE* file = fopen(argv[i], "r");
        if (!file) 
        {
            printf("error\n");
            exit(1);
        }
        char line[1000];

        while (fgets(line, sizeof(line), file)) 
        {
            printf("Infix expression: %s\n", line);
            char expression[1000];
            strcpy(expression, line);

            if (check_balance(expression)) 
            {
                char* postfix_expression = infix_to_postfix(expression);
                printf("Postfix expression: %s\n", postfix_expression);

                int value = solve_expression(postfix_expression);
                printf("Result: %d\n", value);
                
                free(postfix_expression);
            }
            else 
            {
                printf("ERROR\n");
            }
        }
        fclose(file);
    }
    return 0;
}
