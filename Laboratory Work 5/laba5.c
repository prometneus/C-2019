#include <stdio.h>
#include <malloc.h>
#include <math.h>

double* Array_enter(int* N)
{
	double* arr;
	printf("Enter the amount of elements: N=");
	scanf_s("%d", N);
	arr = (double*)malloc(*N * sizeof(double)); //Выделение памяти под массив
	for (int i = 0; i < *N; i++)
	{
		printf("arr[%d] = ", i);
		scanf_s("%lf", &arr[i]);
	}
	return arr;
}

void Array_output(double* arr, int N)
{
	for (int i = 0; i < N; i++)
	{
		printf("%.2lf\t", arr[i]);
	}
}

double Average_foundation(double* arr, int N)
{
	double average = 0, summ = 0;
	for (int i = 0; i < N; i++)
	{
		summ += arr[i];
	}
	average = summ / N;
	printf("\naverage = %lf\n\n", average);
	return average;
}

double* Delete(double* arr, int* N, double average) 
{
	int k = *N;
	for (int i = 0; i < k; i++) 
	{
		if (arr[i] > (1.5*average))
		{
			for (int j = i; j < k; j++) //Цикл по перезаписыванию массива.
			{
				arr[j] = arr[j + 1]; //Предыдущий элемент становится следующим.
			}
			i--; //Для еще одной проверки данного элемента.
			k--; //Счетчик количества элементов в новом массиве после удаления.
		}
	}
	arr = (double*)realloc(arr, k * sizeof(double)); //Перевыделение памяти под новое кол-во элементов.
    *N = k;
	return arr;
}

int main(void)
{
	int N = 0;
	double average;
	double* arr = NULL;
	arr = Array_enter(&N);
	if (N <= 0) 
	{
		printf("There is no elements in the array");
	}
	else 
	{
		Array_output(arr, N);
		average = Average_foundation(arr, N);
		arr = Delete(arr, &N, average);
		Array_output(arr, N);
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		free(arr); //Освобождение более неиспользуемой памяти.
	}
	return 0;
}
