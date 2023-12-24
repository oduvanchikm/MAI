#include "lab.h"

void overfprintf(FILE *file, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    int index = 0;

    while (format[index] != '\0')
    {
        if (format[index] != '%')
        {
            fprintf(file, "%c", format[index]);
            index++;
        }
        else
        {
            int next_index = index + 1;

            if (format[next_index] == '%')
            {
                fprintf(file, "%c", '%');
                index = next_index + 1;
            }
            else
            {
                char flag[25];
                int flag_index = 0;
                flag[flag_index++] = '%';

                while (format[next_index] != '\0' && (isalnum(format[next_index])) || format[next_index] == '.')
                {
                    char c = format[next_index];
                    flag[flag_index] = c;
                    next_index++;
                    flag_index++;
                }

                flag[flag_index] = '\0';

                if (strcmp(flag, "%Ro") == 0)
                {
                    char* roman_result = NULL;
                    int arg = va_arg(args, int);
                    status_code st_roman = roman_digits_flag(arg, &roman_result);
                    if (st_roman == OK)
                    {
                        fprintf(file, "%s", roman_result);
                    }
                    else
                    {
                        print_errors(st_roman);
                    }
                    free(roman_result);
                }

                else if (strcmp(flag, "%Zr") == 0)
                 {
                     char* zeck_result = NULL;
                     unsigned int arg = va_arg(args, unsigned int);
                     status_code st_zc = zecedorf_representation(arg, &zeck_result);
                     if (st_zc == OK)
                     {
                         fprintf(file, "%s", zeck_result);
                     }
                     else
                     {
                         print_errors(st_zc);
                     }
                     free(zeck_result);
                 }

                else if (strcmp(flag, "%Cv") == 0)
                {
                    char* Cv_result = NULL;
                    int arg = va_arg(args, int);
                    int system = va_arg(args, int);
                    status_code Cv_st = decemal_to_other_base_l(&Cv_result, arg, system);

                    if (Cv_st == OK)
                    {
                        fprintf(file, "%s", Cv_result);
                    }

                    else
                    {
                        print_errors(Cv_st);
                    }
                    free(Cv_result);
                }

                else if (strcmp(flag, "%CV") == 0)
                {
                    char* CV_result = NULL;
                    int arg = va_arg(args, int);
                    int system = va_arg(args, int);
                    status_code CV_st = decemal_to_other_base_h(&CV_result, arg, system);

                    if (CV_st == OK)
                    {
                        fprintf(file, "%s", CV_result);
                    }
                    else
                    {
                        print_errors(CV_st);
                    }
                    free(CV_result);
                }

                else if (strcmp(flag, "%to") == 0)
                {
                    char* arg = va_arg(args, char*);
                    int system = va_arg(args, int);
                    int to_st = other_base_to_ten_l(arg, system);
                    fprintf(file, "%d", to_st);
                }

                else if (strcmp(flag, "%TO") == 0)
                {
                    char* arg = va_arg(args, char*);
                    int system = va_arg(args, int);
                    int TO_st = other_base_to_ten_h(arg, system);
                    fprintf(file, "%d", TO_st);
                }

                else if (strcmp(flag, "%mi") == 0)
                {
                    char *mi_result = NULL;
                    int arg = va_arg(args, int);
                    status_code mi_st = print_dump_memory(&mi_result, &arg, sizeof(arg));

                    if (mi_st == OK)
                    {
                        fprintf(file, "%s", mi_result);
                    }
                    else
                    {
                        print_errors(mi_st);
                    }
                    free(mi_result);
                }

                else if (strcmp(flag, "%mu") == 0)
                {
                    char *mu_result = NULL;
                    unsigned int arg = va_arg(args, unsigned int);
                    status_code mu_st = print_dump_memory(&mu_result, &arg, sizeof(arg));

                    if (mu_st == OK)
                    {
                        fprintf(file, "%s", mu_result);
                    }
                    else
                    {
                        print_errors(mu_st);
                    }
                    free(mu_result);
                }

                else if (strcmp(flag, "%md") == 0)
                {
                    char *md_result = NULL;
                    double arg = va_arg(args, double);
                    status_code md_st = print_dump_memory(&md_result, &arg, sizeof(arg));

                    if (md_st == OK)
                    {
                        fprintf(file, "%s", md_result);
                    }
                    else
                    {
                        print_errors(md_st);
                    }
                    free(md_result);
                }

                else if (strcmp(flag, "%mf") == 0)
                {
                    char *mf_result = NULL;
                    float arg = va_arg(args, double);
                    status_code mf_st = print_dump_memory(&mf_result, &arg, sizeof(arg));

                    if (mf_st == OK)
                    {
                        fprintf(file, "%s", mf_result);
                    }
                    else
                    {
                        print_errors(mf_st);
                    }
                    free(mf_result);
                }

                else
                {
                    if (strcmp(flag, "%n") == 0)
                    {
                        int *n_ptr = va_arg(args, int*);

                        *n_ptr = ftell(file);
                    }
                    else
                    {
                        vfprintf(file, flag, args);
                    }
                }
                index = next_index;
            }
        }
    }
    index++;
    va_end(args);
}

