#include "stack.h"

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
