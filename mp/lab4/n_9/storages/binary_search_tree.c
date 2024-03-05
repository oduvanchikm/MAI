#include "binary_search_tree.h"

Binary_node* create_binary_node(char* key, Department* value)
{
    Binary_node* new_binary_node = (Binary_node*)malloc(sizeof(Binary_node));
    if (!new_binary_node)
    {
        return NULL;
    }

    new_binary_node->right = NULL;
    new_binary_node->left = NULL;
    new_binary_node->least_load = NULL;
    new_binary_node->data = key;
    new_binary_node->dep = value;

    return new_binary_node;
}