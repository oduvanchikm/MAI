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

Binary_node* insert_binary_tree(Binary_node* root, char* key, Department* value)
{
    if (!root)
    {
        return create_binary_node(key, value);
    }

    if (strcmp(key, root->data) < 0)
    {
        root->left = insert_binary_tree(root->left, key, value);
    }
    else if (strcmp(key, root->data) > 0)
    {
        root->right = insert_binary_tree(root->right, key, value);
    }

    return root;
}

Department* search_binary_tree(Binary_node* root, char* key)
{
    if (root == NULL || strcmp(key, root->data) == 0)
    {
        return root->dep;
    }

    if (strcmp(key, root->data) < 0)
    {
        return search_binary_tree(root->left, key);
    }
    else
    {
        return search_binary_tree(root->right, key);
    }
}

void free_binary_tree(Binary_node* root, void(*free_heap)(void*, int))
{
    if (root == NULL) {
        return;
    }

    free_binary_tree(root->left, free_heap);
    free_binary_tree(root->right, free_heap);

    if (root->data)
    {
        free(root->data);
    }

    free_heap(root->dep->data_structure, 1);
    free(root->dep->operators);

    free(root);
}
