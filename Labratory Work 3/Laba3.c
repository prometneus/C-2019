#include <math.h>
#include <stdio.h>

int main(void) {
	int key;
	double x;

	printf("Enter the variant of processing (1 or 2), key=");
	scanf_s("%d", &key);
	printf("Enter -1 < x < 1, x = ");
	scanf_s("%lf", &x); 
	
	if (-1 < x && x < 1) {
		switch (key) {
		case 1:
		{
			int N;
			double m, norm, y, Z;
			printf("Enter the number of members, N=");
			scanf_s("%d", &N);
			norm = log((1 + x) / (1 - x));
			y = x; Z = y;
			for (m = 2; m <= N; m++)
			{
				y = y * x * x * (2.0 * m - 3.0) / (2.0 * m - 1.0);
			    Z = Z + y;
			}
			printf("Sum %d members = %lf\n", N, 2*Z);
			printf("Check log=%lf\n", norm);
			break;
		}

		case 2:
		{
			double epsilon, norm, y1, y, Sum;
			int m;

			printf("Enter inaccuracy: epsilon=");
			scanf_s("%lf", &epsilon);
			norm = log((1 + x) / (1 - x));
			m = 2; y = x; Sum = y; y1 = 0;

			while (fabs(y) > epsilon)
			{
				
				y = y * x * x * (2.0 * m - 3.0) / (2.0 * m - 1.0);
				Sum = Sum + y;
					m = m++;
			}
			
			printf("Sum=%lf\n", 2*Sum);
			printf("check log=%lf\n", norm);
			break;
		}
		default: printf("Choose another variant"); break;
		}
	}
	else printf("Impossible to solve\n");
	_getch();
}