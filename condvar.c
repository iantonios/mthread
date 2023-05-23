
// **** compile with -lpthread switch

#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

volatile int x, y;
volatile long z;
pthread_mutex_t mutex;
pthread_cond_t cond;

void *T1(void *thread_arg)
{
   while (1)
   {
      pthread_mutex_lock(&mutex);
      x = rand();
      y = rand();
      pthread_mutex_unlock(&mutex);
      z++;
      printf("%d ", z);
      if (x + y > 50000)
      {
         pthread_cond_signal(&cond);
         break;
      }
   }

   pthread_exit(0);
}

void* T2(void *thread_arg)
{
   pthread_mutex_lock(&mutex);
   if (x + y < 50000)
      pthread_cond_wait(&cond, &mutex);
   printf("It took %d draws before two consecutive numbers were equal.\n", z);
   pthread_mutex_unlock(&mutex);
   pthread_exit(0);
}

int main()
{
    z = 0;
    pthread_t threads[2];
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&threads[0], NULL, T1, NULL);
    pthread_create(&threads[1], NULL, T2, NULL);
     
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

}
