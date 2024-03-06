#include "main.h"
//#include "binary_heap.h"

void read_from_file(FILE* input_file, heap_structure* heap_enum, set_structures* storage_enum,
                    Info_from_first_file data, Department* dep)
{
    char heap[25];
    char storage[30];

    fscanf(input_file, "%s", heap);

    if (strcmp(heap, "BinaryHeap") == 0)
    {
        (*heap_enum) = BINARY_HEAP;
    }
    else if (strcmp(heap, "BinomialHeap") == 0)
    {
        (*heap_enum) = BINOMIAL_HEAP;
    }
    else if (strcmp(heap, "FibonacciHeap") == 0)
    {
        (*heap_enum) = FIBONACCI_HEAP;
    }
    else if (strcmp(heap, "SkewHeap") == 0)
    {
        (*heap_enum) = SKEW_HEAP;
    }
    else if (strcmp(heap, "LeftistHeap") == 0)
    {
        (*heap_enum) = LEFTIST_HEAP;
    }
    else if (strcmp(heap, "Treap") == 0)
    {
        (*heap_enum) = TREAP;
    }

    fscanf(input_file, "%s", storage);

    if (strcmp(storage, "HashSet") == 0)
    {
        (*storage_enum) = HASH_SET;
    }
    else if (strcmp(storage, "DynamicArray") == 0)
    {
        (*storage_enum) = DYNAMIC_ARRAY;
    }
    else if (strcmp(storage, "BinarySearchTree") == 0)
    {
        (*storage_enum) = BINARY_SEARCH_TREE;
    }
    else if (strcmp(storage, "Trie") == 0)
    {
        (*storage_enum) = TRIE;
    }

    fscanf(input_file, "%s", data.date_of_start);
    fscanf(input_file, "%s", data.date_of_end);
    fscanf(input_file, "%d", &(data.min_time));
    fscanf(input_file, "%d", &(data.max_time));
    fscanf(input_file, "%d", &(data.count_of_departments));

    for (int i = 0; i < data.count_of_departments; i++)
    {
        fscanf(input_file, "%d", &(dep[i].count_of_operators));
    }

    fscanf(input_file, "%lf", &(dep->overload_coef));
}


status_code read_requests_from_file(FILE* input_file, Request* requests)
{
    requests = (Request*)malloc(sizeof(Request));
    if (!requests)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    fscanf(input_file, "%s %d %s", requests->timestamp, &(requests->priority), requests->department_id);
    requests->text = malloc(sizeof(char) * 256);
    if (!requests->text)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    fgets(requests->text, 256, input_file);

//    printf("%s\n%d\n%s\n", requests->timestamp, requests->priority, requests->department_id);
//    printf("%s\n", requests->text);

}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("Error with number of arguments\n");
        return 1;
    }

    int max_priority = atoi(argv[1]);

    FILE* file_with_models_parameter = fopen(argv[2], "r");
    if (!file_with_models_parameter)
    {
        printf("Error with opening file\n");
        return 1;
    }

    heap_structure heap;
    set_structures storage;
    Info_from_first_file data;
    Department dep;

    read_from_file(file_with_models_parameter, &heap, &storage, data, &dep);

    FILE* file_with_info_request = NULL;
    Request* request = NULL;

    for (int i = 3; i < argc; i++)
    {
        file_with_info_request = fopen(argv[i], "r");
        if (!file_with_info_request)
        {
            printf("Error with opening file\n");
            return 1;
        }

        status_code st_request = read_requests_from_file(file_with_info_request, request);
        if (st_request != OK)
        {
            print_errors(st_request);
        }

    }
    return 0;
}
