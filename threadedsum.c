// performs a multihreaded sum of an array of 1e6 elements
// number of threads is specified as a command line argument

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define ARRAY_SIZE 1000000

volatile int list[ARRAY_SIZE];
void* sumSegment(void* arg);

// boundaries of the array segment assigned to thread i
typedef struct array_segment_limits
{
   int low;
   int high;
} limits;

int main(int argc, char* argv[])
{
   if (argc !=2)
   {  
      printf("Usage: %s n, where n is the number of threads. Exiting.\n");
      exit(0);
   }

   int n = atoi(argv[1]);
   
   // put random values in array
   int i;
   srand(time(NULL));
   for (i = 0; i < ARRAY_SIZE; i++)
      list[i] = rand() % 10;
   
   // allocate thread id structures, and array segment boundary structures
   pthread_t* threadids = (pthread_t *) malloc(sizeof(pthread_t) * n);   
   limits* boundaries = (limits*) malloc(sizeof(limits) * n);
   
   // compute the array segment boundaries of each thread
   boundaries[0].low = 0;
   boundaries[0].high = ARRAY_SIZE / n - 1;
   boundaries[n-1].high = ARRAY_SIZE - 1;
   for (i = 1; i < n; i++)
   {
      boundaries[i].low = boundaries[i-1].high + 1;
      if (i == n-1) break; // high for last segment is already set
      boundaries[i].high = boundaries[i].low + ARRAY_SIZE / n - 1;
   }
   
   // create the n threads and supply each with its segment boundary
   for (i = 0; i < n; i++)
      pthread_create(&threadids[i], NULL, sumSegment, (void*) &boundaries[i]);
   
   int supersum = 0;
   int* sum;
   void* temp;

   // accumulate sums returned from threads
   for (i = 0; i < n; i++)
   {
      pthread_join(threadids[i], &temp);
      sum = (int*) temp;
      supersum += *sum;
   }
   fprintf(stderr, "Multithreaded sum of all array elements is %d.\n", supersum);
   
   // make sure that we can get the same sum as the threads
   *sum = 0;
   for (i = 0; i < ARRAY_SIZE; i++)
      *sum += list[i];
   
   if (*sum != supersum)
      fprintf(stderr, "Oops, couldn't validate the multithreaded sum.  Sum should be %d.\n", *sum);
}

void* sumSegment(void* arg)
{
   int* sum = (int*) malloc(sizeof(int));   
   *sum = 0;
   limits* boundary = (limits*) arg;
   
   int i;
   for (i = boundary->low; i <= boundary->high; i++)
      *sum += list[i];
   return (void*) sum;
} 

