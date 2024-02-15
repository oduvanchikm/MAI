#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

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
    char* data;
    int count;
    struct Node* left;
    struct Node* right;

} Node;

Node* create_new_node(char *word)
{
    Node *new_node = (Node*)malloc(sizeof(Node));
    if(!new_node)
    {
        return NULL;
    }

    new_node->data = strdup(word);
    if (!new_node->data)
    {
        return NULL;
    }

    new_node->count = 1;
    new_node->left = new_node->right = NULL;

    return new_node;
}

Node* insert_node(Node* root, char* word)
{
    int compare;
    if(!root)
    {
        return create_new_node(word);
    }

    else
    {
        compare = strcmp(word, root->data);
        if(!compare)
        {
            root->count++;
        }

        else if(compare < 0)
        {
            root->left = insert_node(root->left, word);
        }

        else
        {
            root->right = insert_node(root->right, word);
        }
    }
    return root;
}

int count_nodes(Node* root)
{
    if(!root)
    {
        return 0;
    }

    return count_nodes(root->left) + count_nodes(root->right) + 1;
}

int count_words(Node* node, char* word)
{
    printf("%s\n", word);
    int count = 0;
    if(!node)
    {
        return -1;
    }

    if (strcmp(node->data, word) == 0)
    {
        count++;
    }

    else if (strcmp(node->data, word) < 0)
    {
        count_words(node->left, word);
    }

    else
    {
        count_words(node->right, word);
    }

    return count;
}

int find_word_in_tree(Node* root, char* word)
{
    int compare;
    int count = 0;
    if (!root)
    {
        return count;
    }
    else
    {
        compare = strcmp(word, root->data);

        if(!compare)
        {
            count += root->count;
        }

        else if (compare < 0)
        {
            count += find_word_in_tree(root->left, word);
        }

        else
        {
            count += find_word_in_tree(root->right, word);
        }
    }
    return count;
}

int get_tree_depth(Node *root)
{
    if (!root)
    {
        return 0;
    }

    int left_depth = get_tree_depth(root->left);
    int right_depth = get_tree_depth(root->right);

    if(left_depth > right_depth)
    {
        return left_depth + 1;
    }
    else
    {
        return right_depth + 1;
    }
}

