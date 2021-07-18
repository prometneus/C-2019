#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> 
#include "Header.h"
#include <locale.h>
#include <malloc.h> 

int main(void)
{
	int choice = 0, check = -15;
	printf("Menu:\n");
	printf("1. Filling in the database\n");
	printf("2. Adding an entry to the database\n");
	printf("3. Deleting an entry from the database\n");
	printf("4. Search the database\n");
	printf("5. Editing a database entry\n");
	printf("6. Sorting database data by the specified field\n");
	printf("7. Displaying the database\n");
	while (check != 1)
	{
		printf("Your choice:\t");
		if (scanf("%d", &choice) != 1)
		{
			printf("Wrong input");
		}
		switch (choice)
		{
		case 0:
		{
			check = 1;
			break;
		}
		case 1:
		{
			input();
			break;
		}
		case 2:
		{
			add();
			break;
		}
		case 3:
		{
			delete();
			break;
		}
		case 4:
		{
			search();
			break;
		}
		case 5:
		{
			edit();
			break;
		}
		case 6:
		{
			sort();
			break;
		}
		case 7:
		{
			display();
			break;
		}
		default:
		{
			printf("Error in choosing function in menu");
			break;
		}
		}
	}
	return 0;
}