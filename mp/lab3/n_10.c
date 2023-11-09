#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum status_code 
{
    OK, 
    ERROR_WITH_MEMORY_ALLOCATION,
    WRONG_ARGUMENT
};

void print_errors(int flag)
{
    switch (flag)
    {
    case ERROR_WITH_MEMORY_ALLOCATION:
        printf("Error with memory\n");
        break;
    
    case WRONG_ARGUMENT:
        printf("Error with invalif arguments\n");
    
    default:
        break;
    }
}

typedef struct Node
{
    char data;
    struct Node *parent;
    struct Node *child;
    struct Node *brother;

} Node;

void delete_tree(Node* node)
{
    if (!node)
    {
        return;
    }

    delete_tree(node->child);

    free(node);
}

enum status_code create_root(char data, Node **node)
{
    *node = (Node*)malloc(sizeof(Node));

    if (!(*node))
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    (*node)->data = data;
    (*node)->parent = NULL;
    (*node)->child = NULL;
    (*node)->brother = NULL;

    return OK;
}

enum status_code add_child(char data, Node *node)
{
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (!new_node)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    new_node->data = data;
    new_node->parent = node;
    new_node->child = NULL;
    new_node->brother = NULL;

    node->child = new_node;

    return OK;
}


enum status_code add_brother(char data, Node *node)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    new_node->data = data;
    new_node->parent = node->parent;
    new_node->child = NULL;
    new_node->brother = NULL;

    node->brother = new_node;

    return OK;
}

void fprint_tree(FILE* file, Node *root, int tab) 
{
    if (!root) 
    {
        return;
    }

    for (int i = 0; i < tab; i++) 
    {
        fprintf(file, "   ");
    }

    fprintf(file, "%c\n", root->data);

    fprint_tree(file, root->child, 1 + tab);
    fprint_tree(file, root->brother, tab);
}

enum status_code build_tree(char *expression_string, Node **tree)
{
    if (create_root(expression_string[0], tree) != OK)
    {
        return WRONG_ARGUMENT;
    }

    int count = strlen(expression_string);

    Node *tree_tmp = *tree;

    for (int i = 0; i < count; i++)
    {
        switch (expression_string[i])
        {
            case '(':
                i++;
                add_child(expression_string[i], tree_tmp);
                tree_tmp = tree_tmp->child;
                break;

            case ',':
                i++;
                add_brother(expression_string[i], tree_tmp);
                tree_tmp = tree_tmp->brother;
                break;
            
            case ')':
                tree_tmp = tree_tmp->parent;
                break;
        }
    }

    return OK;
}

int main(int argc, char *argv[]) 
{
    if (argc != 3)
    {
        printf("Invalid number of arguments.\n");
        printf("Enter a file of input file and output file.\n");
        return 1;
    }

    FILE* input_file = fopen(argv[1], "r");
    FILE* output_file = fopen(argv[2], "w");

    if (!input_file || !output_file) 
    {
        printf("Error with opening file.\n");
        return 1;
    }

    char expression_string[256];

    fgets(expression_string, 256, input_file);
    Node *tree = NULL;

    enum status_code st = build_tree(expression_string, &tree);

    if (st != OK)
    {
        print_errors(st);
        return 1;
    }

    fprint_tree(output_file, tree, 0);

    delete_tree(tree);

    fclose(input_file);
    fclose(output_file);

    return 0;
}