#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

FILE* fpr1, *fpr2;

void *read_num(void *thread_arg)
{
    int* position = (int *) thread_arg;
    int* nums = malloc(100000*sizeof(int));
    
    printf("Starting position to be read: %d\n", *position);
    //fseek(fpr, sizeof(int) * (*position) * 50000, SEEK_SET);
  
    // read 10000 integers starting at that location
    if (*position == 0)
      fread(nums, sizeof(int), 100000, fpr1);
    else fread(nums, sizeof(int), 100000, fpr2);
    int i, j;
    double sum = 0;
    double avg;
    for (j = 0 ; j < 10000; j++)
    {
      for (i = 0; i < 100000; i++)
	sum += nums[i];
    }
    avg = (double) sum / 10000;
    printf("Average from %d is %lf: \n", *position, avg); 
    pthread_exit(NULL);
}

int main()
{
    int rc, i, status;
    pthread_t threads[10];
    int positions[10];
    
    struct timeval start, stop;
    gettimeofday(&start, NULL);
    
    fpr1 = fopen("numbers1.dat", "rb");	// note binary mode
    fpr2 = fopen("numbers2.dat", "rb");
    if (fpr1 == NULL || fpr2 == NULL) 
    {
      printf("Could not open file. Exiting.\n");
      exit(EXIT_FAILURE);			// terminate program
    }


    for (i = 0; i < 2; i++)
    {
        positions[i] = i;
        rc = pthread_create(&threads[i], NULL, read_num, (void *) &positions[i]);
        if (rc)
        {
            printf("BAD\n");
        }
    }

    for (i = 0; i < 2; i++)
    {
        rc = pthread_join(threads[i], (void **) &status);
    }
    fclose(fpr1);
    fclose(fpr2);
    gettimeofday(&stop, NULL);
    double diff_sec = (double) stop.tv_sec - (double)start.tv_sec;
    double diff_usec = (double) stop.tv_usec - (double)start.tv_usec;
    double diff_s = diff_sec + diff_usec/1e6;
    printf("Program took %lf seconds to execute.\n", diff_s);
}
