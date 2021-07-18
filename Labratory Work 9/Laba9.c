//База данных по цветам: название цветка, цвет, аромат (сильный или слабый), основные регионы распространения
/*Основной файл*/
#define _CRT_SECURE_NO_WARNINGS
#define filename "database.txt"

#include <stdio.h>
#include "Header.h"
#include <malloc.h>
#include <string.h>
#include <io.h>

void input() 
{
	int n = 0, check = 0;
	char d1[7] = "strong", d2[5] = "weak", d[7];
	char* str = (char*)malloc(10 * sizeof(char));
	flower fl;
	FILE* f = fopen(filename, "w");
	if (!f) 
	{
		printf("Error in creating file in input\n");
	}
	printf("Enter the amount of flowers to add:");
	if ((scanf("%d", &n) != 1) || (n <= 0)) 
	{
		printf("Wrong input\n");
		fclose(f);
	}
	for (int i = 0; i < n; i++)
	{
		fgets(str, 10, stdin);
		printf("Enter the appelation of the flower %d:", i + 1);
		gets(fl.name);

		printf("Enter the colour of the flower %d:", i + 1);
		gets(fl.colour);

		printf("Enter the main regions of distribution of flower %d:", i + 1);
		gets(fl.placement);
		check = 0;
		while (check != 1)
		{
			printf("Enter the smell of the flower %d (strong or weak):", i + 1);
			scanf("%s", d);
			if ((strcmp(d, d1) == 0) || (strcmp(d, d2) == 0))
			{
				check = 1;
				strcpy(fl.smell, d);
			}
			else
			{
				printf("Wrong input. Enter again\n");
			}
		}

		fwrite(&fl, (sizeof(flower)), 1, f);
	}
	printf("Successfully created\n");
	fclose(f);
	free(str);
}

void add() 
{
	int n = 0, check = 0;
	char d1[7] = "strong", d2[5] = "weak", d[7];
	char* str = (char*)malloc(10 * sizeof(char));
	flower fl;
	FILE* f = fopen(filename, "a");
	if (!f) 
	{
		printf("Error in creating file in add function\n");
	}

	printf("Enter the amount of flowers to add:");
	if ((scanf("%d", &n) != 1) || (n <= 0))
	{
		printf("Wrong input\n");
		fclose(f);
	}

	for (int i = 0; i < n; i++)
	{
		fgets(str, 10, stdin);
		printf("Enter the appelation of the flower %d:", i + 1);
		gets(fl.name);

		printf("Enter the colour of the flower %d:", i + 1);
		gets(fl.colour);

		printf("Enter the main regions of distribution of flower %d:", i + 1);
		gets(fl.placement);

		check = 0;
		while (check != 1)
		{
			printf("Enter the smell of the flower %d (strong or weak):", i + 1);
			scanf("%s", d);
			if ((strcmp(d, d1) == 0) || (strcmp(d, d2) == 0))
			{
				check = 1;
				strcpy(fl.smell, d);
			}
			else
			{
				printf("Wrong input. Enter again\n");
			}
		}
		fwrite(&fl, (sizeof(flower)), 1, f);
	}
	printf("Successfully added\n");
	fclose(f);
}

void delete() 
{
	int index, size;
	flower fl;
	FILE* f = fopen(filename, "r+");
	if (!f)
	{
		printf("Error in creating file in delete function\n");
	}
	printf("Enter the number of flower that needs to delete:\t");
	if (scanf("%d", &index) != 1) 
	{
		printf("Input error - it is not a number\n");
		fclose(f);
	}
	fseek(f, 0, SEEK_END);//ftell вернет значение указателя на текущем положении каретки в потоке  
	size = ftell(f) / sizeof(flower);//Подсчет количества записей в базе данных
	while (index <= 0 || index > size) 
	{
		printf("There is no flower with this index. Enter again:");
		if (scanf("%d", &index) != 1); 
		{
			printf("Input error - it is not a number\n");
			fclose(f);
		}
	}
	for (int i = index - 1; i < size - 1; i++) //Помещаем каретку перед элементом, который надо удалить
	{
		fseek(f, (i + 1) * sizeof(flower), SEEK_SET);
		fread(&fl, sizeof(flower), 1, f); //Считывание следующего элемента
		fseek(f, i * sizeof(flower), SEEK_SET); //Возврат назад
		fwrite(&fl, sizeof(flower), 1, f); //Перезапись следующуго элемента вместо текущего
	}
	_chsize(_fileno(f), (size - 1) * sizeof(flower)); //Уменьшение размера файла
	printf("Flower deleted\n");
	fclose(f);
}

