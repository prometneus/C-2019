#include <stdio.h>
#include <math.h>

int main2(void) {
	double x1, y1;
	printf("x1=");
	scanf_s("%lf", &x1);
	printf("y1=");
	scanf_s("%lf", &y1);

	   if (y1 > 0 && ((x1 < 0 && y1 <= 0.5 * x1 - 1) || (x1 >= 0 && y1 <= 1 - x1 * x1 * x1)))
	   {
		   printf("Yes somewhere");
	   }
	   else printf("No way");

	 _getch();
	 return 0;
}
