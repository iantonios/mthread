
// using a binary semaphore to protect access to shared array
// array values should be 0 (compare that to racecondition.c)
// **** compile with -lpthread switch

#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

volatile int amt[1000];
sem_t mutex; // semaphore to achieve mutual exclusion

void *deposit(void *thread_arg)
{
  int i = 0, j = 0;
   for (i = 0; i < 1000000; i++)
    {
      // start of critical section
      sem_wait(&mutex);
      for (j = 0; j < 100; j++)
	amt[j] = amt[j] - 10;
      // end of critical section
      sem_post(&mutex);
    }
}

void* withdraw(void *thread_arg)
{
  int i = 0, j = 0;
  for (i = 0; i < 1000000; i++)
    {
      // start of critical section
      sem_wait(&mutex);
      for (j = 0; j < 100; j++)
	amt[j] = amt[j] + 10;
      // end of critical section
      sem_post(&mutex);
    }
}

int main()
{
    int rc, i, status;
    pthread_t threads[2];

    // initialize mutex value to 1
    // 0 as a second argument denotes that all threads of this process
    // can manipulate mutex
    sem_init(&mutex, 0, 1);

    for (i = 0; i < 1000; i++)
	amt[i] = 0;

    rc = pthread_create(&threads[0], NULL, withdraw, NULL);
    if (rc) printf("BAD\n");
    rc = pthread_create(&threads[1], NULL, deposit, NULL);
    if (rc) printf("BAD\n");

    for (i = 0; i < 2; i++)
        rc = pthread_join(threads[i], NULL);

    for (i = 0; i < 100; i++)
      printf("%d ", amt[i]);

    // give back the resource to the OS
    sem_destroy(&mutex);
}