void search() 
{
	FILE* f = fopen(filename, "r+");
	flower fl;
	int check = 0, choice = 0, j = 0;
	char str[50];
	char* str1 = (char*)malloc(10 * sizeof(char));
	if (!f) 
	{
		printf("Error in creating file in search\n");
	}
	printf("What field do you want to search for?\n");
	printf("1 -  appelation\n");
	printf("2 -  colour\n");
	printf("3 -  smell\n");
	printf("4 -  regions of destribution\n");
	printf("Enter your choice:\t");
	if (scanf("%d", &choice) != 1) 
	{
		printf("Input error - it is not a number\n");
		fclose(f);
	}
	switch(choice)
	{
	case 1: 
	{
		fgets(str1, 10, stdin);
		printf("Enter the appelation of the flower:\t");
		gets(str);
		printf("Matches found:\n");
		printf("______________________________________________________________________________\n");
		printf("|   |                      |               |         |                        |\n");
		printf("| № |     Appelation       |     Colour    |  Smell  |        Placement       |\n");
		printf("|___|______________________|_______________|_________|________________________|\n");

		while (!feof(f)) 
		{
			fread(&fl, (sizeof(flower)), 1, f);
			if (!feof(f) && !strcmp(fl.name, str)) //Если нашлось совпадение
			{

				printf("|%-3d|%-22s|%-15s|%-9s|%-24s|\n", j+1, fl.name, fl.colour, fl.smell, fl.placement);
				j++;
				check = 1;
			}
		}
		if (check == 0)
		{
			printf("No matches found\n");
		}
		printf("|___|______________________|_______________|_________|________________________|\n");
		printf("\n");
		break;
	}
	case 2: 
	{
		fgets(str1, 10, stdin);
		printf("Enter the colour of the flower:\t");
		gets(str);
		printf("Matches found:\n");
		printf("______________________________________________________________________________\n");
		printf("|   |                      |               |         |                        |\n");
		printf("| № |     Appelation       |     Colour    |  Smell  |        Placement       |\n");
		printf("|___|______________________|_______________|_________|________________________|\n");
		while (!feof(f))
		{
			fread(&fl, (sizeof(flower)), 1, f);
			if (!feof(f) && !strcmp(fl.colour, str)) //Если нашлось совпадение
			{
				printf("|%-3d|%-22s|%-15s|%-9s|%-24s|\n", j + 1, fl.name, fl.colour, fl.smell, fl.placement);
				j++;
				check = 1;
			}
		}
		if (check == 0)
		{
			printf("No matches found\n");
			break;
		}
		printf("|___|______________________|_______________|_________|________________________|\n");
		printf("\n");
		break;
	}
	case 3: 
	{
		fgets(str1, 10, stdin);
		printf("Enter the smell of the flower (strong or weak):");
		gets(str);
		check = 1;
		printf("Matches found:\n");
		printf("______________________________________________________________________________\n");
		printf("|   |                      |               |         |                        |\n");
		printf("| № |     Appelation       |     Colour    |  Smell  |        Placement       |\n");
		printf("|___|______________________|_______________|_________|________________________|\n");
		while (!feof(f))
		{
			fread(&fl, (sizeof(flower)), 1, f);
			if (!feof(f) && !strcmp(fl.smell, str)) //Если нашлось совпадение
			{
				printf("|%-3d|%-22s|%-15s|%-9s|%-24s|\n", j + 1, fl.name, fl.colour, fl.smell, fl.placement);
				j++;
				check = 1;
			}
		}
		if (check == 0)
		{
			printf("No matches found\n");
			break;
		}
		printf("|___|______________________|_______________|_________|________________________|\n");
		printf("\n");
		break;
	}
	case 4: 
	{
		fgets(str1, 10, stdin);
		printf("Enter the main regions of destribution:\t");
		gets(str);
		printf("Matches found:\n");
		printf("______________________________________________________________________________\n");
		printf("|   |                      |               |         |                        |\n");
		printf("| № |     Appelation       |     Colour    |  Smell  |        Placement       |\n");
		printf("|___|______________________|_______________|_________|________________________|\n");
		while (!feof(f))
		{
			fread(&fl, (sizeof(flower)), 1, f);
			if (!feof(f) && !strcmp(fl.placement, str)) //Если нашлось совпадение
			{
				printf("|%-3d|%-22s|%-15s|%-9s|%-24s|\n", j + 1, fl.name, fl.colour, fl.smell, fl.placement);
				j++;
				check = 1;
			}
		}
		if (check == 0)
		{
			printf("No matches found\n");
			break;
		}
		printf("|___|______________________|_______________|_________|________________________|\n");
		printf("\n");
		break;
	}
	default: 
	{
	printf("There is no such a field"); 
	fclose(f);
	}
	}
}

