#ifndef N_9_STORAGES_HASH_SET_H
#define N_9_STORAGES_HASH_SET_H

#include "../main.h"

typedef struct Hash_set_node
{
    char* key;
    struct Hash_set_node* prev;
    struct Hash_set_node* next;
    Department* dep;

} Hash_set_node;



#endif