#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>

typedef struct Node
{
    int data;
    struct Node* next;

} Node;

typedef struct
{
    Node* top;

} Stack;

void initialize(Stack* stack);
void push(Stack* stack, int data);
char pop(Stack** stack);
char peek(Stack* stack);
int is_empty(Stack* stack);


#endif