void edit()
{
	flower fl;
	FILE* f = fopen(filename, "r+");
	int index, choice, size;
	if (!f)
	{
		printf("Error in creating file in edit\n");
	}
	printf("Enter the number of the flower need to edit:\t");
	if (scanf("%d", &index) != 1)
	{
		printf("Input error - it is not a number\n");
		fclose(f);
	}
	fseek(f, 0, SEEK_END);
	size = ftell(f) / sizeof(flower);//Подсчет количества записей в базе данных
	while (index <= 0 || index > size)
	{
		printf("There is no flower with this index. Enter again:");
		if (scanf("%d", &index) != 1);
		{
			printf("Input error - it is not a number\n");
			fclose(f);
		}
	}
	printf("What field do you want to edit?\n");
	printf("1 -  appelation\n");
	printf("2 -  colour\n");
	printf("3 -  smell\n");
	printf("4 -  regions of destribution\n");
	printf("Enter your choice:");
	if (scanf("%d", &choice) != 1)
	{
		printf("Input error - it is not a number\n");
		fclose(f);
	}
	fseek(f, (index - 1) * sizeof(flower), SEEK_SET);
	fread(&fl, 1, sizeof(flower), f);
	rewind(stdin);
	switch (choice)
	{
	case 1:
	{
		printf("Enter new appelation:");
		gets(fl.name);
		printf("Successfully changed\n");
		break;
	}
	case 2:
	{
		printf("Enter new colour:");
		gets(fl.colour);
		printf("Successfully changed\n");
		break;
	}
	case 3:
	{
		int check = 0;
		char d1[7] = "strong", d2[5] = "weak", d[7];
		check = 0;
		while (check != 1)
		{
			printf("Enter the smell of the flower (strong or weak):");
			scanf("%s", d);
			if ((strcmp(d, d1) == 0) || (strcmp(d, d2) == 0))
			{
				check = 1;
				strcpy(fl.smell, d);
			}
			else
			{
				printf("Wrong input. Enter again\n");
			}
		}
		strcpy(fl.smell, d);
		printf("Successfully changed\n");
		break;
	}
	case 4:
	{
		printf("Enter new regions:");
		gets(fl.placement);
		printf("Successfully changed\n");
		break;
	}
	default:
	{
		printf("There is no such a field\n");
		fclose(f);
	}
	}
	fseek(f, (index - 1) * sizeof(flower), SEEK_SET);
	fwrite(&fl, (sizeof(flower)), 1, f);
	fclose(f);
}

