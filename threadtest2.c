// This program creates 3 threads, each with an array of 20 integers.  
// The arrays are initialized with values corresponding to the thread number.
// Each thread prints out the contents of its array.  The program's output
// illustrates the interleaving of thread execution.

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define ARRAY_SIZE 20
#define NTHREADS 3

struct data_t
{
  int array[ARRAY_SIZE];
};

void *print_array(void *thread_arg)
{
    struct data_t *data;
    
    data = (struct data_t *) thread_arg;

    int i;
    for (i = 0; i < ARRAY_SIZE; i++)
      printf("%d\n", data->array[i]);
    pthread_exit(NULL);
}

int main()
{
  int rc, i, j;
  void* status;
  pthread_t threads[NTHREADS];
  struct data_t data[NTHREADS];
  
  
  for (i = 0; i < NTHREADS; i++)
    {
      // initialize thread array
      // thread i's array contains i's for values
      for (j = 0; j < ARRAY_SIZE; j++)
        data[i].array[j] = i;
      
      rc = pthread_create(&threads[i], NULL, print_array, (void *) &data[i]);
      if (rc)
        {
	  printf("BAD\n");
        }
    }
  
  for (i = 0; i < NTHREADS; i++)
    {
      rc = pthread_join(threads[i], &status);
    }  
}
