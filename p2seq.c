#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int a = 5;
int b;

int isPrime(int);

int main()
{
	int n, i, j, largest = 0;
	FILE *fp;
	char fn[10];

        float diff_sec, diff_usec;
        double diff_s;
        struct timeval start, stop;

        gettimeofday(&start, NULL);

	for (j = 1; j <= 10; j++)
	{
		sprintf(fn, "%d.%s", j, "txt");
		fp = fopen(fn, "r");
		for (i = 0; i < 1000000; i++)
		{
			fscanf(fp, "%d", &n);
			if (n > largest)
			{
				if (isPrime(n) == 0) largest = n;
			}
		}
		fclose(fp);
	}
	
	gettimeofday(&stop, NULL);

        diff_sec = (float) stop.tv_sec - (float)start.tv_sec;
        diff_usec = (float) stop.tv_usec - (float)start.tv_usec;
        diff_s = diff_sec + diff_usec/1e6;
        printf("Program took %lf seconds to execute.\n", diff_s);
 
	printf("Largest prime is: %d\n", largest);
}

int isPrime(int n)
{
	
	int i, max = ((int) sqrt(n)) + 1;
	
	for (i = 2; i <= max; i++)
	{
		if (n % i == 0)
			return 1;
	}
	return 0;
}
