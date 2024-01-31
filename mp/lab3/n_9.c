#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum
{
    OK, 
    ERROR_WITH_MEMORY_ALLOCATION,
    INVALID_VALUE,
    ERROR_WITH_NUMBER_OF_ARGUMENTS,
    ERROR_WITH_OPENING_FILE

} status_code;

void print_errors(int flag)
{
    switch(flag)
    {
        case ERROR_WITH_MEMORY_ALLOCATION:
            printf("Error with memory allocation\n");
            break;

        case INVALID_VALUE:
            printf("Invalid input\n");
            break;

        case ERROR_WITH_NUMBER_OF_ARGUMENTS:
            printf("Wrong number of arguments\nEnter input file and separators\n");
            break;

        case ERROR_WITH_OPENING_FILE:
            printf("Error with opening file\n");
            break;

        default:
            break;
    }
}

void print_actions()
{
    printf("\tMENU\n");
    printf("Enter a digit 1 - 7 and you can see:\n");
    printf("1 - how many times a word occurs in a file\n");
    printf("2 - output the first n most common words in a file\n");
    printf("3 - search the longest and shortest words\n");
    printf("4 - find depth in th tree\n");
    printf("5 - save tree in file\n");
    printf("6 - load tree from file\n");
    printf("7 - exit the menu\n");
}

bool check_action(char action)
{
    if (action < '1' || action > '7')
    {
        return false;
    }
    return true;
}

typedef struct Node
{
    char* word;
    int count;
    struct Node* left;
    struct Node* right;

} Node;

Node* create_new_node(char* word)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node)
    {
        return NULL;
    }
    new_node->word = (char*)malloc((strlen(word) + 1) * sizeof(char));

    if (!new_node->word)
    {
        free(new_node);
        return NULL;
    }

    strcpy(new_node->word, word);
    new_node->count = 1;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;

}

Node* insert_node(Node* root, char* word)
{
    if (root == NULL)
    {
        return create_new_node(word);
    }

    int res_strcmp = strcmp(word, root->word);

    if (res_strcmp == 0)
    {
        root->count++;
    }
    else if (res_strcmp < 0)
    {
        root->left = insert_node(root->left, word);
    }
    else
    {
        root->right = insert_node(root->right, word);
    }

    return root;
}

void read_file(FILE* file, Node** root, const char* separators)
{
    char buffer[100];
    while (fscanf(file, "%s", buffer) != EOF)
    {
        char* word = strtok(buffer, separators);
        while (word != NULL)
        {
            *root = insert_node(*root, word);
            word = strtok(NULL, separators);
        }
    }
}

void print_tree(Node* root, int depth)
{
    if (root == NULL)
    {
        return;
    }

    print_tree(root->left, depth + 1);
    for (int i = 0; i < depth*3; i++)
    {
        printf("     ");
    }
    printf("./%s(%d)\n", root->word, root->count);
    print_tree(root->right, depth + 1);
}

int count_nodes(Node* root)
{
    if(root == NULL)
    {
        return 0;
    }

    return count_nodes(root->left) + count_nodes(root->right) + 1;
}

//void count_words(Node* node, char* word, int* count)
//{
//    if(!node)
//    {
//        return;
//    }
//
//    if(strcmp(node->word, word) == 0)
//    {
//        (*count)++;
//    }
//
//    else if (strcmp(node->word, word) < 0)
//    {
//        count_words(node->left, word, count);
//    }
//
//    else
//    {
//        count_words(node->right, word, count);
//    }
//}

int count_words(Node* node, char* word)
{
    int count = 0;
    if(!node)
    {
        return -1;
    }

    if(strcmp(node->word, word) == 0)
    {
        count++;
    }

    else if (strcmp(node->word, word) < 0)
    {
        count_words(node->left, word);
    }

    else
    {
        count_words(node->right, word);
    }

    return count;
}

int compare(const void* a, const void* b)
{
    Node* node_a = *(Node**)a;
    Node* node_b = *(Node**)b;

    return node_b->count - node_a->count;
}

void all_nodes(Node* node, Node*** array_of_nodes, int* index_2)
{

    if(node == NULL)
    {
        return;
    }

    all_nodes(node->left, array_of_nodes, index_2);

    (*array_of_nodes)[*index_2] = node;
    (*index_2)++;

    all_nodes(node->right, array_of_nodes, index_2);
}

void search_min_and_max_words(Node* root, Node** min_3, Node** max_3)
{
    if(!root)
    {
        return;
    }

    search_min_and_max_words(root->right, min_3, max_3);
    if(strlen(root->word) > strlen((*max_3)->word))
    {
        (*max_3) = root;
    }

    if(strlen(root->word) < strlen((*min_3)->word))
    {
        *min_3 = root;
    }

    search_min_and_max_words(root->left, min_3, max_3);

}

void find_depth_of_tree(Node* root, unsigned int* max_depth_3, int depth_3)
{
    if(!root)
    {
        return;
    }

    if(root->left)
    {
        find_depth_of_tree(root->left, max_depth_3, depth_3 + 1);
    }

    if(root->right)
    {
        find_depth_of_tree(root->right, max_depth_3, depth_3 + 1);
    }

    if(depth_3 > (*max_depth_3))
    {
        (*max_depth_3) = depth_3;
    }
}

