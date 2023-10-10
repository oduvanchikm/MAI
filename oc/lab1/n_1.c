#include <stdio.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Error, enter the file name\n");
    }

    FILE* file = fopen(argv[1], "w");
    if (file == NULL)
	{
		printf("Cannot open the file\n");
		return 2;
	}

    
}