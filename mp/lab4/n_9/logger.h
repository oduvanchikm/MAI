#ifndef LOGGER_H
#define LOGGER_H
//#include "main.h"
#include <time.h>
#include <stdio.h>

//typedef struct Time
//{
//    int year;
//    int mounth;
//    int day;
//    int hour;
//    int min;
//    int second;
//
//} Time;

typedef enum code_of_situation
{
    NEW_REQUEST,
    REQUEST_HANDLING_STARTED,
    REQUEST_HANDLING_FINISHED,
    DEPARTMENT_OVERLOADED

} code_of_situation;

//typedef struct Logger
//{
//    code_of_situation code;
//    char* id_departmeint;
//    int id_request;
//    char* name_op;
//    int time_treatment;
//
//} Logger;



#endif