void oversprintf(char *buffer, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    int index = 0;
    int buffer_index = 0;

    char* zeck_result = NULL;
    char* Cv_result = NULL;
    char* CV_result = NULL;
    char* mi_result = NULL;
    char* mu_result = NULL;
    char* md_result = NULL;
    char* mf_result = NULL;

    int value = 0;

    while (format[index] != '\0')
    {
        if (format[index] != '%')
        {
            buffer[buffer_index] = format[index];
            buffer_index++;
            index++;
        }
        else
        {
            int g = 0;
            int next_index = index + 1;
            if (format[next_index] == '%')
            {
                sprintf(&(buffer[buffer_index]), "%c", '%');
                g = next_index + 1;
                buffer_index++;
            }
            else
            {
                next_index = index;
                char flag[25];
                int flag_index = 0;
                flag[flag_index++] = '%';
                next_index++;
                while (format[next_index] != '\0' && (isalnum(format[next_index])))
                {
                    flag[flag_index++] = format[next_index++];
                }

                flag[flag_index] = '\0';
                if (strcmp(flag, "%Ro") == 0)
                {
                    char* roman_result = NULL;
                    int arg = va_arg(args, int);
                    status_code st_roman = roman_digits_flag(arg, &roman_result);
                    if (st_roman == OK)
                    {
                        sprintf((buffer + buffer_index), "%s", roman_result);
                        buffer_index += strlen(roman_result);
                    }
                    else
                    {
                        print_errors(st_roman);
                    }
                    free(roman_result);
                }

                else if (strcmp(flag, "%Zr") == 0)
                {
                    unsigned int arg = va_arg(args, unsigned int);
                    status_code st_zc = zecedorf_representation(arg, &zeck_result);
                    if (st_zc == OK)
                    {
                        printf("%d\n", buffer_index);
                        sprintf((buffer + buffer_index), "%s", zeck_result);
                        buffer_index += strlen(zeck_result);
                    }
                    else
                    {
                        print_errors(st_zc);
                    }
                    free(zeck_result);
                }

                else if (strcmp(flag, "%Cv") == 0)
                {
                    int arg = va_arg(args, int);
                    int system = va_arg(args, int);
                    status_code Cv_st = decemal_to_other_base_l(&Cv_result, arg, system);

                    if (Cv_st == OK)
                    {
                        sprintf((buffer + buffer_index), "%s", Cv_result);
                        buffer_index += strlen(Cv_result);
                    }

                    else
                    {
                        print_errors(Cv_st);
                    }
                    free(Cv_result);
                }

                else if (strcmp(flag, "%CV") == 0)
                {
                    int arg = va_arg(args, int);
                    int system = va_arg(args, int);
                    status_code CV_st = decemal_to_other_base_l(&CV_result, arg, system);

                    if (CV_st == OK)
                    {
                        sprintf(&(buffer[buffer_index]), "%s", CV_result);
                        buffer_index += strlen(CV_result);
                    }
                    else
                    {
                        print_errors(CV_st);
                    }
                    free(CV_result);
                }

                else if (strcmp(flag, "%to") == 0)
                {
                    char* arg = va_arg(args, char*);
                    int system = va_arg(args, int);
                    int to_st = other_base_to_ten_l(arg, system);
                    buffer_index += sprintf(&(buffer[buffer_index]), "%d", to_st);;
                }

                else if (strcmp(flag, "%TO") == 0)
                {
                    char* arg = va_arg(args, char*);
                    int system = va_arg(args, int);
                    int TO_st = other_base_to_ten_h(arg, system);
                    buffer_index += (sprintf(&(buffer[buffer_index]), "%d", TO_st));
                }

                else if (strcmp(flag, "%mi") == 0)
                {
                    int arg = va_arg(args, int);
                    status_code mi_st = print_dump_memory(&mi_result, &arg, sizeof(arg));

                    if (mi_st == OK)
                    {
                        sprintf(&(buffer[buffer_index]), "%s", mi_result);
                        buffer_index += strlen(mi_result);
                    }
                    else
                    {
                        print_errors(mi_st);
                    }
                    free(mi_result);
                }

                else if (strcmp(flag, "%mu") == 0)
                {
                    unsigned int arg = va_arg(args, unsigned int);
                    status_code mu_st = print_dump_memory(&mu_result, &arg, sizeof(arg));

                    if (mu_st == OK)
                    {
                        sprintf(&(buffer[buffer_index]), "%s", mu_result);
                        buffer_index += strlen(mu_result);
                    }
                    else
                    {
                        print_errors(mu_st);
                    }
                    free(mu_result);
                }

                else if (strcmp(flag, "%md") == 0)
                {
                    double arg = va_arg(args, double);
                    status_code md_st = print_dump_memory(&md_result, &arg, sizeof(arg));

                    if (md_st == OK)
                    {
                        sprintf(&(buffer[buffer_index]), "%s", md_result);
                        buffer_index += strlen(md_result);
                    }
                    else
                    {
                        print_errors(md_st);
                    }
                    free(md_result);
                }

                else if (strcmp(flag, "%mf") == 0)
                {
                    float arg = va_arg(args, double);
                    status_code mf_st = print_dump_memory(&mf_result, &arg, sizeof(arg));

                    if (mf_st == OK)
                    {
                        sprintf(&(buffer[buffer_index]), "%s", mf_result);
                        buffer_index += strlen(mf_result);
                    }
                    else
                    {
                        print_errors(mf_st);
                    }
                    free(mf_result);
                }

                else
                {
                    if (strcmp(flag, "%n") == 0)
                    {
                        int *n_ptr = va_arg(args, int*);
                        *n_ptr = index;
                    }
                    else
                    {
                       buffer_index += vsprintf(buffer + buffer_index, flag, args);
                    }
                }
                index = next_index;
            }
        }

    }
    va_end(args);
    buffer[buffer_index] = '\0';
}