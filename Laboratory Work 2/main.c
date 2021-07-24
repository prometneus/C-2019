#include <stdio.h>
#include <math.h>

int main(void) {
	double x, y;

	printf("x=");
	scanf_s("%lf", &x);
	printf("y=");
	scanf_s("%lf", &y);

	switch (x < > 0)
	{
		case (x <= 0) && (x >= -2) :
			if (y <= 0.5 * x + 1) 
			{
				printf("Yes");
			}
			else
			{
				printf("no1");
			}
		 break;
		 case (x >= 0) && (x <= 1) :
			 if (y <= 1 - x * x * x)
			 {
				 printf("Yes");
			 }
			 else
			 {
				 printf("no2");
			 }
		 break;
		 default: printf("NO");
	}

return 0;
}