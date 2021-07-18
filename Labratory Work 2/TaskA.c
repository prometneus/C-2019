#include <stdio.h>
#include <math.h>
int a(double x, double y)
{
	return (y > 0 && ((x < 0 && y <= 0.5 * x + 1) || (x >= 0 && y <= 1 - x * x * x)));
}

int main(void) 
{
	double x, y;
	int m = 0;

	printf("x=");
	scanf_s("%lf", &x);
	printf("y=");
	scanf_s("%lf", &y);

	if (y > 0)
	{
		if (x < 0)
		{
			if (y <= 0.5 * x + 1)
			{
				printf("Yes left\n");
			}
			else printf("No left\n");
		}
		else if (y <= 1 - x * x * x)
		{
			printf("Yes right\n");
		}
		else printf("No right\n");
	}
	else printf("No anyway\n");

	if (y > 0 && ((x < 0 && y <= 0.5 * x + 1) || (x >= 0 && y <= 1 - x * x * x)))
	{
		printf("Yes somewhere\n");
	}
	else printf("No\n");

	if (a(x, y))
	{
		printf("True\n");
	}
	else printf("False\n");
	
	_getch();
	return 0;
}