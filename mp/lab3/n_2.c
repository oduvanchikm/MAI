#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>

enum status_code
{
    OK,
    ERROR_WITH_MEMORY_ALLOCATION,
    INVALID_PARAMETER,
};

void print_errors(int error)
{
    switch(error)
    {
        case ERROR_WITH_MEMORY_ALLOCATION:
            printf("Error with memory allocation\n");
            break;

        case INVALID_PARAMETER:
            printf("This is invalid parameter\n");
            break;

        default:
            break;
    }
}

typedef struct
{
    int size;
    double *vector_coordinates;

} vector;

enum status_code inf_norm(vector *vector, int n, double *result)
{
    if (!vector)
    {
        return INVALID_PARAMETER;
    }

    *result = 0.0;
    double fabs_vector_value;

    for (int i = 0; i < n; i++)
    {
        if (!vector->vector_coordinates)
        {
            return INVALID_PARAMETER;
        }

        fabs_vector_value = fabs(vector->vector_coordinates[i]);
        if (fabs_vector_value > *result)
        {
            *result = fabs_vector_value;
        }
    }
    return OK;
}

enum status_code p_norm(vector *vector, int n, double *result, int p) 
{
    if (p < 1) 
    {
        return INVALID_PARAMETER;
    }

    double sum_vectors = 0.0;
    double tmp_result;

    for (int i = 0; i < n; i++) 
    {
        double fabs_vector_value = fabs(vector->vector_coordinates[i]);
        tmp_result = pow(fabs_vector_value, p);
        sum_vectors += tmp_result;
    }

    double sum_result;

    sum_result = pow(sum_vectors, 1.0 / p);
    *result = sum_result;

    return OK;
}

enum status_code create_identity_matrix(int n, double ***result)
{
    double **matrix = (double**)malloc(sizeof(double*) * n);

    if (!matrix)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    for (int i = 0; i < n; i++)
    {
        matrix[i] = (double*)malloc(sizeof(double) * n);

        if (!matrix[i])
        {
            return ERROR_WITH_MEMORY_ALLOCATION;
        }

        for (int j = 0; j < n; j++)
        {
            if (j == i)
            {
                matrix[i][j] = 1;
            }
            else
            {
                matrix[i][j] = 0;
            }
        }
    }
    *result = matrix;
    return OK;
}

enum status_code calculate_matrix_and_vector(double *vector, double **matrix, int n, double **result)
{
    *result = (double*)malloc(sizeof(double) * n);

    if (!*result)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    for (int i = 0; i < n; i++)
    {
        (*result)[i] = 0.0;

        for (int j = 0; j < n; j++)
        {
            (*result)[i] += matrix[i][j] * vector[j];
        }
    }
    return OK;
}

enum status_code marix_vector_norma(int n, vector *vector, int p, double *result)
{
    double **matrix;
    double *result_mult;

    enum status_code m = create_identity_matrix(n, &matrix);

    if (m == ERROR_WITH_MEMORY_ALLOCATION)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    enum status_code calculate = calculate_matrix_and_vector(vector->vector_coordinates, matrix, n, &result_mult);

    if (calculate == ERROR_WITH_MEMORY_ALLOCATION)
    {
        return ERROR_WITH_MEMORY_ALLOCATION;
    }

    for (int i = 0; i < n; i++)
    {
        *result += pow(result_mult[i] * result_mult[i], 1.0 / 2.0);
    }
    return OK;
}

// double find_max_value(double *result, int count)
// {
//     double max = result[0];
//     for (int i = 1; i < count; i++)
//     {
//         if (result[i] > max)
//         {
//             max = result[i];
//         }
//     }

//     return max;
// }

enum status_code the_longest_vector
(
    vector *max_vector, double *res,
    enum status_code (*inf_norm)(vector *vector, int n, double *result),
    enum status_code (*p_norm)(vector *vector, int n, double *result, int p),
    enum status_code (*marix_vector_norma)(int n, vector *vector, int p, double *result),
    int dimension, int p, int count_of_vectors, ...
)

{
    double eps = 0.0001;

    va_list(args);
    va_start(args, count_of_vectors);

    double max_res[3] = {INT_MIN, INT_MIN, INT_MIN};

    for (int i = 0; i < count_of_vectors; i++)
    {
        vector vectorr = va_arg(args, vector);

        double result[3];

        if (inf_norm(&vectorr, dimension, &result[0]) != OK)
        {
            return INVALID_PARAMETER;
        }

        if (p_norm(&vectorr, dimension, &result[1], p) != OK)
        {
            return INVALID_PARAMETER;
        }

        if (marix_vector_norma(dimension, &vectorr, p, &result[2]) != OK)
        {
            return ERROR_WITH_MEMORY_ALLOCATION;
        }

        for (int j = 0; j < 3; j++)
        {
            if (result[j] - max_res[j] > eps)
            {
                max_res[j] = result[j];
                max_vector[0] = vectorr;
            }

            else if (fabs(result[j] - max_res[j]) < eps)
            {
                max_vector[j++] = vectorr;
            }
        }
    }
    va_end(args);
    return OK;
}

void print_vector(vector vectors, int dimension)
{
    for (int i = 0; i < dimension; i++)
    {
        printf("%f ", vectors.vector_coordinates[i]);
    }
    printf("\n");
}

int main()
{
    int p = 1;
    int dimension = 3;

    vector vector1;
    vector1.vector_coordinates = (double*)malloc(sizeof(double) * dimension);
    vector1.vector_coordinates[0] = 1.0;
    vector1.vector_coordinates[1] = 0.5;
    vector1.vector_coordinates[2] = 7.7;

    vector vector2;
    vector2.vector_coordinates = (double*)malloc(sizeof(double) * dimension);
    vector2.vector_coordinates[0] = 6.0;
    vector2.vector_coordinates[1] = 2.0;
    vector2.vector_coordinates[2] = 8.1;

    vector vector3;
    vector3.vector_coordinates = (double*)malloc(sizeof(double) * dimension);
    vector3.vector_coordinates[0] = 1.0;
    vector3.vector_coordinates[1] = 4.0;
    vector3.vector_coordinates[2] = 8.0;

    double result[3]; 

    vector result_vector[3];  

    int count = 3;

    enum status_code st = the_longest_vector(result_vector, result, inf_norm, p_norm, marix_vector_norma, dimension, p, count, vector1, vector2, vector3);

    if (st != OK)
    {
        print_errors(st);
    }

    for (int i = 0; i < 3; i++)
    {
        printf("For norm %d the longest vector is:\n", i + 1);
        print_vector(result_vector[i], dimension);
        printf("Value: %lf\n", result[i]);
    }

    free(vector1.vector_coordinates);
    free(vector2.vector_coordinates);
    free(vector3.vector_coordinates);
    
    return 0;
}
