// Variation of multithreaded sum program threadedsum.c illustrating the 
// use of condition variables.  The program creates n worker threads and 
// a reporter thread.  When a worker thread computes its sum, it places
// its result in array 'thread_sums'. The last worker thread signals the 
// reporter thread using the 'threads_done' condition variable. The reporter 
// outputs the final sum.
// 
// Use -lpthread when compiling 

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define ARRAY_SIZE 10000000  

volatile int list[ARRAY_SIZE];
volatile int threads_left;
int* thread_sums;
pthread_cond_t threads_done;
pthread_mutex_t mutex;

// function prototypes
void* sumSegment(void*);
void* reporter(void*);

// boundaries of the array segment assigned to thread i
typedef struct array_segment_limits
{
   int low;
   int high;
   int id;  
} limits;

int main(int argc, char* argv[])
{
   if (argc !=2)
   {  
      printf("Usage: %s n, where n is the number of threads. Exiting.\n", argv[0]);
      exit(0);
   }

   int n = atoi(argv[1]);
   threads_left = n;
   
   // put random values in array
   int i;
   srand(time(NULL));
   for (i = 0; i < ARRAY_SIZE; i++)
      list[i] = rand() % 10;
   
   // allocate thread id structures, and array segment boundary structures
   pthread_t* threadids = (pthread_t *) malloc(sizeof(pthread_t) * (n+1));   
   limits* boundaries = (limits*) malloc(sizeof(limits) * n);
   
   // compute the array segment boundaries of each thread
   boundaries[0].low = 0;
   boundaries[0].high = ARRAY_SIZE / n - 1;
   boundaries[0].id = 0;
   boundaries[n-1].high = ARRAY_SIZE - 1;
   for (i = 1; i < n; i++)
   {
      boundaries[i].low = boundaries[i-1].high + 1;
      boundaries[i].id = i;
      if (i == n-1) break; // high for last segment is already set
      boundaries[i].high = boundaries[i].low + ARRAY_SIZE / n - 1;
   }
   
   // create array for threads to place their sums
   // calloc clears the allocated memory
   thread_sums = (int*) calloc(n, sizeof(int));
   
   // initialize mutex and condition variable
   pthread_mutex_init(&mutex, NULL);
   pthread_cond_init(&threads_done, NULL);
   
   // create reporter thread
   pthread_create(&threadids[n], NULL, reporter, NULL);
   
   // create the n threads and supply each with its segment boundary
   for (i = 0; i < n; i++)
      pthread_create(&threadids[i], NULL, sumSegment, (void*) &boundaries[i]);
   
   // wait for reporter thread
   pthread_join(threadids[n], NULL);
}

void* sumSegment(void* arg)
{
   int sum = 0;
   limits* boundary = (limits*) arg;
   
   int i;
   for (i = boundary->low; i <= boundary->high; i++)
      sum += list[i];

   thread_sums[boundary->id] = sum;
   
   // last thread to compute its sum will signal reporter thread
   pthread_mutex_lock(&mutex);
   threads_left--;
   if (threads_left == 0)
      pthread_cond_signal(&threads_done);
   pthread_mutex_unlock(&mutex);

   fprintf(stderr, "Thread %d done.\n", boundary->id);
   pthread_exit(0);
} 

void* reporter(void* arg)
{
   pthread_mutex_lock(&mutex);
   if (threads_left > 0)
   {
      fprintf(stderr, "Reporter thread: started, waiting for worker threads to finish.\n");
      // pthread_cond_wait simulatenously blocks and releases mutex so that other threads
      // can enter their critical sections
      pthread_cond_wait(&threads_done, &mutex);
      // upon function return, reporter thread holds mutex
   }
   pthread_mutex_unlock(&mutex);
   
   int sum = 0, i;
   for (i = 0; i < ARRAY_SIZE; i++)
      sum += list[i];
   
   fprintf(stderr, "Reporter thread: multithreaded sum is %d.\n", sum);
}
