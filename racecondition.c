#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define ARRAY_SIZE 100

volatile int amt[ARRAY_SIZE];

void *deposit(void *thread_arg)
{
  int i = 0, j = 0;
   for (i = 0; i < 1000000; i++)
    {
      for (j = 0; j < ARRAY_SIZE; j++)
	amt[j] = amt[j] - 10;
    }
}

void* withdraw(void *thread_arg)
{
  int i = 0, j = 0;
  for (i = 0; i < 1000000; i++)
    {
      for (j = 0; j < ARRAY_SIZE; j++)
	amt[j] = amt[j] + 10;
    }
}

int main()
{
    int rc, i;
    void* status;
    pthread_t threads[2];

    for (i = 0; i < ARRAY_SIZE; i++)
      {
	amt[i] = 0;
      }

    rc = pthread_create(&threads[0], NULL, withdraw, NULL);
    if (rc) printf("BAD\n");
    rc = pthread_create(&threads[1], NULL, deposit, NULL);
    if (rc) printf("BAD\n");

    for (i = 0; i < 2; i++)
    {
        rc = pthread_join(threads[i], &status);
    }

    for (i = 0; i < ARRAY_SIZE; i++)
      printf("%d ", amt[i]);
}
