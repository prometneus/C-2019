#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define N 100

int menu() 
{
	int a;
	printf("Choose the task (1 or 2):\t");
	scanf_s("%d", &a);
	return a;
}

double createA(char* name) 
{
	int n;
	double a;
	FILE* f;
	printf("enter the amount of numbers in file n=\t");
	scanf_s("%d", &n);
	if (((f = fopen(name, "w"))) == NULL)// Открытие на создание
	{
		printf("Error in opening f in createA\n");
		return -3;
	}
	for (int i = 0; i < n; i++)//Запись в файл
	{
		printf("x=\t");
		scanf_s("%lf", &a);
		fwrite(&a, (sizeof(double)), 1, f);
	}
	fclose(f);// закрытие
	return n;
}

int funkA(char* name)
{
	double average = 0, summ = 0, a;
	int index = 0, pos = 0, n = 0;
	FILE* f;
	if ((f = fopen(name, "r+")) == NULL)
	{
		printf("Error in opening f in funkA\n");
		return -3;
	}
	while (!feof(f))
	{
		if (!feof(f))
		{
			if (fread(&a, (sizeof(double)), 1, f))//Если считывается новый элемент
			{
				if (a > 0) pos++;
				summ += a; n++;
			}
		}
	}
	average = summ / n;
	if (pos == 0)
	{
		printf("average is %lf\n", average);
		fseek(f, 0, SEEK_END);
		fwrite(&average, (sizeof(double)), 1, f);
	}
	else 
	{
		fseek(f, 0, SEEK_SET);
		while(!feof(f))
		{
			fread(&a, (sizeof(double)), 1, f);
			if (a > 0) break;
			else index++;
		}
		printf("index = %d\naverage = %lf\n", index, average);
		for (int i = n; i > index; i--)
		{
			fseek(f, ((i - 1) * sizeof(double)), SEEK_SET);//К последнему (не сдвинутому) элементу
			fread(&a, (sizeof(double)), 1, f);//Считывание
			fseek(f, ((i - 1) * sizeof(double)), SEEK_SET);//К последнему (не сдвинутому) элементу
			fseek(f, (sizeof(double)), SEEK_CUR);//Сдвиг с текущего на double
			fwrite(&a, (sizeof(double)), 1, f);//Перезапись элемента
			fflush(f);//Сброс буфера
		}
		fseek(f, (index * sizeof(double)), SEEK_SET);
		fwrite(&average, (sizeof(double)), 1, f);
	}
	fclose(f);
	return 0;
}

int displayA(char* name)
{
	double a;
	FILE* f;
	if ((f = fopen(name, "r")) == NULL)
	{
		printf("Error in opening f in displayA\n");
		return -3;
	}
	while (!feof(f)) //Вывод содержимого файла на экран
	{
		fread(&a, (sizeof(double)), 1, f);
		if (!feof(f)) printf("%lf", a);
	}
	fclose(f);
	return 0;
}

char createB(char* name)
{
	{
		FILE* S1;
		int n = 0;
		char* str = (char*)malloc(N * sizeof(char));//Буфер для ввода строки
		if ((S1 = fopen(name, "w")) == NULL)
		{
			printf("Error in opening S1 in createB\n");
			return -3;
		}
		else
		{
			if (str != 0) fgets(str, N, stdin);
			printf("Amount of strings to enter:\t");
			scanf("%d", &n);
			if (str != 0) fgets(str, N, stdin);
			for (int i = 0; i < n; i++) 
			{
				printf("Enter string %d:\t", i+1);
				gets(str, N, stdin);//Считывание с потока ввода
				fputs(str, S1);//Запись
				fputs("\n", S1);
			}
		}
		fclose(S1);
	}
	return 0;
}

int funkB(char* name, char* vorname)
{
	FILE* S1;
	FILE* S2;
	char a;
	if ((S1 = fopen(name, "r")) == NULL)
	{
		printf("\nError in opening S1 in funkB\n");
		return -3;
	}
	if ((S2 = fopen(vorname, "w")) == NULL)
	{
		printf("\nError in opening S2 in funkB\n");
		return -3;
	}
	while (!feof(S1) && !feof(S2))
	{
		if (!feof(S1) && !feof(S2))
		{
			if (fread(&a, (sizeof(char)), 1, S1))
			{
				if (a == '{') { fwrite("begin", (sizeof(char)), 5, S2); }
				else if (a == '=') { fwrite(":=", (sizeof(char)), 2, S2); }
				else if (a == '}') { fwrite("end", (sizeof(char)), 3, S2); }
				else fwrite(&a, (sizeof(char)), 1, S2);
			}
		}
	}
	fclose(S1);
	fclose(S2);
	return 0;
}

int displayB1(char* name) 
{
	FILE* S1;
	int a;
	if ((S1 = fopen(name, "r")) == NULL) 
	{
		printf("Error in opening S1 in displayB1\n");
		return -3;
	}
	printf("\nOld file was:\n");
	while (!feof(S1)) 
	{
		fread(&a, (sizeof(char)), 1, S1);
		if (!feof(S1)) printf("%c", a);
	}
	return 0;
}

int displayB2(char* vorname) 
{
	FILE* S2;
	int a;
	if ((S2 = fopen(vorname, "r"))==NULL)
	{
		printf("Error in opening S2 in displayB2\n");
		return -3;
	}
	printf("\nNew file:\n");
	while (!feof(S2))
	{
		fread(&a, (sizeof(char)), 1, S2);
		if (!feof(S2)) printf("%c", a);
	}
	return 0;
}

int main(void) 
{
	int w = menu();
	switch (w) 
	{
	case 1: 
	{
		char f[] = "C:/Users/ДОМАШНИЙ/Desktop/Программирование/f.txt";//Указание точного пути, где будет создаваться файл в процессе выполнения программы.
		int n = createA(f);
		if (n == 0) { printf("File is empty"); break; }
		else 
		{
			funkA(f);
			displayA(f);
			break;
		}
	}
	case 2: 
	{
		char S1[] = "C:/Users/ДОМАШНИЙ/Desktop/Программирование/S1.txt";
		char S2[] = "C:/Users/ДОМАШНИЙ/Desktop/Программирование/S2.txt";
		//createB(S1);
		funkB(S1, S2);
		displayB1(S1);
		displayB2(S2);
	}
	}
	return 0;
}