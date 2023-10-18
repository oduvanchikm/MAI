#include <stdio.h>
#include <stdlib.h>

typedef struct // информация о пользователе 
{
    char login[7];
    int PIN;
} Users;

void welcome_print()
{
    printf("____________________________________________________________________________\n");
    printf(" \t\t\t\t| Welcome! |\n");
    printf("____________________________________________________________________________\n");
    printf("You can register or log in the system\n");
    printf("Enter 'R' to register, 'L' to log in, 'E' to exit\n");
}

void choice_function(char *choice)
{
    do {

        if (choice != 'R' && choice != 'r' && choice != 'L' && choice != 'l' && choice != 'E' && choice != 'e') {
            printf("Invalid input! Please enter 'R', 'L', or 'E'\n");
        }
    } while (choice != 'R' && choice != 'r' && choice != 'L' && choice != 'l' && choice != 'E' && choice != 'e');
}


int main()
{
    char choice;
    scanf("%c", &choice);
    welcome_print();
    choice_function(choice);

    if (choice == 'R' && choice == 'r')
    {
        printf("Please enter your login: \n");
    }

    return 0;
}