Node* destroy_tree(Node* root)
{
    if(root)
    {
        destroy_tree(root->left);
        destroy_tree(root->right);
        free(root->word);
        free(root);
    }

    return NULL;
}

void save_tree_to_file(FILE* file_for_save, Node* root, char* separators)
{
    if(!root)
    {
        return;
    }

    fprintf(file_for_save, "%s%c", root->word, separators[0]);
    save_tree_to_file(file_for_save, root->left, separators);
    save_tree_to_file(file_for_save, root->right, separators);
}

bool is_digit(char* string)
{
    int len = strlen(string);
    for (int i = 0; i < len; i++)
    {
        if (string[i] < '0' || string[i] > '9')
        {
            return false;
        }
    }
    return true;
}

bool check_input(int argc, const char* argv[])
{
    if (argc < 3)
    {
        return false;
    }

    for (int i = 2; i < argc; i++)
    {
        if (strlen(argv[i]) != 1)
        {
            return false;
        }
    }
    return true;
}

int main(int argc, const char* argv[])
{
    if (!check_input(argc, argv))
    {
        printf("Error with number of arguments\n");
        return 0;
    }

    FILE* file_input = fopen(argv[1], "r");
    if (!file_input)
    {
        printf("Error with opening file\n");
        return 0;
    }

    int length_of_separators = argc - 2;
    char* separators = (char*)malloc(sizeof(char) * (length_of_separators + 1));
    if (!separators)
    {
        printf("Error with memory allocation\n");
        return 0;
    }

    separators[0] = '\0';

    for (int i = 2; i < argc; i++)
    {
        strcat(separators, argv[i]);
    }

    Node* root = NULL;

    read_file(file_input, &root, separators);
    int count_of_nodes = count_nodes(root);

    int flag = 1;

    while(flag)
    {
        char action_char;
        char word_find[100];
        char action_2_char;
        int index_2 = 0;
        Node* min = root;
        Node* max = root;
        int depth_3 = 1;
        unsigned int max_depth = 0;
        char file_5[32];
        char file_6[32];

        print_actions();
        scanf("%s", &action_char);
        if(!check_action(action_char))
        {
            printf("Wrong action\nPlease enter other action\n");
            root = destroy_tree(root);
        }

        int action = atoi(&action_char);

        if (action == 7)
        {
            flag = 0;
            root = destroy_tree(root);
        }

        switch(action)
        {
            case 1:
                printf("Program shows how many times a word occurs in a file\n");
                printf("Enter word which you want to find:\n");

                scanf("%s", word_find);
                int count_find_words_1 = count_words(root, word_find);

                printf("Word %s occurred %d times in the file.\n", word_find, count_find_words_1);
                break;

            case 2:
                printf("Program outputs the first <n> most common words in a file\n");
                printf("Please enter <n>: \n");
                scanf("%s", &action_2_char);
                if (!is_digit(&action_2_char))
                {
                    printf("It's wrong number\nEnter only digits\n");
                    root = destroy_tree(root);
                    return INVALID_VALUE;
                }

                int action_2 = atoi(&action_2_char);

                Node** array_of_nodes = (Node**)malloc(sizeof(Node*) * count_of_nodes);
                if(!array_of_nodes)
                {
                    destroy_tree(root);
                    printf("Error with memory allocation\n");
                    return ERROR_WITH_MEMORY_ALLOCATION;
                }

                all_nodes(root, &array_of_nodes, &index_2);

                qsort(array_of_nodes, count_of_nodes, sizeof(Node**), compare);
                for (int i = 0; i < action_2; i++)
                {
                    printf("%s\n", array_of_nodes[i]->word);
                }

                printf("\n");
                free(array_of_nodes);
                break;

            case 3:
                printf("Program searches the longest and shortest words\n");
                search_min_and_max_words(root, &min, &max);
                printf("The shortest word is %s\n", min->word);
                printf("The longest word is %s\n", max->word);
                break;

            case 4:
                printf("Program finds depth in th tree\n");
                find_depth_of_tree(root, &max_depth, depth_3);
                printf("The max depth of the tree is %u\n", max_depth);
                break;

            case 5:
                printf("Program saves tree to file\n");
                printf("Enter the file name where you want to save tree:\n");
                scanf("%s", file_5);
                FILE* output_file = fopen(file_5, "w");
                if(!output_file)
                {
                    printf("Error with opening file\n");
                    destroy_tree(root);
                    free(separators);
                    return ERROR_WITH_OPENING_FILE;
                }

                save_tree_to_file(output_file, root, separators);
                printf("Tree saves to file\n");
                destroy_tree(root);
                fclose(output_file);
                break;

            case 6:
                printf("Program loads tree from file\n");
                printf("Please enter the filename from read tree:\n");
                scanf("%s", file_6);
                FILE* input_file = fopen(file_6, "r");
                if(!input_file)
                {
                    printf("Error with opening file\n");
                    destroy_tree(root);
                    free(separators);
                    return ERROR_WITH_OPENING_FILE;

                }

                read_file(input_file, &root, separators);
                printf("Tree\n");
                print_tree(root, 0);
                fclose(input_file);
                break;
        }
    }
    free(separators);
    destroy_tree(root);
    return 0;
}
