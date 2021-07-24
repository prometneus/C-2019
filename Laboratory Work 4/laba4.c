#include <stdio.h>

int array_enter(double *arr) {
	int k;
	printf("Enter the amount of members in array, k=");
	scanf_s("%d", &k);
		for (int i = 0; i < k; i++)
		{
			printf("Enter the member of array, a%d=\t", i);
			scanf_s("%lf", &arr[i]);
		}
	return k;
}

void array_display(double *arr, int k) {
	for (int i=0; i<k; i++)
	{
		printf("%lf\t", arr[i]);
	}
}

void maximum_determination(double* arr, int k, float Y) {
	int b = 0;
	double min = arr[0];
	for (int i = 0; i < k; i++) 
	{
		if (arr[i] <= min) 
		{
			min = arr[i];
		}
	}
	double max = min; //Определение минимума, который нужно приравнять его к максимуму, чтобы он гарантированно изменился.
	for (int i = 0; i < k; i++)
	{
		if (arr[i] < Y)
		{
			if (arr[i] >= max)
			{
				max = arr[i];
			}
		}
		else b++; //Определение количества непроходов.
	}
	if (b == k) //Если кол-во непроходов == кол-ву элементов, то все элементы не удовлетворяют условию <Y, а значит max отсутствует.
	{
		printf("Impossible to find maximum");
	}
	else printf("\n\nmaximum = %lf\n", max);
}


double minimum_determination(double* arr, int k, float Y) {
	double min = arr[0], nomer = 0;
	for (int i = 0; i < k; i++) 
	{
		if (arr[i] <= min)
		{
			nomer = i;
			min = arr[i];
		}
	}
	return nomer; //Возврат количества элементов до последнего минимума.
}

double arithmetic_mean(double *arr, int k, float Y, double nomer) {
	double summ=0, average = 0;
	for (int i = 0; i < nomer; i++)
	{
		summ += arr[i];
	}
	average = summ / nomer;
	if (nomer == 0)
	{
		printf("\nImpossible to find average\n");
	}
	else printf("\nArithmetic mean is =%lf\n", average);
	return average;
}

int main(void)
{
	int k = 0;
	float Y;
	double arr[100], average, min = 0, nomer;

	printf("Enter the upper limit for members, Y=");
	scanf_s("%f", &Y);

	k = array_enter(&arr);
	array_display(arr, k);
	if (k <= 0) //Если количество элементов равно 0 или меньше, программа не должна выполняться.
	{
		printf("There is no elements in the array - impossible to find either maximum or average\n\n\n\n\n");
	}
	else
	{
		nomer = minimum_determination(arr, k, Y);
		maximum_determination(arr, k, Y);
		printf("\n\namount of elements before last minimum = %lf\t", nomer);
		average = arithmetic_mean(arr, k, Y, nomer);
	}
	return 0;
}
