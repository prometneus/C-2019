#include <stdio.h>
#include <malloc.h>
#include <time.h>

double selectionsort(double* arr, int N)
{
    clock_t start = clock();
    int min, temp; 
    for (int i = 0; i < N - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < N; j++)
        {
            if (arr[j] < arr[min])
                min = j;
        }
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
	}
    clock_t stop = clock();
    double zeit = (double)(stop - start) * 1000 / CLOCKS_PER_SEC;
    return zeit;
}

double quicksort(double* arr, int first, int last)
{
    int i = first, j = last, x = arr[(first + last) / 2];
    clock_t start = clock();
    do {
        while (arr[i] < x) i++;
        while (arr[j] > x) j--;

        if (i <= j) {
            if (arr[i] > arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp; //swap(&arr[i], &arr[j]);
            }
            i++;
            j--;
        }
    } while (i <= j);

    if (i < last)
        quicksort(arr, i, last);
    if (first < j)
        quicksort(arr, first, j);
    clock_t stop = clock();
    double zeit = (double)(stop - start) * 1000 / CLOCKS_PER_SEC;
    return zeit;
}

void siftDown(double* arr, int k, int N)
{
    int maxChild;
    int done = 0;
    while ((k * 2 <= N) && (!done))
    {
        if (k * 2 == N)
            maxChild = k * 2;
        else if (arr[k * 2] > arr[k * 2 + 1])
            maxChild = k * 2;
        else
            maxChild = k * 2 + 1;
        if (arr[k] < arr[maxChild])
        {
            double temp = arr[k];
            arr[k] = arr[maxChild];
            arr[maxChild] = temp;
            k = maxChild;
        }
        else
            done = 1;
    }
}

double heapsort(double* arr, int N)
{
    clock_t start = clock();
    for (int i = (N / 2) - 1; i >= 0; i--)
        siftDown(arr, i, N - 1);
    for (int i = N - 1; i >= 1; i--)
    {
        double temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        siftDown(arr, 0, i - 1);
    }
    clock_t stop = clock();
    double zeit = (double)(stop - start) * 1000 / CLOCKS_PER_SEC;
    return zeit;
}

int main(void)
{
    srand((unsigned)time(NULL));
    double* arr;
    int N = 0, type;
    double zeit_eins, zeit_zwei, zeit_drei;

    printf("Enter the amount of elements in the array\t");
    scanf_s("%d", &N);
    arr = (double*)malloc(N * sizeof(double));
    for (int i = 0; i < N; i++)
    {
        arr[i] = (double)rand();
    }

    printf("\nEnter the type of sorting: 1 - Selectionsort; 2 - Quicksort; 3 - Heapsort - \t");
    scanf_s("%d", &type);

    switch (type)
    {
    case 1:
    {
        printf("\n\nYou chose selectionsort\n");
        zeit_eins = selectionsort(arr, N);
        printf("Selectionsort took %lf miliseconds\n", zeit_eins);
        break;
    }
    case 2:
    {
        printf("\n\nYou chose quicksorting\n");
        int first = 0, last = N - 1;
        zeit_zwei = quicksort(arr, first, last);
        printf("Quicksort took %lf miliseconds\n", zeit_zwei);
        break;
    }
    case 3:
    {
        printf("\n\nYou chose heapsort\n");
        zeit_drei = heapsort(arr, N);
        printf("Heapsort took %lf miliseconds\n", zeit_drei);
        break;
    }
    default: printf("Error enter\n"); break;
    }
    free(arr);
    return 0;
}