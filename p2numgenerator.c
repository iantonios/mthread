#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;
	srand(time(NULL));
	for (i = 0; i < 1000000; i++)
	{
		int n = rand();
		if (n % 2 == 0) n++;
		printf("%d \n", n);
	}
}

