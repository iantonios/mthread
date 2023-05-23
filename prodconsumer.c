// Implements solution to bounded buffer problem.  Buffer access
// is LIFO (not a queue).  

#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define BUFFSIZE 5
#define N 5 // number of threads

void* producer(void*);
void* consumer(void*);

sem_t full, empty, mutex;
char buff[N];
volatile int current = 0; // index of buffer location to fill

int main()
{
  pthread_t threads[N];

  sem_init(&full, 0, 0);
  sem_init(&empty, 0, BUFFSIZE);
  
  int i;
  // create floor(N/2) threads if N is odd
  for (i = 0; i < N/2; i++)
    { 
      pthread_create(&threads[i], NULL, producer, (void*)&i);
      pthread_create(&threads[i+1], NULL, consumer, (void*) &i);
    }

  for (i = 0; i < N; i++)
      pthread_join(threads[i], (void **) NULL);
}


void* producer(void* arg)
{

  int i = 0;
  int* id = (int*) arg;
  while (i++ < 50)
    {
      sem_wait(&empty);
      // produce a letter
      char c = (char) (rand() % 26 + 'a');
      
      sem_wait(&mutex);
	// place letter in buffer and update index
      buff[current++] = c;
      printf("producer %d: placed %c in %d\n", *id, c, current-1);
      sem_post(&mutex);
	// signal consumer that a slot has been filled
      sem_post(&full);
    }
}


void* consumer(void* arg)
{
  int i = 0;
  int* id = (int*) arg;

  while (i++ < 50)
    {
      sem_wait(&full);
      sem_wait(&mutex);
      char c = buff[--current];
      printf("consumer %d: removed %c from location %d\n", *id, c, current);
      sem_post(&mutex);
	// signal producer that a slot is empty
      sem_post(&empty);
    }
}

