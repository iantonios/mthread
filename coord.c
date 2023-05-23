
// basic coordination problem
// **** compile with -lpthread switch

#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

volatile int x, y;
sem_t s1, s2; 

void* T1(void *thread_arg)
{
  int i = 0;
  while (i < 10)
  {
    sem_wait(&s1);
    printf("T1 read x as: %d\n", x);
    y = rand();
    printf("T1 wrote %d in y\n", y);
    sem_post(&s2);
    i++;
  }
}

void* T2(void *thread_arg)
{
  int i = 0;
  while (i < 10)
  {
    x = rand();
    printf("T2 wrote %d in x\n", x);
    sem_post(&s1);
    sem_wait(&s2);
    printf("T2 read %d from y\n", y);
    i++;
  }
}

int main()
{
    pthread_t threads[2];

    sem_init(&s1, 0, 0);

    pthread_create(&threads[0], NULL, T1, NULL);
    pthread_create(&threads[1], NULL, T2, NULL);
    
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    
    sem_destroy(&s1);
    sem_destroy(&s2);
}
