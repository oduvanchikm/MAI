#include "main.h"
//#include "binary_heap.h"

Info* read_data_from_first_file(FILE* file)
{
    Info* data = (Info*)malloc(sizeof(Info));
    if (!data)
    {
        return NULL;
    }

    fscanf(file, "%s", data->heap_type);
    fscanf(file, "%s", data->set_type);
    fscanf(file, "%s", data->date_of_start);
    fscanf(file, "%s", data->date_of_end);
    fscanf(file, "%d", &(data->min_time));
    fscanf(file, "%d", &(data->max_time));
    fscanf(file, "%d", &(data->count_of_depatment));

    data->count_of_operators = (char**)malloc(sizeof(char*) * (data->count_of_depatment + 1));
    if (!data->count_of_operators)
    {
        free(data);
        return NULL;
    }

    for (int i = 0; i < data->count_of_depatment; i++)
    {
        data->count_of_operators[i] = (char*)malloc(sizeof(char) * (data->count_of_depatment + 1));
        fscanf(file, "%s", data->count_of_operators[i]);
    }

    fscanf(file, "%lf", &(data->overload_coef));
    fclose(file);
    return data;
}

storage_of_applications choosing_data_structure(Info* data)
{
    if (strcmp(data->heap_type, "BinaryHeap") == 0)
    {
        return BINARY_HEAP;
    }

    else if (strcmp(data->heap_type, "BinomialHeap") == 0)
    {
        return BINOMIAL_HEAP;
    }

    else if (strcmp(data->heap_type, "FibonacciHeap") == 0)
    {
        return FIBONACCI_HEAP;
    }

    else if (strcmp(data->heap_type, "SkewHeap") == 0)
    {
        return SKEW_HEAP;
    }

    else if (strcmp(data->heap_type, "LeftistHeap") == 0)
    {
        return LEFTIST_HEAP;
    }

    else if (strcmp(data->heap_type, "Treap") == 0)
    {
        return TREAP;
    }

    else
    {
        return INVALID_STRUCTURE;
    }
}


status_code read_line(FILE* file, char** line)
{
    if (file == NULL || line == NULL)
    {
        return INVALID_INPUT;
    }

    int i = 0;
    int size = 10;

    char* line_tmp = (char*) malloc(sizeof(char) * size);
    if (!line_tmp)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    char ch = getc(file);
    if (feof(file))
    {
        free(line_tmp);
        return INVALID_INPUT;
    }

    while (!feof(file) && ch != '\n')
    {
        if (i + 1 == size)
        {
            size *= 2;
            char* tmp = realloc(line_tmp, size);
            if (!tmp)
            {
                free(line_tmp);
                return ERROR_WITH_MEMORY_ALLOCATION;
            }

            line_tmp = tmp;
        }
        line_tmp[i++] = ch;
        ch = getc(file);
    }

    line_tmp[i] = '\0';
    *line = line_tmp;
    return OK;
}

status_code create_request(char* line, Request* requests, FILE* input_file)
{
    status_code st_line = read_line(input_file, &line);
    if (st_line != OK)
    {
        return INVALID_INPUT;
    }

    int len = strlen(line);
    printf("%s\n", line);

    int flag = 1;
    int time_size = 19;

    char* time_string = (char*)malloc(sizeof(char) * (time_size + 1));
    if (!time_string)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    time_string[time_size] = '\0';

    char* comment = (char*)malloc(sizeof(char) * (len - time_size + 1));
    if (!comment)
    {
        free(time_string);
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    comment[len - time_size] = '\0';

    int comment_index = 0;
    int time_index = 0;
    int index = 0;

    while (line[index] != '\n' && !isspace(line[index]) && time_index < time_size)
    {
        time_string[time_index++] = line[index];
        index++;
    }

    time_string[time_index] = '\0';

    flag = 1;

    while (line[index] != '\n' && line[index] != EOF && flag)
    {
        if (line[index] == '"')
        {
            index++;
            while (line[index] != '"' && line[index] != '\0')
            {
                comment[comment_index++] = line[index];
                index++;
            }

            comment[comment_index] = '\0';
            flag = 0;
        }

        index++;
    }

    while (line[index] != '\n' && line[index] != EOF)
    {



    }

    if (flag == 1)
    {
        free(comment);
        free(time_string);
        return INVALID_INPUT;
    }

    printf("%s\n", time_string);
    printf("%s\n", comment);

    free(comment);
    free(time_string);

    return OK;
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

    Info* data = read_data_from_first_file(file_with_models_parameter);

    storage_of_applications st_storage = choosing_data_structure(data);
    if (st_storage == INVALID_STRUCTURE)
    {
        printf("You write a wrong structure\nPlease enter other in file\n");
        for (int i = 0; i < data->count_of_depatment; i++)
        {
            free(data->count_of_operators[i]);
        }

        free(data->count_of_operators);
        free(data);
    }

    FILE* file_with_info_request = NULL;
    Request* request;
    Storage_of_applications storage;
    char* string = NULL;
    char* time = NULL;
    int priority;
    char* department_id = NULL;
    char* text = NULL;

    for (int i = 3; i < argc; i++)
    {
        file_with_info_request = fopen(argv[i], "r");
        if (!file_with_info_request)
        {
            printf("Error with opening file\n");
            return 1;
        }

        status_code st_request = create_request(string, request, file_with_info_request);
        if (st_request != OK)
        {
            print_errors(st_request);
        }

//        printf("%s\n", request->timestamp);
//        printf("%d\n", request->priority);
    }

    for (int i = 0; i < data->count_of_depatment; i++)
    {
        free(data->count_of_operators[i]);
    }

    free(data->count_of_operators);
    free(data);
    return 0;
}
