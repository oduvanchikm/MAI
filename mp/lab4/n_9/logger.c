#include "logger.h"

//[<время возникновения ситуации в рамках модели в формате ISO 8601>] [<код ситуации>]: <описание>

char* format_time(time_t rawtime)
{
    struct tm* time_info = localtime(&rawtime);

    static char time_string[20];

    strftime(time_string, sizeof(time_string), "%Y-%m-%dT%H:%M:%S", time_info);

    return time_string;
}

void write_time_to_file(FILE* file)
{
    time_t rawtime;
    time(&rawtime);

    char* time_string = format_time(rawtime);

    fprintf(file, "%s\n", time_string);
}

//void logger(FILE* file, Logger* logger)
//{
//    switch(logger->code)
//    {
//        case NEW_REQUEST:
//
//    }
//}

int main()
{
    FILE* file = fopen("time.txt", "w");
    if (!file)
    {
        return 1;
    }

    write_time_to_file(file);
    printf("Текущее время было записано в файл current_time.txt\n");

    return 0;
}