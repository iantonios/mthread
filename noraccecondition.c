// file: noracecondition.c
// Program eliminates data corruption in racecondition.c via a mutex

#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define ARRAY_SIZE 100

pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;

volatile int amt[ARRAY_SIZE];

void *deposit(void *thread_arg)
{
  int i = 0, j = 0;
   for (i = 0; i < 1000000; i++)
    {
      // start critical section
      pthread_mutex_lock(&mylock);
      for (j = 0; j < ARRAY_SIZE; j++)
	{
	  amt[j] = amt[j] - 10; 
	}
      // end critical section
      pthread_mutex_unlock(&mylock);
    }
}

void* withdraw(void *thread_arg)
{
  int i = 0, j = 0;
  for (i = 0; i < 1000000; i++)
    {
      // start critical section
      pthread_mutex_lock(&mylock);
      for (j = 0; j < ARRAY_SIZE; j++)
	{
	  amt[j] = amt[j] + 10;
	}
      // end critical section
      pthread_mutex_unlock(&mylock);
    }
}

int main()
{
    int rc, i, status;
    pthread_t threads[2];

    for (i = 0; i < ARRAY_SIZE; i++)
      {
	amt[i] = 0;
      }

    pthread_create(&threads[0], NULL, withdraw, NULL);
    pthread_create(&threads[1], NULL, deposit, NULL);
    
    for (i = 0; i < 2; i++) {
        rc = pthread_join(threads[i], (void **) &status);
    }

    for (i = 0; i < ARRAY_SIZE; i++)
      printf("%d ", amt[i]);
}
