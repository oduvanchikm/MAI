#ifndef N_9_STORAGES_BINARY_SEARCH_TREE_H
#define N_9_STORAGES_BINARY_SEARCH_TREE_H

#include "../main.h"

typedef struct Binary_node
{
    char* data;
    Department* dep;
    struct Binary_node* left;
    struct Binary_node* right;
    Department* least_load;

} Binary_node;

typedef struct Binary_search_true
{
    Binary_node* node;


} Binary_search_true;


#endif