Node* destroy_tree(Node* root)
{
    if(root)
    {
        destroy_tree(root->left);
        destroy_tree(root->right);
        free(root->data);
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

    fprintf(file_for_save, "%s%c", root->data, separators[0]);
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

bool is_separator(const char symbol, char *separator)
{
    int length = strlen(separator);

    for(int i = 0; i < length; i++)
    {
        if (symbol == separator[i] || symbol == ' ')
        {
            return true;
        }
    }
    return false;
}

status_code read_file(FILE* input, char* separator, Node** root)
{
    char symbol;
    int size = 10;
    char* word = (char*)malloc(sizeof(char) * (size + 1));
    if(!word)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    int index = 0;
    while((symbol = fgetc(input)) != EOF)
    {
        if(!is_separator(symbol, separator))
        {
            word[index++] = symbol;

            if (index == size - 1)
            {
                size *= 2;
                char *temp = (char*)realloc(word, size * sizeof(char));
                if (!temp)
                {
                    free(word);
                    return ERROR_WITH_MEMORY_ALLOCATION;
                }
                word = temp;
            }
        }
        else
        {
            if (index > 0)
            {
                word[index] = '\0';
                printf("%s\n", word);
                *root = insert_node(*root, word);
                if (!(*root))
                {
                    free(word);
                    return ERROR_WITH_MEMORY_ALLOCATION;
                }

                index = 0;
                free(word);

                word = (char*)malloc(sizeof(char) * (size + 1));
                if(!word)
                {
                    return ERROR_WITH_MEMORY_ALLOCATION;
                }
            }
        }
    }
    if (index > 0)
    {
        word[index] = '\0';
        *root = insert_node(*root, word);
        if (!(*root))
        {
            free(word);
            return ERROR_WITH_MEMORY_ALLOCATION;
        }
    }
    free(word);
    return OK;
}

void print_tree(Node *root, int level)
{
    if(root)
    {
        for(int i = 0; i < level; i++)
        {
            printf("    ");
        }
        printf("%s(%d)\n", root->data, root->count);
        print_tree(root->left, level + 1);
        print_tree(root->right, level + 1);
    }
}

int count_of_nodes(Node* root)
{
    if(!root)
    {
        return 0;
    }

    return 1 + count_of_nodes(root->left) + count_of_nodes(root->right);
}

void read_from_file(FILE* input_file, Node** root, const char* separators)
{
    char buffer[100];
    while (fscanf(input_file, "%s", buffer) != EOF)
    {
        char* word = strtok(buffer, separators);
        while (word != NULL)
        {
            *root = insert_node(*root, word);
            word = strtok(NULL, separators);
        }
    }
}

int find_longest_and_shortest_words(Node* root, char** longest_word, char** shortest_word)
{
    if (!root)
    {
        return INVALID_VALUE;
    }

    if ((*longest_word) == NULL || strlen(root->data) > strlen(*longest_word))
    {
        (*longest_word) = strdup(root->data);
        if (!(*longest_word))
        {
            return ERROR_WITH_MEMORY_ALLOCATION;
        }
    }

    else if ((*shortest_word) == NULL || strlen(root->data) < strlen(*shortest_word))
    {
        (*shortest_word) = strdup(root->data);
        if (!(*longest_word))
        {
            return ERROR_WITH_MEMORY_ALLOCATION;
        }
    }

    find_longest_and_shortest_words(root->left, longest_word, shortest_word);
    find_longest_and_shortest_words(root->right, longest_word, shortest_word);
    return OK;
}

bool check_file(const char* filename)
{
    int len = strlen(filename);

    if (len <= 4)
    {
        return false;
    }

    for (int i = len - 1; i > 0; i--)
    {
        if (filename[i] == 't' && filename[i - 1] == 'x' && filename[i - 2] == 't' && filename[i - 3] == '.' && isalnum(filename[i - 4]))
        {
            return true;
        }
    }
    return false;
}

void nodes_in_one_place(Node* node, Node** array_of_nodes, int* index)
{
    if(!node)
    {
        return;
    }

    nodes_in_one_place(node->left, array_of_nodes, index);

    array_of_nodes[*index] = node;
    (*index)++;

    nodes_in_one_place(node->right, array_of_nodes, index);
}


void write_tree_to_file(FILE* output_file, Node* root, char* separators)
{
    if(!root)
    {
        return;
    }

    fprintf(output_file, "%s%c", root->data, separators[0]);
    save_tree_to_file(output_file, root->left, separators);
    save_tree_to_file(output_file, root->right, separators);
}

void write_words(Node* root, Node** array_of_nodes, int* count, int number)
{
    if (!root)
    {
        return;
    }

    for (int i = 0; i < number; i++)
    {
        if (array_of_nodes[i] == NULL)
        {
            array_of_nodes[i] = root;
            (*count)++;
            break;
        }
        else if (array_of_nodes[i]->count <= root->count)
        {
            if ((*count) < number)
            {
                for (int j = *count; j > i; j--)
                {
                    array_of_nodes[j] = array_of_nodes[j - 1];
                }

                array_of_nodes[i] = root;
                (*count)++;
                break;

            }
            else
            {
                for (int j = number - 1; j > i; j--)
                {
                    array_of_nodes[j] = array_of_nodes[j - 1];
                }

                array_of_nodes[i] = root;
                break;
            }
        }
    }
    write_words(root->left, array_of_nodes, count, number);
    write_words(root->right, array_of_nodes, count, number);

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

    status_code st_read_file = read_file(file_input, separators, &root);
    if (st_read_file != OK)
    {
        free(separators);
        print_errors(st_read_file);
    }

    print_tree(root, 0);

    int flag = 1;

    int count = count_of_nodes(root);

    while(flag)
    {
        char number_of_words;
        char* longest_word = NULL;
        char* shortest_word = NULL;
        int depth;
        int index;
        int count_new = 0;
        char action_char;
        char word_find[100];
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
                int count_find_of_words = find_word_in_tree(root, word_find);

                printf("Word %s occurred %d times in the file.\n", word_find, count_find_of_words);
                break;

            case 2:
                printf("Program outputs the first <n> most common words in a file\n");
                printf("Please enter <n>: \n");
                scanf("%s", &number_of_words);
                if (!is_digit(&number_of_words))
                {
                    printf("It's wrong number\nEnter only digits\n");
                    root = destroy_tree(root);
                    return INVALID_VALUE;
                }

                int number = atoi(&number_of_words);

                if (number > count)
                {
                    printf("You enter a very big value\n");
                    return INVALID_VALUE;
                }

                Node** array_of_nodes = (Node**)malloc(sizeof(Node*) * count);
                if(!array_of_nodes)
                {
                    destroy_tree(root);
                    printf("Error with memory allocation\n");
                    return ERROR_WITH_MEMORY_ALLOCATION;
                }

                for (int i = 0; i < number; i++)
                {
                    array_of_nodes[i] = NULL;
                }

                write_words(root, array_of_nodes, &count_new, number);

                printf("%d the words:\n", number);

                for (int i = 0; i < number; i++)
                {
                    printf("%d. %s\n", i + 1, array_of_nodes[i]->data);
                }

            case 3:
                printf("Program searches the longest and shortest words\n");
                int flag = find_longest_and_shortest_words(root, &longest_word, &shortest_word);
                if (flag != OK)
                {
                    return INVALID_VALUE;
                }
                printf("The shortest word is %s\n", shortest_word);
                printf("The longest word is %s\n", longest_word);
                break;

            case 4:
                printf("Program finds depth in th tree\n");
                depth = get_tree_depth(root);
                printf("The max depth of the tree is %d\n", depth);
                break;

            case 5:
                printf("Program saves tree to file\n");
                printf("Enter the file name where you want to save tree:\n");
                scanf("%s", file_5);

                if (!check_file(file_5))
                {
                    printf("Error with file\n");
                    return INVALID_VALUE;
                }

                if (strcmp(argv[1], file_5) == 0)
                {
                    printf("It's not a different files\nPlease enter other file for output\n");
                    return ERROR_WITH_OPENING_FILE;
                }

                FILE* output_file = fopen(file_5, "w");
                if(!output_file)
                {
                    printf("Error with opening file\n");
                    destroy_tree(root);
                    free(separators);
                    return ERROR_WITH_OPENING_FILE;
                }

                write_tree_to_file(output_file, root, separators);
                printf("Tree saves to file\n");
                destroy_tree(root);
                fclose(output_file);
                break;

            case 6:
                printf("Program loads tree from file\n");
                printf("Please enter the filename from read tree:\n");
                scanf("%s", file_6);

                if (!check_file(file_6))
                {
                    printf("Error with file\n");
                    return INVALID_VALUE;
                }

                FILE* input_file = fopen(file_6, "r");
                if(!input_file)
                {
                    printf("Error with opening file\n");
                    destroy_tree(root);
                    free(separators);
                    return ERROR_WITH_OPENING_FILE;

                }

                read_from_file(input_file, &root, separators);
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
