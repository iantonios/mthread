#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int primes[] = {1645333507,253450711,1006003,715827883,99990001,1442968193,
	111191111,3337333,60000049,2281,780291637,2922509,37024851,16785407,
	479001599, 120121};

int main()
{
	int filenum;
	FILE* fp;
	char filename[7];
	srand(time(NULL));
   	for (filenum = 1; filenum <= 10; filenum++)
   	{
		// generate file name
   		sprintf(filename, "%d.txt", filenum);
		fp = fopen(filename, "w");
		if (!fp) 
		{
			fprintf(stderr, "Unable to create %s. Exiting.", filename);
			exit(1);
		}
		fprintf(stdout, "Generating %s\n", filename);
 		int i;
 		for (i = 0; i < 1000000; i++)
 		{
 			int num = rand();
 			if (num > primes[0] && num % 3 != 0) 
			{
				int k = primes[0] + 2 * (rand()%10000) - 1;
 				fprintf(fp, "%d\n", k);
			}
 			else if (i % 9000 == 0)
 			{
 				int j = rand() % 16;
 				fprintf(fp, "%d\n", primes[j]);
 			}
 			else
 				fprintf(fp, "%d\n", num);
 		}
		fclose(fp);
	}
}
