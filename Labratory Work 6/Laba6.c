#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>

int **matrix_creating(int* m, int* n) 
{
	int** arr;
	printf("Enter the amount of rows,m=");
	scanf_s("%d", m);
	printf("Enter the amount of columns, n=");
	scanf_s("%d", n);
	arr = (int**)malloc(*m * sizeof(int*));//Выделение памяти по строкам.

	for (int i = 0; i < *m; i++) 
	{
		arr[i] = (int*)malloc(*n * sizeof(int*));//Выделение памяти по столбцам.

		for (int j = 0; j < *n; j++) 
		{
			printf("Enter the member of an array a[%d][%d]=", i, j);
			scanf_s("%d", &arr[i][j]);
		}
	}
	return arr;
}

void matrix_display(int **arr, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d\t", arr[i][j]);
		}
		printf("\n");
	}
}

double minimum_determination(int** arr, int m, int n) 
{
	int min = arr[0][0];
	double average = 0, summ = 0;
	for (int i = 0; i < m; i++)
	{
		int min = fabs(arr[i][0]);
		for (int j = 0; j < n; j++)
		{
			if (fabs(arr[i][j]) <= fabs(min)) 
			{
				min = arr[i][j];
			}
		}
		summ += min;
	}
	average = summ / m;
	printf("Average = %.3lf", average);
	return average;
}

void make_array_free_again(int** arr, int m) //Функция для освобождения ранее занятой массивом памяти.
{
	for (int i = 0; i < m; i++)
	{
		free(arr[i]);
	}
	free(arr);
}

int main(void) 
{
	int** arr, m, n;
	double average;
	arr = matrix_creating(&m, &n);
	matrix_display(arr, m, n);
	if (m <= 0 || n <= 0) 
	{
		printf("There is no elements in array");
	}
	else {average = minimum_determination(arr, m, n);}
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	make_array_free_again(arr, m);
	return 0;
}