void sort() 
{
	FILE* f = fopen(filename, "r+b");
	int size, choice;
	fseek(f, 0, SEEK_END);
	size = ftell(f) / sizeof(flower);
	fseek(f, 0, SEEK_SET);
	flower* fl = (flower*)malloc(size * sizeof(flower));//Массив структур
	flower tmp;
	if (!f)
	{
		printf("Error in creating file in sort\n");
	}
	for (int i = 0; i < size; i++) 
	{
		fread(&fl[i], (sizeof(flower)), 1, f);
	}
	printf("What field do you want to sort by?\n");
	printf("1 -  appelation\n");
	printf("2 -  colour\n");
	printf("3 -  smell\n");
	printf("4 -  regions of destribution\n");
	printf("Enter your choice:");
	if (scanf("%d", &choice) != 1)
	{
		printf("Input error - it is not a number\n");
		fclose(f);
	}
	switch (choice)
	{
	case 1:
	{
		for (int i = size - 1; i >= 0; i--)
		{
			for (int j = 0; j < i; j++)
			{
				if (strcmp(fl[j].name, fl[j + 1].name) > 0)
				{
					tmp = fl[j];
					fl[j] = fl[j + 1];
					fl[j + 1] = tmp;
				}
			}
		}
		break;
	}
	case 2:
	{
		for (int i = size - 1; i > 0; i--)
		{
			for (int j = 0; j < i; j++)
			{
				if (strcmp(fl[j].colour, fl[j + 1].colour) > 0)
				{
					tmp = fl[j];
					fl[j] = fl[j + 1];
					fl[j + 1] = tmp;
				}
			}
		}
		break;
	}
	case 3:
	{
		for (int i = size - 1; i > 0; i--)
		{
			for (int j = 0; j < i; j++)
			{
				if (strcmp(fl[j].smell, fl[j + 1].smell) > 0)
				{
					tmp = fl[j];
					fl[j] = fl[j + 1];
					fl[j + 1] = tmp;
				}
			}
		}
		break;
	}
	case 4:
	{
		for (int i = size - 1; i > 0; i--)
		{
			for (int j = 0; j < i; j++)
			{
				if (strcmp(fl[j].placement, fl[j + 1].placement) > 0)
				{
					tmp = fl[j];
					fl[j] = fl[j + 1];
					fl[j + 1] = tmp;
				}
			}
		}
		break;
	}
	default:
	{
		printf("There is no such a field");
		fclose(f);
		break;
	}
	}
	fseek(f, 0, SEEK_SET);
	for (int i = 0; i < size; i++) //Запись в файл отсортированный массив структур
	{
		fwrite(&fl[i], sizeof(flower), 1, f);
	}
	free(fl);//Освобождаем массив структур
	printf("Successfully sorted\n");
	fclose(f);
}

void display() 
{
	flower fl;
	FILE* f = fopen(filename, "r");
	int j = 0;
	if (!f)
	{
		printf("Error in creating file in sort\n");
	}
	printf("Database:\n\n");
	printf("______________________________________________________________________________\n");
	printf("|   |                      |               |         |                        |\n");
	printf("| № |     Appelation       |     Colour    |  Smell  |        Placement       |\n");
	printf("|___|______________________|_______________|_________|________________________|\n");
	while (!feof(f)) 
	{
		fread(&fl, (sizeof(flower)), 1, f);
		if (!feof(f)) 
		{
			printf("|%-3d|%-22s|%-15s|%-9s|%-24s|\n", j + 1, fl.name, fl.colour, fl.smell, fl.placement);
			j++;
		}
	}
	printf("|___|______________________|_______________|_________|________________________|\n");
	printf("\n");
	fclose(f);
}